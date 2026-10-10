# NarrativeEngine

A modular narrative engine written in C++20 for branching dialogues and interactive storytelling.

The project aims to provide a lightweight, engine-independent runtime for narrative-driven games, with future Unreal Engine 5 integration.

## Features

### Current Development
- Dialogue graph with unique node identifiers
- Dialogue, choice, and ending nodes
- Node storage and lookup

### Planned
- Branching dialogue execution
- Narrative variables and conditions
- Actions and event system
- JSON-based story definitions
- Save/load support
- Narrative graph validation
- Unreal Engine 5 integration

## Tech Stack

- C++20
- CMake
- MinGW / GCC
- CLion

## Project Structure

```text
NarrativeEngine/
├── include/narrative/    # Public headers
├── src/                  # Engine implementation
├── examples/             # Console demo
├── stories/              # Narrative data
└── tests/                # Automated tests
```

## Status

Early development — initial dialogue runtime implementation.

## License

MIT License.
