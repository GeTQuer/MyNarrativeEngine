#include "../include/narrative/NarrativeEngine.hpp"
#include "narrative/NarrativeEngine.hpp"

#include <stdexcept>
#include <utility>

#include "../include/narrative/Node.hpp"

using namespace std;

namespace narrative {

    void NarrativeEngine::addNode(Node node) {

        // string id = visit([](const auto& nodeValue) {
        //     return nodeValue.id;
        // }, node);

        string id;

        if (holds_alternative<DialogueNode>(node)) {
            id = get<DialogueNode>(node).id;
        }
        else if (holds_alternative<ChoiceNode>(node)) {
            id = get<ChoiceNode>(node).id;
        }
        else if (holds_alternative<EndNode>(node)) {
            id = get<EndNode>(node).id;
        }

        if (nodes_.contains(id)) {
            throw runtime_error("Node already exists: " + id);
        }

        nodes_.emplace(id, move(node));
    }

    void NarrativeEngine::moveTo(const NodeId&id) {
        if (!nodes_.contains(id)) {
            throw runtime_error("Node not found: " + id);
        }
        currentId_ = id;
    }


    void NarrativeEngine::start(const NodeId& id) {
        moveTo(id);
    }

    const Node& NarrativeEngine::current() const {

        if (!currentId_.has_value()) {
            throw logic_error("Dialogue has not started");
        }

        return nodes_.at(currentId_.value());
    }

};