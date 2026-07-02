cmake_minimum_required(VERSION 3.16)
project(SeqForge VERSION 0.3.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# The core library, shared by the command-line tool and the tests.
add_library(seqforge_core
    src/SequenceFile.cpp
    src/FastaReader.cpp
    src/FastqReader.cpp
    src/SequenceAnalyzer.cpp
    src/Menu.cpp
    src/TwoBitEncoder.cpp
    src/KmerIndex.cpp
    src/Mapper.cpp
)
target_include_directories(seqforge_core PUBLIC src)

# The command-line executable.
add_executable(seqforge src/main.cpp)
target_link_libraries(seqforge PRIVATE seqforge_core)

# Unit tests.
enable_testing()
add_executable(seqforge_tests tests/test_main.cpp)
target_link_libraries(seqforge_tests PRIVATE seqforge_core)
add_test(NAME unit_tests COMMAND seqforge_tests)
