cmake_minimum_required(VERSION 3.12)
project(CSplayTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CSplayTree
        cmake-build-debug/Balanced_Binary_Tree
        cmake-build-debug/Balanced_Binary_Tree.cbp
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        CMakeLists.txt
        SplayTree.c
        SplayTree.h
        SplayTreeTests.c)
