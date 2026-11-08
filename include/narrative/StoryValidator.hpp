//
// Created by maxim_main on 11.10.2026.
//

#pragma once
#include "NarrativeEngine.hpp"
#include <unordered_set>
using namespace std;

namespace narrative {

    enum class ValidationSeverity {
        Error,
        Warning
    };

    struct ValidationIssue {
        NodeId nodeId;
        std::string message;
        ValidationSeverity severity;
    };

    class StoryValidator {
    public:
        // static vector<std::string> validate(const NarrativeEngine &engine, const NodeId& startId);
        static vector<ValidationIssue> validate(const NarrativeEngine &engine, const NodeId& startId);
    private:
        static void dfs(const string& currentId,const unordered_map<NodeId, Node>& nodes_, unordered_set<NodeId>& visited);
    };
};


