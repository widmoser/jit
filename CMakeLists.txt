cmake_minimum_required(VERSION 3.8)
project(jit)

set(CMAKE_CXX_STANDARD 17)

add_executable(jit main.cpp ByteStream.cpp asm.cpp Instruction.cpp Instruction.h asm.h)