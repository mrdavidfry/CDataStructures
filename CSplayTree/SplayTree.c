#include <malloc.h>
#include <assert.h>
#include "SplayTree.h"
#include <stdbool.h>
#include <string.h>
#include<stdio.h>

#define COUNT 10

/* Left rotates a subtree, about node.
   Returns the new root node of the subtree. */
struct Node *rotate_left(struct SplayTree *tree, struct Node *subtree_root) {
  assert (subtree_root != NULL);
  assert (tree != NULL);

  struct Node *new_subtree_root = subtree_root->right_node; // new root of the subtree
  struct Node *old_root_parent = subtree_root->parent_node;  // old root of the subtree

  if (!new_subtree_root) { // Cannot rotate
    return subtree_root;
  }

  subtree_root->right_node = new_subtree_root->left_node;
  if (new_subtree_root->left_node) {
    new_subtree_root->left_node->parent_node = subtree_root;
  }
  new_subtree_root->parent_node = old_root_parent;
  if (!old_root_parent) {
    tree->root_node = new_subtree_root;
  } else if (subtree_root == old_root_parent->left_node) {
    old_root_parent->left_node = new_subtree_root;
  } else {
    old_root_parent->right_node = new_subtree_root;
  }
  new_subtree_root->left_node = subtree_root;
  subtree_root->parent_node = new_subtree_root;
  return new_subtree_root;
}

/* Right rotates a subtree, about node.
   Returns the new root node of the subtree. */
struct Node *rotate_right(struct SplayTree *tree, struct Node *subtree_root) {
  assert (subtree_root != NULL);
  assert (tree != NULL);

  struct Node *new_subtree_root = subtree_root->left_node; // new root of the subtree
  struct Node *old_root_parent = subtree_root->parent_node;  // old root of the subtree
  if (!new_subtree_root) { // Cannot rotate
    return subtree_root;
  }

  subtree_root->left_node = new_subtree_root->right_node;
  if (new_subtree_root->right_node) {
    new_subtree_root->right_node->parent_node = subtree_root;
  }
  new_subtree_root->parent_node = old_root_parent;
  if (!old_root_parent) {
    tree->root_node = new_subtree_root;
  } else if (subtree_root == old_root_parent->right_node) {
    old_root_parent->right_node = new_subtree_root;
  } else {
    old_root_parent->left_node = new_subtree_root;
  }
  new_subtree_root->right_node = subtree_root;
  subtree_root->parent_node = new_subtree_root;
  return new_subtree_root;
}

/* Uses binary search to find the required position for address.
   Creates a new node and inserts the address into the tree if address
   is not already in the tree. If address is in the tree, then the
   corresponding node is splayed to the root. */
void insert(struct SplayTree *tree, unsigned int address) {
  assert (tree != NULL);
  // Insert new_node using binary search:
  struct Node *new_node = NULL;
  struct Node *cur_node = tree->root_node;
  struct Node *parent_node = NULL;
  unsigned int cur_address;
  while (cur_node) {
    cur_address = cur_node->address;
    parent_node = cur_node;
    if (address < cur_address) { // search left case
      cur_node = cur_node->left_node; // get next node
      if (!cur_node) { // create a new node case
        new_node = create_node(address, parent_node);
        if (new_node) { // check node was created successfully
          parent_node->left_node = new_node;
          tree->stored_nodes++;
        }
      }
    } else if (address > cur_address) { // search right case
      cur_node = cur_node->right_node; // get next node
      if (!cur_node) { // create a new node case
        new_node = create_node(address, parent_node);
        if (new_node) { // check node was created successfully
          parent_node->right_node = new_node;
          tree->stored_nodes++;
        }
      }
    } else {
      new_node = cur_node; // assigned to splay already existing node
      break;
    }
  }
  if (new_node) {
    splay_node(tree, new_node);
  }
}

/* Returns a ptr to the corresponding node if a given address is
   found in tree. Returns NULL otherwise.*/
struct Node *find(struct SplayTree *tree, unsigned int address) {
  if (!tree) {
    return NULL;
  }

  struct Node *cur_node = tree->root_node;
  unsigned int cur_address;
  while (cur_node) {
    cur_address = cur_node->address;
    if (address < cur_address) { // search left case
      cur_node = cur_node->left_node;
    } else if (address > cur_address) { // search right case
      cur_node = cur_node->right_node;
    } else { // found case
      return cur_node;
    }
  }
  return NULL;
}

/* Removes a given address in a tree, provided address is in tree. Returns true
   if successful, false otherwise. */
bool remove_address(struct SplayTree *tree, unsigned int address) {
  struct Node *corresponding_node = find(tree, address);
  if (!corresponding_node) { // corresponding node not found
    return false;
  }
  splay_node(tree, corresponding_node);
  struct Node *smaller_subtree = corresponding_node->left_node;
  struct Node *larger_subtree = corresponding_node->right_node;
  delete_node(corresponding_node);
  struct Node *joined_subtree_root = join(tree, smaller_subtree, larger_subtree);
  tree->root_node = joined_subtree_root;
  tree->stored_nodes--;
  return true;
}

/* PRE: All elements in the smaller_subtree MUST BE smaller
   than all elements in the larger_subtree.
   Joins two trees together and returns the root of the new tree. */
struct Node *join(struct SplayTree *tree, struct Node *smaller_subtree, struct Node *larger_subtree) {
  if (!smaller_subtree && !larger_subtree) {
    return NULL;
  } else if (!smaller_subtree) {
    larger_subtree->parent_node = NULL;
    return larger_subtree;
  } else if (!larger_subtree) {
    smaller_subtree->parent_node = NULL;
    return smaller_subtree;
  }

  struct Node *new_root = get_max(smaller_subtree);
  smaller_subtree->parent_node = NULL; // pretend smaller_subtree was the root
  splay_node(tree, new_root); // splay until 'root' reached.
  new_root->right_node = larger_subtree;
  larger_subtree->parent_node = new_root;
  return new_root;
}

/* Returns the node with the minimum address in subtree.
   Returns NULL if original subtree_node is NULL. */
struct Node *get_min(struct Node* subtree_node) {
  struct Node *prev_subtree_node = NULL;
  struct Node *cur_subtree_node = subtree_node;
  while (cur_subtree_node) {
    prev_subtree_node = cur_subtree_node;
    cur_subtree_node = cur_subtree_node->left_node;
  }
  return prev_subtree_node;
}

/* Returns the node with the maximum address in subtree.
   Returns NULL if original subtree_node is NULL. */
struct Node *get_max(struct Node* subtree_node) {
  struct Node *prev_subtree_node = NULL;
  struct Node *cur_subtree_node = subtree_node;
  while (cur_subtree_node) {
    prev_subtree_node = cur_subtree_node;
    cur_subtree_node = cur_subtree_node->right_node;
  }
  return prev_subtree_node;
}

/* Splays node to the root of the tree it is in.
   PRE: node must be in a valid tree. */
void splay_node(struct SplayTree *tree, struct Node *node) {
  assert (node != NULL);

  struct Node *cur_node = node;
  struct Node *parent_node = node->parent_node;
  struct Node *grandparent_node = NULL;

  while (parent_node) { // while node is not the root
    grandparent_node = parent_node->parent_node;
    if (node_equals(parent_node->left_node, cur_node)) { // left-sided cases
      if (!grandparent_node) { // parent is the root case
        rotate_right(tree, parent_node);
      } else if (node_equals(grandparent_node->left_node, parent_node)) { // zig-zig case
        rotate_right(tree, grandparent_node);
        rotate_right(tree, parent_node);
      } else if (node_equals(grandparent_node->right_node, parent_node)) { // zig-zag case
        rotate_right(tree, parent_node);
        rotate_left(tree, parent_node);
      } else {
        printf("1: In splay_node: Tree is not constructed correctly!\n");
        assert (false);
        return;
      }

    } else if (node_equals(parent_node->right_node, cur_node)) { // right-sided cases
      if (!grandparent_node) { // parent is the root case
        rotate_left(tree, parent_node);
      } else if (node_equals(grandparent_node->right_node, parent_node)) { // zig-zig case
        rotate_left(tree, grandparent_node);
        rotate_left(tree, parent_node);
      } else if (node_equals(grandparent_node->left_node, parent_node)) { // zig-zag case
        rotate_left(tree, parent_node);
        rotate_right(tree, parent_node);
      } else {
        printf("2: In splay_node: Tree is not constructed correctly\n");
        printf("Current Node: %d. Parent node: %d\n", cur_node->address, parent_node->address);
        assert (false);
        return;
      }

    } else {
      printf("3: In splay_node: Tree is not constructed correctly!\n");
      assert (false);
      return;
    }
    parent_node = cur_node->parent_node;
  }
}

/* Returns true if a given tree is in a zig-zig shape. False otherwise. */
bool is_zig_zig(struct Node *node, struct Node *parent, struct Node *grandparent) {
  assert (node != NULL);
  assert (parent != NULL);
  assert (grandparent != NULL);

  return (parent->left_node == node && grandparent->left_node == parent) ||
         (parent->right_node == node && grandparent->right_node == parent);
}

/* Returns true if a given tree is in a zig-zag shape. False otherwise. */
bool is_zig_zag(struct Node *node, struct Node *parent, struct Node *grandparent) {
  assert (node != NULL);
  assert (parent != NULL);
  assert (grandparent != NULL);

  return (parent->left_node == node && grandparent->right_node == parent) ||
         (parent->right_node == node && grandparent->left_node == parent);
}

/* Creates and returns a new node with the given address. */
struct Node *create_node(unsigned int address, struct Node *parent_node) {
  struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
  if (!new_node) {
    printf("In create_node: Malloc failed!\n");
    return NULL;
  }
  new_node->parent_node = parent_node;
  new_node->address = address;
  new_node->left_node = NULL;
  new_node->right_node = NULL;
  return new_node;
}

/* Creates and returns a new tree, malloced in memory, with the root node storing address. */
struct SplayTree *create_tree(unsigned int address) {
  struct SplayTree *tree = (struct SplayTree *) malloc(sizeof(struct SplayTree));
  if (!tree) {
    printf("In create_tree: Malloc failed!\n");
    return NULL;
  }
  tree->root_node = create_node(address, NULL);
  tree->stored_nodes = 1;
  return tree;
}

/* Frees the memory of a given node. */
void delete_node(struct Node *node) {
  free(node);
}

/* Recursively frees a node and all of its sub nodes. */
void delete_subtree(struct Node *subtree_node) {
  if (!subtree_node) {
    return;
  }

  struct Node *left_node = subtree_node->left_node;
  struct Node *right_node = subtree_node->right_node;

  if (left_node) {
    delete_subtree(left_node);
  }
  if (right_node) {
    delete_subtree(right_node);
  }
  delete_node(subtree_node);
}

/* Frees the memory of a tree and it's children nodes */
void delete_tree(struct SplayTree *tree) {
  assert (tree != NULL);

  delete_subtree(tree->root_node);
  free(tree);
}

unsigned int get_address(struct Node *node) {
  assert (node != NULL);

  return node->address;
}

/* Returns true if provided Node structs are equal and not NULL. False otherwise */
bool node_equals(struct Node *node_a, struct Node *node_b) {
  if (!node_a || !node_b) {
    return false;
  }

  return node_a->address == node_b->address;
}

void print_tree(struct SplayTree *tree)
{
  // Pass initial space count as 0
  print2DUtil(tree->root_node, 0);
}

void print2DUtil(struct Node *root, int space)
{
  // Base case
  if (root == NULL) {
    return;
  }

  // Increase distance between levels
  space += COUNT;

  // Process right child first
  print2DUtil(root->right_node, space);

  // Print current node after space
  // count
  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  printf("%d\n", root->address);

  // Process left child
  print2DUtil(root->left_node, space);
}