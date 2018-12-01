#include <stdio.h>
#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

/* C and C++ complilation creates different symbol names on object file
 * level ('name mangling'). You must use the extern "C" {} block
 * to stop C++ from mangling the names . */
extern "C" {
#include "BST.h"
}

struct BSTTest : testing::Test {
  struct BST *tree;

  BSTTest() {
    tree = create_tree();
  }

  ~BSTTest() {
    delete_tree(tree);
  }
};


// ------------------ Creating node tests: ------------------

TEST(CreateNode, CreatingANodeInitializesValueToValuePassedIntoFunction) {
  struct node *node = create_node(10, NULL);

  EXPECT_EQ(10, node->value);

  destroy_node(node);
}

TEST(CreateNode, CreatingANodeInitializesChildrenToNull) {
  struct node *node = create_node(10, NULL);

  EXPECT_EQ(NULL, node->left);
  EXPECT_EQ(NULL, node->right);

  destroy_node(node);
}

TEST(CreateNode, CreatingANodeInitializesTheRootToRootPassedIntoFunction) {
  struct node *node1 = create_node(13, NULL);
  struct node *node2 = create_node(10, node1);

  EXPECT_EQ(NULL, node1->parent);
  EXPECT_EQ(node2->parent->value, node1->value);

  destroy_node(node1);
  destroy_node(node2);
}


// ------------------ Node equality tests: ------------------

TEST(NodeEquality, NodesWithTheSameValueAreEqual) {
  struct node *node1 = create_node(12, NULL);
  struct node *node2 = create_node(12, NULL);

  EXPECT_TRUE(node_equals(node1, node2));
  EXPECT_TRUE(node_equals(node2, node1));

  destroy_node(node1);
  destroy_node(node2);
}

TEST(NodeEquality, NodesWithDifferentValuesAreNotEqual) {
  struct node *node1 = create_node(12, NULL);
  struct node *node2 = create_node(13, NULL);

  EXPECT_FALSE(node_equals(node1, node2));
  EXPECT_FALSE(node_equals(node2, node1));

  destroy_node(node1);
  destroy_node(node2);
}


// ---------------- Tree initialization tests: ----------------

TEST_F(BSTTest, CreatingTreeInitializesRootToNull) {
  EXPECT_EQ(NULL, tree->root);
}


// -------------------- Node insert tests: --------------------

TEST_F(BSTTest, InsertingNodeIntoEmptyTreeMakesNodeTheRoot) {
  EXPECT_EQ(NULL, tree->root);
  insert_node(tree, 10);
  EXPECT_EQ(10, tree->root->value);
}

TEST_F(BSTTest, InsertThreeSimpleAndCheckLeavesHaveNoChildren) {
  insert_node(tree, 10);
  insert_node(tree, 5);
  insert_node(tree, 15);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(NULL, tree->root->left->left);
  EXPECT_EQ(NULL, tree->root->left->right);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(NULL, tree->root->right->left);
  EXPECT_EQ(NULL, tree->root->right->right);
}

TEST_F(BSTTest, InsertTenNodesInNoSpecificOrder) {
  insert_node(tree, 10);
  insert_node(tree, 15);
  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 9);
  insert_node(tree, 13);
  insert_node(tree, 14);
  insert_node(tree, 22);
  insert_node(tree, 21);
  insert_node(tree, 0);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(7, tree->root->left->right->value);
  EXPECT_EQ(9, tree->root->left->right->right->value);
  EXPECT_EQ(13, tree->root->right->left->value);
  EXPECT_EQ(14, tree->root->right->left->right->value);
  EXPECT_EQ(22, tree->root->right->right->value);
  EXPECT_EQ(21, tree->root->right->right->left->value);
  EXPECT_EQ(0, tree->root->left->left->value);
}

TEST_F(BSTTest, FiveNodesInsertedInDecreasingOrder) {
  insert_node(tree, 5);
  insert_node(tree, 4);
  insert_node(tree, 3);
  insert_node(tree, 2);
  insert_node(tree, 1);

  EXPECT_EQ(5, tree->root->value);
  EXPECT_EQ(4, tree->root->left->value);
  EXPECT_EQ(3, tree->root->left->left->value);
  EXPECT_EQ(2, tree->root->left->left->left->value);
  EXPECT_EQ(1, tree->root->left->left->left->left->value);
}

TEST_F(BSTTest, FiveNodesInsertedInIncreasingOrder) {
  insert_node(tree, 1);
  insert_node(tree, 2);
  insert_node(tree, 3);
  insert_node(tree, 4);
  insert_node(tree, 5);

  EXPECT_EQ(1, tree->root->value);
  EXPECT_EQ(2, tree->root->right->value);
  EXPECT_EQ(3, tree->root->right->right->value);
  EXPECT_EQ(4, tree->root->right->right->right->value);
  EXPECT_EQ(5, tree->root->right->right->right->right->value);
}


// -------------------- Node find tests: --------------------

TEST_F(BSTTest, FindingANodeNotInTreeReturnsNull) {
  insert_node(tree, 1);
  insert_node(tree, 4);
  insert_node(tree, 7);
  insert_node(tree, 2);
  insert_node(tree, 6);

  EXPECT_EQ(NULL, find_node(tree, 100));
}

TEST_F(BSTTest, FindingRootNodeReturnsThatNode) {
  struct node* node1 = create_node(1, NULL);

  insert_node(tree, 1);

  EXPECT_TRUE(node_equals(find_node(tree, 1), node1));

  destroy_node(node1);
}

TEST_F(BSTTest, FindingANodeNotInTreeReturnsThatNode) {
  struct node *node2 = create_node(2, NULL);
  struct node *node4 = create_node(4, NULL);

  insert_node(tree, 1);
  insert_node(tree, 4);
  insert_node(tree, 7);
  insert_node(tree, 2);
  insert_node(tree, 6);

  EXPECT_TRUE(node_equals(find_node(tree, 2), node2));
  EXPECT_TRUE(node_equals(find_node(tree, 4), node4));

  destroy_node(node2);
  destroy_node(node4);
}


// -------------------- Tree remove tests: --------------------

TEST_F(BSTTest, RemovingFromEmptyTreeDoesNothing) {
  EXPECT_EQ(NULL, tree->root);
}

TEST_F(BSTTest, RemovingRootNodeMakesTreeRootNull) {
  insert_node(tree, 10);
  EXPECT_EQ(10, tree->root->value);
  remove_node(tree, 10);
  EXPECT_EQ(NULL, tree->root);
}

TEST_F(BSTTest, RemovingNodesNotInTreeDoesNothing) {
  insert_node(tree, 10);
  insert_node(tree, 15);
  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 9);
  insert_node(tree, 13);
  insert_node(tree, 14);
  insert_node(tree, 22);
  insert_node(tree, 21);
  insert_node(tree, 0);

  remove_node(tree, -10);
  remove_node(tree, 1);
  remove_node(tree, 8);
  remove_node(tree, 100);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(7, tree->root->left->right->value);
  EXPECT_EQ(9, tree->root->left->right->right->value);
  EXPECT_EQ(13, tree->root->right->left->value);
  EXPECT_EQ(14, tree->root->right->left->right->value);
  EXPECT_EQ(22, tree->root->right->right->value);
  EXPECT_EQ(21, tree->root->right->right->left->value);
  EXPECT_EQ(0, tree->root->left->left->value);
}

TEST_F(BSTTest, RemovingLeftLeafJustDeletesThatLeaf) {
  insert_node(tree, 10);
  insert_node(tree, 15);
  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 9);
  insert_node(tree, 13);
  insert_node(tree, 14);
  insert_node(tree, 22);
  insert_node(tree, 21);
  insert_node(tree, 0);

  remove_node(tree, 0);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(7, tree->root->left->right->value);
  EXPECT_EQ(9, tree->root->left->right->right->value);
  EXPECT_EQ(13, tree->root->right->left->value);
  EXPECT_EQ(14, tree->root->right->left->right->value);
  EXPECT_EQ(22, tree->root->right->right->value);
  EXPECT_EQ(21, tree->root->right->right->left->value);
  EXPECT_EQ(NULL, tree->root->left->left);
}

TEST_F(BSTTest, RemovingRightLeafJustDeletesThatLeaf) {
  insert_node(tree, 10);
  insert_node(tree, 15);
  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 9);
  insert_node(tree, 13);
  insert_node(tree, 14);
  insert_node(tree, 22);
  insert_node(tree, 21);
  insert_node(tree, 0);

  remove_node(tree, 9);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(7, tree->root->left->right->value);
  EXPECT_EQ(NULL, tree->root->left->right->right);
  EXPECT_EQ(13, tree->root->right->left->value);
  EXPECT_EQ(14, tree->root->right->left->right->value);
  EXPECT_EQ(22, tree->root->right->right->value);
  EXPECT_EQ(21, tree->root->right->right->left->value);
  EXPECT_EQ(0, tree->root->left->left->value);
}

TEST_F(BSTTest, RemovingNodeWithSingleLeftChildCase1) {
  insert_node(tree, 10);
  insert_node(tree, 15);
  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 9);
  insert_node(tree, 13);
  insert_node(tree, 14);
  insert_node(tree, 22);
  insert_node(tree, 21);
  insert_node(tree, 0);

  remove_node(tree, 22);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(7, tree->root->left->right->value);
  EXPECT_EQ(13, tree->root->right->left->value);
  EXPECT_EQ(14, tree->root->right->left->right->value);
  EXPECT_EQ(21, tree->root->right->right->value);
  EXPECT_EQ(NULL, tree->root->right->right->left);
  EXPECT_EQ(0, tree->root->left->left->value);
}

TEST_F(BSTTest, RemovingNodeWithSingleLeftChildCase2) {
  insert_node(tree, 10);
  insert_node(tree, 9);
  insert_node(tree, 8);
  insert_node(tree, 7);
  insert_node(tree, 6);
  insert_node(tree, 5);
  insert_node(tree, 4);
  insert_node(tree, 3);
  insert_node(tree, 2);
  insert_node(tree, 1);

  remove_node(tree, 6);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(9, tree->root->left->value);
  EXPECT_EQ(8, tree->root->left->left->value);
  EXPECT_EQ(7, tree->root->left->left->left->value);
  EXPECT_EQ(5, tree->root->left->left->left->left->value);
  EXPECT_EQ(4, tree->root->left->left->left->left->left->left->value);
  EXPECT_EQ(3, tree->root->left->left->left->left->left->left->left->value);
  EXPECT_EQ(2, tree->root->left->left->left->left->left->left->left->left->value);
  EXPECT_EQ(1, tree->root->left->left->left->left->left->left->left->left->left->value);
  EXPECT_EQ(NULL, tree->root->left->left->left->left->left->left->left->left->left->value);
}

TEST_F(BSTTest, RemovingNodeWithSingleRightChildCase1) {
  insert_node(tree, 10);
  insert_node(tree, 15);
  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 9);
  insert_node(tree, 13);
  insert_node(tree, 14);
  insert_node(tree, 22);
  insert_node(tree, 21);
  insert_node(tree, 0);

  remove_node(tree, 13);

  EXPECT_EQ(10, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(7, tree->root->left->right->value);
  EXPECT_EQ(9, tree->root->left->right->right->value);
  EXPECT_EQ(14, tree->root->right->left->value);
  EXPECT_EQ(NULL, tree->root->right->left->right);
  EXPECT_EQ(22, tree->root->right->right->value);
  EXPECT_EQ(21, tree->root->right->right->left->value);
  EXPECT_EQ(0, tree->root->left->left->value);
}

TEST_F(BSTTest, RemovingNodeWithSingleRightChildCase2) {
  insert_node(tree, 1);
  insert_node(tree, 2);
  insert_node(tree, 3);
  insert_node(tree, 4);
  insert_node(tree, 5);
  insert_node(tree, 6);
  insert_node(tree, 7);
  insert_node(tree, 8);
  insert_node(tree, 9);
  insert_node(tree, 10);

  remove_node(tree, 3);

  EXPECT_EQ(1, tree->root->value);
  EXPECT_EQ(2, tree->root->right->value);
  EXPECT_EQ(4, tree->root->right->right->value);
  EXPECT_EQ(5, tree->root->right->right->right->value);
  EXPECT_EQ(6, tree->root->right->right->right->right->value);
  EXPECT_EQ(7, tree->root->right->right->right->right->right->value);
  EXPECT_EQ(8, tree->root->right->right->right->right->right->right->value);
  EXPECT_EQ(9, tree->root->right->right->right->right->right->right->right->value);
  EXPECT_EQ(10, tree->root->right->right->right->right->right->right->right->right->value);
  EXPECT_EQ(NULL, tree->root->right->right->right->right->right->right->right->right->right);
}

TEST_F(BSTTest, RemovingNodRightLeftRightLeftLongZigZagCase) {
  insert_node(tree, 0);
  insert_node(tree, 15);
  insert_node(tree, 1);
  insert_node(tree, 14);
  insert_node(tree, 2);
  insert_node(tree, 13);
  insert_node(tree, 3);
  insert_node(tree, 12);
  insert_node(tree, 4);
  insert_node(tree, 11);
  insert_node(tree, 5);
  insert_node(tree, 10);

  remove_node(tree, 0);

  EXPECT_EQ(15, tree->root->value);
  EXPECT_EQ(NULL, tree->root->right);
  EXPECT_EQ(1, tree->root->left->value);
  EXPECT_EQ(NULL, tree->root->left->left);
  EXPECT_EQ(14, tree->root->left->right->value);
  EXPECT_EQ(2, tree->root->left->right->left->value);
  EXPECT_EQ(NULL, tree->root->left->right->right);
  EXPECT_EQ(13, tree->root->left->right->left->right->value);
  EXPECT_EQ(3, tree->root->left->right->left->right->left->value);
  EXPECT_EQ(NULL, tree->root->left->right->left->right->right);
  EXPECT_EQ(NULL, tree->root->left->right->left->right->left->left);
  EXPECT_EQ(12, tree->root->left->right->left->right->left->right->value);
  EXPECT_EQ(4, tree->root->left->right->left->right->left->right->left->value);
  EXPECT_EQ(NULL, tree->root->left->right->left->right->left->right->right);
  EXPECT_EQ(11, tree->root->left->right->left->right->left->right->left->right->value);
  EXPECT_EQ(NULL, tree->root->left->right->left->right->left->right->left->left);
  EXPECT_EQ(5, tree->root->left->right->left->right->left->right->left->right->left->value);
  EXPECT_EQ(NULL, tree->root->left->right->left->right->left->right->left->right->right);
}

TEST_F(BSTTest, RemovingRootNodeWithTwoChildSubTrees) {
  insert_node(tree, 10);
  insert_node(tree, 15);
  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 9);
  insert_node(tree, 13);
  insert_node(tree, 14);
  insert_node(tree, 22);
  insert_node(tree, 21);
  insert_node(tree, 0);

  remove_node(tree, 10);

  EXPECT_EQ(13, tree->root->value);
  EXPECT_EQ(5, tree->root->left->value);
  EXPECT_EQ(15, tree->root->right->value);
  EXPECT_EQ(7, tree->root->left->right->value);
  EXPECT_EQ(14, tree->root->right->left->value);
  EXPECT_EQ(NULL, tree->root->right->left->right);
  EXPECT_EQ(22, tree->root->right->right->value);
  EXPECT_EQ(21, tree->root->right->right->left->value);
  EXPECT_EQ(0, tree->root->left->left->value);
}
// -------------------- Get min node tests: --------------------

TEST_F(BSTTest, GetMinFromAnEmptyTreeReturnsNull) {
  EXPECT_EQ(NULL, get_min(tree));
}

TEST_F(BSTTest, CanGetTheMinNodeFromATree) {
  struct node *nodeMinus25 = create_node(-25, NULL);

  insert_node(tree, 100);
  insert_node(tree, 40);
  insert_node(tree, 70);
  insert_node(tree, 120);
  insert_node(tree, 60);
  insert_node(tree, 20);
  insert_node(tree, -5);
  insert_node(tree, -25);

  EXPECT_TRUE(node_equals(get_min(tree), nodeMinus25));

  destroy_node(nodeMinus25);
}


// -------------------- Get max node tests: --------------------

TEST_F(BSTTest, GetMaxFromAnEmptyTreeReturnsNull) {
  EXPECT_EQ(NULL, get_max(tree));
}

TEST_F(BSTTest, CanGetTheMaxNodeFromATree) {
  struct node *node120 = create_node(120, NULL);

  insert_node(tree, 100);
  insert_node(tree, 40);
  insert_node(tree, 70);
  insert_node(tree, 120);
  insert_node(tree, 60);
  insert_node(tree, 20);
  insert_node(tree, -5);
  insert_node(tree, -25);

  EXPECT_TRUE(node_equals(get_max(tree), node120));

  destroy_node(node120);
}