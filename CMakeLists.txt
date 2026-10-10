
cmake_minimum_required(VERSION 3.20)

project(NarrativeEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(narrative_core STATIC
        src/NarrativeEngine.cpp
)

target_include_directories(narrative_core
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(narrative_demo
        examples/main.cpp
)

target_link_libraries(narrative_demo
        PRIVATE narrative_core
)
