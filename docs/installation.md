# Installation

SeqForge is written in C++20 and has no external dependencies.

## Requirements

- A C++20 compiler (for example g++ 11 or later).
- CMake 3.16 or later (optional, a single g++ command also works).

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
```

The executable is produced at `build/seqforge`.

## Run the tests

The project ships with unit tests covering the encoder, the k-mer index, the
mapper and the readers.

```bash
ctest --test-dir build --output-on-failure
```

## Build without CMake

A single command is enough for a quick build:

```bash
g++ -std=c++20 -Isrc src/*.cpp -o seqforge
```
