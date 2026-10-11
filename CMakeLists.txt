
cmake_minimum_required(VERSION 3.20)

project(NarrativeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(nlohmann_json)

add_library(narrative_core STATIC
        src/NarrativeEngine.cpp
        src/StoryLoader.cpp
        src/StoryValidator.cpp
        include/narrative/StoryValidator.hpp
)

target_include_directories(narrative_core
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(narrative_core
        PUBLIC nlohmann_json::nlohmann_json
)

add_executable(narrative_demo
        examples/main.cpp
)

target_link_libraries(narrative_demo
        PRIVATE narrative_core
)
