//
// Created by maxim_main on 11.10.2026.
//


#include "narrative/StoryLoader.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <utility>

#include "narrative/StoryValidator.hpp"

using namespace std;
using json = nlohmann::json;

namespace narrative {

    void StoryLoader::load(const string& path, NarrativeEngine& engine) {
        ifstream file(path);

        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + path);
        }

        json story;
        file >> story;

        NarrativeEngine loadedEngine;

        for (const json& item : story.at("nodes")) {

            string type = item.at("type").get<string>();
            NodeId id = item.at("id").get<string>();

            if (type == "dialogue") {

                loadedEngine.addNode(
                    DialogueNode{
                    id,
                    item.at("speaker").get<string>(),
                    item.at("text").get<string>(),
                    item.at("next").get<string>()
                });
            }
            else if (type == "choice") {

                vector<Choice> choices;

                for (const json& option : item.at("choices")) {
                    choices.push_back(Choice{
                        option.at("text").get<string>(),
                        option.at("next").get<string>()
                    });
                }
                loadedEngine.addNode(ChoiceNode{id,move(choices)});
            }
            else if (type == "end") {

                loadedEngine.addNode(EndNode{id});
            }
            else {
                throw runtime_error("Unknown node type: " + type);
            }
        }

        NodeId startId = story.at("startNode").get<string>();

        StoryValidator::validate(loadedEngine, startId);

        loadedEngine.start(startId);
        engine = move(loadedEngine);
    }
}
