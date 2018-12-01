cmake_minimum_required(VERSION 3.12)
project(CDataStructures C)

set(CMAKE_C_STANDARD 11)

include_directories(BinarySearchTree)
include_directories(CSplayTree)

add_executable(CDataStructures
        BinarySearchTree/BST.c
        BinarySearchTree/BST.h
        BinarySearchTree/Main.c
        CSplayTree/SplayTree.c
        CSplayTree/SplayTree.h
        CSplayTree/SplayTreeTests.c)
