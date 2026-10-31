#include "narrative/StoryValidator.hpp"

#include <type_traits>
#include <utility>
#include <variant>

namespace narrative {

std::vector<std::string> StoryValidator::validate(
    const NarrativeEngine& engine,
    const NodeId& startId)
{
    std::vector<std::string> errors;
    const auto& nodes = engine.getNodes();

    if (nodes.empty()) {
        errors.push_back("Story contains no nodes");
        return errors;
    }

    bool hasEndNode = false;
    bool hasBrokenLinks = false;

    // 1. Проверяем структуру всех узлов
    for (const auto& [key, nodeValue] : nodes) {

        if (const auto* dialogue =
                std::get_if<DialogueNode>(&nodeValue)) {

            const NodeId& next = dialogue->next;

            if (!nodes.contains(next)) {
                errors.push_back(
                    "DialogueNode {" + key +
                    "} references unknown node {" + next + "}"
                );

                hasBrokenLinks = true;
            }
        }
        else if (const auto* choiceNode =
                     std::get_if<ChoiceNode>(&nodeValue)) {

            if (choiceNode->choices.empty()) {
                errors.push_back(
                    "ChoiceNode {" + key + "} has no choices"
                );
            }

            for (const Choice& choice : choiceNode->choices) {
                const NodeId& next = choice.next;

                if (!nodes.contains(next)) {
                    errors.push_back(
                        "ChoiceNode {" + key +
                        "} references unknown node {" + next + "}"
                    );

                    hasBrokenLinks = true;
                }
            }
        }
        else if (std::holds_alternative<EndNode>(nodeValue)) {
            hasEndNode = true;
        }
    }

    // 2. Проверяем наличие EndNode
    if (!hasEndNode) {
        errors.push_back("Story contains no EndNode");
    }

    // 3. Проверяем начальный узел
    if (!nodes.contains(startId)) {
        errors.push_back(
            "Start node {" + startId + "} does not exist"
        );
    }

    // 4. Если ссылки или startId некорректны,
    //    проверку достижимости пропускаем
    if (hasBrokenLinks || !nodes.contains(startId)) {
        return errors;
    }

    // 5. Проверяем достижимость через DFS
    std::unordered_set<NodeId> visited;
    dfs(startId, nodes, visited);

    for (const auto& [id, node] : nodes) {
        if (!visited.contains(id)) {
            errors.push_back(
                "Node {" + id + "} is unreachable"
            );
        }
    }

    return errors;
}

void StoryValidator::dfs(
    const NodeId& currentId,
    const std::unordered_map<NodeId, Node>& nodes,
    std::unordered_set<NodeId>& visited)
{
    if (visited.contains(currentId)) {
        return;
    }

    // Защита от несуществующего ID
    if (!nodes.contains(currentId)) {
        return;
    }

    visited.insert(currentId);

    const Node& node = nodes.at(currentId);

    std::visit([&](const auto& currentNode) {

        using T = std::decay_t<decltype(currentNode)>;

        if constexpr (std::is_same_v<T, DialogueNode>) {
            dfs(currentNode.next, nodes, visited);
        }
        else if constexpr (std::is_same_v<T, ChoiceNode>) {
            for (const Choice& choice : currentNode.choices) {
                dfs(choice.next, nodes, visited);
            }
        }

        // EndNode: переходов нет

    }, node);
}

}