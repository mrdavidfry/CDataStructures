#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include "SplayTree.h"

// Function declarations:
void InsertNodeAndRemoveTests ();
void RotateTreeTest ();

/*
int main() {
  printf("Tests started\n");
  InsertNodeAndRemoveTests();
  RotateTreeTest ();
}
 */

void InsertNodeAndRemoveTests () {
  struct SplayTree* tree = create_tree ();
  assert (tree->root_node == NULL);
  if (!tree) {
    printf("Tree was not created.");
    return;
  }
  insert_node(tree, 15);

  // Grandparent is NULL, add to left of parent insert case:
  insert_node(tree, 14);
  assert (tree->root_node->address == 14);
  assert (tree->root_node->right_node->address == 15);
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Zig-zig right side insert case:
  insert_node (tree, 16);
  assert (tree->root_node->address == 16);
  assert (tree->root_node->left_node->address == 15);
  assert (tree->root_node->left_node->left_node->address == 14);
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree-);

  // Zig-zig left side insert case
  insert_node (tree, 10);
  assert (tree->root_node->address == 10);
  assert (tree->root_node->left_node == NULL);
  assert (tree->root_node->right_node->address == 16);
  assert (tree->root_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->left_node->address == 14);
  assert (tree->root_node->right_node->left_node->right_node->address == 15);
  assert (tree->root_node->right_node->left_node->left_node == NULL);
  assert (tree->root_node->right_node->left_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->left_node->right_node->left_node == NULL);
  assert (tree->root_node->parent_node == NULL);

 //print_tree(tree);

  // Grandparent is NULL, add to left of parent insert case:
  insert_node (tree, 9);
  assert (tree->root_node->address == 9);
  assert (tree->root_node->right_node->address == 10);
  assert (tree->root_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->address == 16);
  assert (tree->root_node->right_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->right_node->left_node->address == 14);
  assert (tree->root_node->right_node->right_node->left_node->right_node->address == 15);
  assert (tree->root_node->right_node->right_node->left_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->left_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->right_node->left_node->right_node->left_node == NULL);
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Left then righted sided zig-zig cases:
  insert_node (tree, 11);
  assert (tree->root_node->address == 11);
  assert (tree->root_node->right_node->address == 14);
  assert (tree->root_node->right_node->right_node->address == 16);
  assert (tree->root_node->right_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->right_node->left_node->address == 15);
  assert (tree->root_node->right_node->right_node->left_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->left_node->right_node == NULL);
  assert (tree->root_node->left_node->address == 10);
  assert (tree->root_node->left_node->right_node == NULL);
  assert (tree->root_node->left_node->left_node->address == 9);
  assert (tree->root_node->left_node->left_node->right_node == NULL);
  assert (tree->root_node->left_node->left_node->left_node == NULL);
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Grandparent is NULL, add to left of parent insert case:
  insert_node (tree, 8);
  assert (tree->root_node->address == 8);
  assert (tree->root_node->left_node == NULL);
  assert (tree->root_node->right_node->address == 11);
  assert (tree->root_node->right_node->right_node->address == 14);
  assert (tree->root_node->right_node->right_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->right_node->address == 16);
  assert (tree->root_node->right_node->right_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->right_node->right_node->left_node->address == 15);
  assert (tree->root_node->right_node->right_node->right_node->left_node->right_node == NULL);
  assert (tree->root_node->right_node->right_node->right_node->left_node->left_node == NULL);
  assert (tree->root_node->right_node->left_node->address == 9);
  assert (tree->root_node->right_node->left_node->left_node == NULL);
  assert (tree->root_node->right_node->left_node->right_node->address == 10);
  assert (tree->root_node->right_node->left_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->left_node->right_node->left_node == NULL);
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Reinsert a node case:
  insert_node (tree, 16);

  assert (tree->root_node->address == 16);
  assert (tree->root_node->right_node == NULL);
  assert (tree->root_node->left_node->address == 8);
  assert (tree->root_node->left_node->left_node == NULL);
  assert (tree->root_node->left_node->right_node->address == 14);
  assert (tree->root_node->left_node->right_node->right_node->address == 15);
  assert (tree->root_node->left_node->right_node->right_node->right_node == NULL);
  assert (tree->root_node->left_node->right_node->right_node->left_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->address == 11);
  assert (tree->root_node->left_node->right_node->left_node->right_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->left_node->address == 9);
  assert (tree->root_node->left_node->right_node->left_node->left_node->left_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->left_node->right_node->address == 10);
  assert (tree->root_node->left_node->right_node->left_node->left_node->right_node->right_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->left_node->right_node->left_node == NULL);
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  printf ("-----------------------------\nInsert Node Tests All Finished!\n");

  // Remove tests:

  // Delete an address that is not in the tree case:
  remove_address(tree, 39);
  assert (tree->root_node->address == 16);
  assert (tree->root_node->right_node == NULL);
  assert (tree->root_node->left_node->address == 8);
  assert (tree->root_node->left_node->left_node == NULL);
  assert (tree->root_node->left_node->right_node->address == 14);
  assert (tree->root_node->left_node->right_node->right_node->address == 15);
  assert (tree->root_node->left_node->right_node->right_node->right_node == NULL);
  assert (tree->root_node->left_node->right_node->right_node->left_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->address == 11);
  assert (tree->root_node->left_node->right_node->left_node->right_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->left_node->address == 9);
  assert (tree->root_node->left_node->right_node->left_node->left_node->left_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->left_node->right_node->address == 10);
  assert (tree->root_node->left_node->right_node->left_node->left_node->right_node->right_node == NULL);
  assert (tree->root_node->left_node->right_node->left_node->left_node->right_node->left_node == NULL);
  assert (tree->root_node->parent_node == NULL);

  // Delete leaf node case:
  int num_stored_addresses = tree->stored_nodes;
  remove_address(tree, 10);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check only one node was removed
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Delete root node case:
  num_stored_addresses = tree->stored_nodes;
  remove_address(tree, 9);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check only one node was removed
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Delete intemidiate node case:
  num_stored_addresses = tree->stored_nodes;
  remove_address(tree, 11);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check only one node was removed
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Delete a root node, where left child is NULL case:
  num_stored_addresses = tree->stored_nodes;
  remove_address(tree, 8);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check only one node was removed
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Delete a root node, where right child is NULL case:
  num_stored_addresses = tree->stored_nodes;
  remove_address(tree, 16);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check only one node was removed
  assert (tree->root_node->parent_node == NULL);
  assert (tree->root_node->left_node == NULL);
  assert (tree->root_node->right_node->address == 15);
  assert (tree->root_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->left_node == NULL);

  //print_tree(tree);

  // Delete a child node of root, where right child  of child is NULL case:
  num_stored_addresses = tree->stored_nodes;
  remove_address(tree, 14);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check only one node was removed
  assert (tree->root_node->parent_node == NULL);

  //print_tree(tree);

  // Remove last node case:
  num_stored_addresses = tree->stored_nodes;
  remove_address(tree, 15);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check only one node was removed
  assert (tree->root_node == NULL);

  // Remove a node from an empty tree:
  remove_address(tree, 4);
  assert (tree->stored_nodes == num_stored_addresses - 1); // check no nodes deleted

  printf ("-----------------------------\nRemove Node Tests All Finished!\n");
  delete_tree (tree);
}

void RotateTreeTest () {
  printf("-----------------------------\nRotated tests started\n");
  struct SplayTree* tree = create_tree ();
  if (!tree) {
    printf("Tree was not created.");
    return;
  }
  insert_node(tree, 15);
  // Single node in tree rotate left case:
  struct Node *new_root = rotate_left(tree, tree->root_node);
  assert (new_root->address == 15);
  assert (tree->root_node->address == 15);
  assert (tree->root_node->parent_node == NULL);

  // Single node in tree rotate right case:
  new_root = rotate_left(tree, tree->root_node);
  assert (new_root->address == 15);
  assert (tree->root_node->address == 15);
  assert (new_root->parent_node == NULL);

  insert_node (tree, 14);
  assert (tree->root_node->address == 14);
  assert (tree->root_node->right_node->address == 15);
  assert (tree->root_node->parent_node == NULL);

  // Check tree has initially been built correctly:
  insert_node (tree, 16);
  assert (tree->root_node->address == 16);
  assert (tree->root_node->right_node == NULL);
  assert (tree->root_node->left_node->address == 15);
  assert (tree->root_node->left_node->right_node == NULL);
  assert (tree->root_node->left_node->left_node->address == 14);

  // Cannot rotate left case:
  new_root = rotate_left(tree, tree->root_node);
  assert (tree->root_node->address == 16);
  assert (new_root->address == 16);
  assert (tree->root_node->right_node == NULL);
  assert (tree->root_node->left_node->address == 15);
  assert (tree->root_node->left_node->right_node == NULL);
  assert (tree->root_node->left_node->left_node->address == 14);
  assert (new_root->parent_node == NULL);

  // Ziz-zig rotate right case:
  new_root = rotate_right (tree, tree->root_node);
  assert (tree->root_node->address == 15);
  assert (new_root->address == 15);
  assert (new_root->left_node->address == 14);
  assert (new_root->right_node->address == 16);
  assert (new_root->parent_node == NULL);

  // Tree depth of 2 rotate right case:
  new_root = rotate_right (tree, tree->root_node);
  assert (tree->root_node->address == 14);
  assert (new_root->address == 14);
  assert (tree->root_node->left_node == NULL);
  assert (tree->root_node->right_node->address == 15);
  assert (tree->root_node->right_node->right_node->address == 16);
  assert (tree->root_node->right_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->right_node->left_node == NULL);
  assert (new_root->parent_node == NULL);

  // Cannot rotate right case:
  new_root = rotate_right (tree, tree->root_node);
  assert (tree->root_node->address == 14);
  assert (new_root->address == 14);
  assert (tree->root_node->left_node == NULL);
  assert (tree->root_node->right_node->address == 15);
  assert (tree->root_node->right_node->right_node->address == 16);
  assert (tree->root_node->right_node->left_node == NULL);
  assert (tree->root_node->right_node->right_node->right_node == NULL);
  assert (tree->root_node->right_node->right_node->left_node == NULL);
  assert (new_root->parent_node == NULL);

  printf ("-----------------------------\nRotate Tests All Finished!\n");
  delete_tree (tree);
}

