//
// Created by maxim_main on 11.10.2026.
//

#pragma once
#include <string>
#include "NarrativeEngine.hpp"
using namespace std;

    


namespace narrative {
    struct ParsedStory {
        NarrativeEngine engine;
        NodeId startId;
    };

    class StoryLoader {
        public:
            static void load(
                const string&path,
                NarrativeEngine& engine
                );
            static ParsedStory parse(const std::string& path);
    };
}

