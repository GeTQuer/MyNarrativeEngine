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

    ParsedStory StoryLoader::parse(const string& path) {
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

        const vector<ValidationIssue> errors = StoryValidator::validate(
            loadedEngine, startId
        );

        return ParsedStory{
            std::move(loadedEngine),
            std::move(startId)
        };
    }
    void StoryLoader::load(
            const std::string& path,
            NarrativeEngine& engine
        )
    {
        ParsedStory parsed = parse(path);

        const auto errors = StoryValidator::validate(
            parsed.engine,
            parsed.startId
        );

        if (!errors.empty()) {
            std::string message = "Story validation failed:\n";

            for (const auto& error : errors) {
                message += "- " + error.message + "\n";
            }

            throw std::runtime_error(message);
        }

        parsed.engine.start(parsed.startId);
        engine = std::move(parsed.engine);
    }


}
