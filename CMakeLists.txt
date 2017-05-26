cmake_minimum_required(VERSION 3.6)
project(VeMUlator)

set(CMAKE_CXX_STANDARD 11)

set(EMU_SOURCE_FILES Source/VeMUlator/main.cpp
                     Source/VeMUlator/86KCore.cpp
                     Source/VeMUDisassembler/Disassembler.cpp)
set(DISASSEMBLER_SOURCE_FILES Source/VeMUDisassembler/main.cpp
                              Source/VeMUDisassembler/Disassembler.cpp)
include_directories(Source/VeMUlator Source/VeMUDisassembler)

add_executable(VeMUlator ${EMU_SOURCE_FILES})
add_executable(VeMUDisassembler ${DISASSEMBLER_SOURCE_FILES})