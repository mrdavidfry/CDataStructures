#include <stdio.h>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "SplayTree.h"
}

struct SplayTreeTests : testing::Test {

  struct SplayTree *tree;

  SplayTreeTests() {
    tree = create_tree();
  }

  ~SplayTreeTests() {
    if (!tree) {
      return;
    }
    delete_tree(tree);
  }

};

typedef struct SplayTreeTests InitTests;
typedef struct SplayTreeTests InsertTests;
typedef struct SplayTreeTests RotateTests;


// --------------- Init Tests ---------------

TEST_F(InitTests, CreatingATreeSetsTheRootToNull) {
  EXPECT_EQ(NULL, tree->root_node);
}


// --------------- Insert Tests ---------------

TEST_F(InsertTests,
        InsertingNodeIntoEmptyTreeSetsRootToThatNodeAndChildrenToNull) {

  insert_node(tree, 10);

  EXPECT_EQ(10, tree->root_node->address);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
  EXPECT_EQ(NULL, tree->root_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->right_node);
}

TEST_F(InsertTests, InsertAtLeftOfRoot) {
  insert_node(tree, 10);
  insert_node(tree, 5);
  EXPECT_EQ(5, tree->root_node->address);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
  EXPECT_EQ(10, tree->root_node->right_node->address);
  EXPECT_EQ(NULL, tree->root_node->left_node);
}

TEST_F(InsertTests, InsertAtRightOfRoot) {
  insert_node(tree, 10);
  insert_node(tree, 15);

  EXPECT_EQ(15, tree->root_node->address);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
  EXPECT_EQ(10, tree->root_node->left_node->address);
  EXPECT_EQ(NULL, tree->root_node->right_node);
}

TEST_F(InsertTests, LeftZigZigSimpleInsert) {
  insert_node(tree, 15);
  insert_node(tree, 16);
  insert_node(tree, 14);

  EXPECT_EQ(14, tree->root_node->address);
  EXPECT_EQ(15, tree->root_node->right_node->address);
  EXPECT_EQ(16, tree->root_node->right_node->right_node->address);
  EXPECT_EQ(NULL, tree->root_node->right_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->right_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
}

TEST_F(InsertTests, RightZigZigSimpleInsert) {
  insert_node(tree, 15);
  insert_node(tree, 14);
  insert_node(tree, 16);

  EXPECT_EQ(16, tree->root_node->address);
  EXPECT_EQ(15, tree->root_node->left_node->address);
  EXPECT_EQ(14, tree->root_node->left_node->left_node->address);
  EXPECT_EQ(NULL, tree->root_node->left_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->left_node->left_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
}

TEST_F(InsertTests, LeftRightZigZagSimpleInsert) {
  insert_node(tree, 14);
  insert_node(tree, 16);
  insert_node(tree, 15);

  EXPECT_EQ(15, tree->root_node->address);
  EXPECT_EQ(14, tree->root_node->left_node->address);
  EXPECT_EQ(16, tree->root_node->right_node->address);
  EXPECT_EQ(NULL, tree->root_node->left_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->left_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
}

TEST_F(InsertTests, RightLeftZigZagSimpleInsert) {
  insert_node(tree, 16);
  insert_node(tree, 14);
  insert_node(tree, 15);

  EXPECT_EQ(15, tree->root_node->address);
  EXPECT_EQ(14, tree->root_node->left_node->address);
  EXPECT_EQ(16, tree->root_node->right_node->address);
  EXPECT_EQ(NULL, tree->root_node->left_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->left_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
}

TEST_F(InsertTests, ReinsertNodeAtRootSimple) {
  insert_node(tree, 15);
  insert_node(tree, 15);

  EXPECT_EQ(NULL, tree->root_node->parent_node);
  EXPECT_EQ(NULL, tree->root_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->right_node);
}

TEST_F(InsertTests, ReinsertNodeAtRootThatHasChildren) {
  insert_node(tree, 16);
  insert_node(tree, 14);
  insert_node(tree, 15);

  EXPECT_EQ(15, tree->root_node->address);
  EXPECT_EQ(14, tree->root_node->left_node->address);
  EXPECT_EQ(16, tree->root_node->right_node->address);
  EXPECT_EQ(NULL, tree->root_node->left_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->left_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->parent_node);

  insert_node(tree, 15);

  EXPECT_EQ(15, tree->root_node->address);
  EXPECT_EQ(14, tree->root_node->left_node->address);
  EXPECT_EQ(16, tree->root_node->right_node->address);
  EXPECT_EQ(NULL, tree->root_node->left_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->left_node);
  EXPECT_EQ(NULL, tree->root_node->left_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->right_node->right_node);
  EXPECT_EQ(NULL, tree->root_node->parent_node);
}