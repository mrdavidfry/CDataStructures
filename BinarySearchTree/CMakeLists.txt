cmake_minimum_required(VERSION 3.12)
project(BinarySearchTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BinarySearchTree
        cmake-build-debug/BinarySearchTree.cbp
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        BST.h
        BST.c
        CMakeLists.txt
        Main.c)
