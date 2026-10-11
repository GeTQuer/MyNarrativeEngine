//
// Created by maxim_main on 11.10.2026.
//

#include "narrative/StoryValidator.hpp"
#include <stdexcept>
#include <format>
#include <unordered_set>
using namespace std;

namespace narrative {
    void StoryValidator::validate(const NarrativeEngine &engine, const NodeId& startId) {
        const auto& nodes = engine.getNodes();
        if (nodes.empty()) {
            throw runtime_error("Story validation requested for empty nodes.");
        }

        bool hasEndNode = false;

        for (const auto& [key,nodeValue] : nodes) {
            if (holds_alternative<DialogueNode>(nodeValue)) {

                const DialogueNode& dialogueNode = get<DialogueNode>(nodeValue);

                const NodeId& next = dialogueNode.next;


                if (!nodes.contains(next)) {
                    throw runtime_error(
                        format("DialogueNode '{}' references unknown node '{}'", key, next)
                        );
                }


            }else if (holds_alternative<ChoiceNode>(nodeValue)) {

                const ChoiceNode& choiceNode = get<ChoiceNode>(nodeValue);

                if (choiceNode.choices.empty()) {
                    throw runtime_error(
                        format("ChoiceNode {} has no choices", key)
                        );
                }
                for (const Choice& choice: choiceNode.choices) {

                    const NodeId& next = choice.next;

                    if (!nodes.contains(next)) {
                        throw runtime_error(
                            format("ChoiceNode '{}' references unknown node '{}'", key, next)
                            );
                    }

                }
            }else if (holds_alternative<EndNode>(nodeValue)) {
                hasEndNode = true;
            }
        }
        if (!hasEndNode) {
            throw runtime_error("Story contains no EndNode");
        }
        
        unordered_set<NodeId> visited;
        dfs(startId, nodes, visited);

        if (visited.size() != nodes.size()) {
            for (const auto& [id, node] : nodes) {
                if (!visited.contains(id)) {
                    throw runtime_error(format("Node '{}' is unreachable", id));
                }
            }
        }
    }
    void StoryValidator::dfs
    (
        const string& currentId,
        const unordered_map<NodeId, Node>& nodes,
        unordered_set<NodeId>& visited)
    {
        if (visited.contains(currentId)) {
            return;
        }

        visited.insert(currentId);
        const Node& node = nodes.at(currentId);


        visit([&](const auto& currentNode) {
            using T = decay_t<decltype(currentNode)>;

            if constexpr (is_same_v<T, DialogueNode>) {
                dfs(currentNode.next, nodes, visited);
            }
            else if constexpr (is_same_v<T, ChoiceNode>) {
                for (const Choice& choice : currentNode.choices) {
                    dfs(choice.next, nodes, visited);
                }
            }
        }, node);
    }

}
