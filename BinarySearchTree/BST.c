#include "BST.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

/* Returns a new malloc-ed BST with the root node storing value. */
struct BST *create_tree(int value) {
  struct BST *tree = (struct BST *) malloc(sizeof(struct BST));
  if (!tree) {
    printf("In create_tree: Malloc failed!\n");
    return NULL;
  }
  tree->root = create_node(value, NULL);
  tree->stored_nodes = 1;
  return tree;
}

/* Returns a new malloc-ed node, given a value. */
struct node *create_node(int value, struct node *parent) {
  struct node *node = (struct node *) malloc(sizeof(struct node));
  if (!node) {
    printf("In create_node: Malloc failed!\n");
  }
  node->left = NULL;
  node->right = NULL;
  node->parent = parent;
  node->value = value;
}

/* Inserts a given value into a given binary search tree, BST.
 * PRE: tree != NULL. */
void insert_node(struct BST *tree, int value) {
  assert(tree != NULL);

  struct node *cur = tree->root;

  if (!cur) { // if no root node existed
    tree->root = create_node(value, NULL);
  }

  struct node *new_node;
  struct node *prev;
  int cur_node_value;
  while (cur) {
    prev = cur;
    cur_node_value = cur->value;
    if (value < cur_node_value) { // search left case
      cur = cur->left;
      if (!cur) {
        new_node = create_node(value, prev);
        set_left_child(prev, new_node);
        tree->stored_nodes++;
        printf("Node inserted, value: %d, parent: %d\n", new_node->value, prev->value);
      }
    } else if (value > cur_node_value) { // search right case
      cur = cur->right;
      if (!cur) {
        new_node = create_node(value, prev);
        set_right_child(prev, new_node);
        tree->stored_nodes++;
        printf("Node inserted, value: %d, parent: %d\n", new_node->value, prev->value);
      }
    } else { // found node already

    }
  }
}

/* Returns the corresponding tree node if value is found.
 * Otherwise, returns NULL.
 * PRE: tree != NULL. */
struct node *find_node(struct BST *tree, int value) {
  assert(tree != NULL);

  struct node *cur = tree->root;
  int cur_node_value;
  while (cur) {
    cur_node_value = cur->value;
    if (value < cur_node_value) { // search left case
      cur = cur->left;
    } else if (value > cur_node_value) { // search right case
      cur = cur->right;
    } else { // found node case
      return cur;
    }
  }
  return NULL;
}

/* Removes the value from the tree if value is in the tree.
 * PRE: tree != NULL. */
void remove_node(struct BST *tree, int value) {
  assert (tree != NULL);

  struct node *node = find_node(tree, value);
  if (!node) { // value not found
    printf("Node with value: %d not found!\n", value);
    return;
  }

  if (is_leaf_node(node)) {
    if (is_left_of_parent(node)) {
      node->parent->left = NULL;
    } else { // right of parent case
      node->parent->right = NULL;
    }
  } else if (has_only_left_child(node)) {
    if (is_left_of_parent(node)) {
      node->parent->left = node->left;
    } else { // right of parent case
      node->parent->right = node->left;
    }
  } else if (has_only_right_child(node)) {
    if (is_left_of_parent(node)) {
      node->parent->left = node->right;
    } else { // right of parent case
      node->parent->right = node->right;
    }
  } else { // has two children case
    struct node *new_sub_root = get_min_subtree_node(node->right);
    struct node *left_sub_root = node->left;
    struct node *right_sub_root = node->right;
    set_left_child(new_sub_root, left_sub_root);
    set_right_child(new_sub_root, right_sub_root);
  }
  destroy_node(node);
  tree->stored_nodes--;
  printf("Node deleted!\n");
}

/* Returns the minimum node in a given tree.
 * Returns NULL if tree or root node is NULL. */
struct node *get_min(struct BST *tree) {
  if (!tree) {
    return NULL;
  }

  return get_min_subtree_node(tree->root);
}

/* Returns the maximum node in a given tree.
 * Returns NULL if tree or root node is NULL. */
struct node *get_max(struct BST *tree) {
  if (!tree) {
    return NULL;
  }

  return get_max_subtree_node(tree->root);
}

/* Returns the minimum node in the subtree, starting at the given subroot.
 * Returns NULL if subroot is NULL. */
struct node *get_min_subtree_node(struct node *subroot) {
  if (!subroot) {
    return NULL;
  }

  struct node *cur = subroot;
  while (cur->left) {
    cur = cur->left;
  }
  return cur;
}

/* Returns the maximum node in the subtree, starting at the given subroot.
 * Returns NULL if subroot is NULL. */
struct node *get_max_subtree_node(struct node *subroot) {
  if (!subroot) {
    return NULL;
  }

  struct node *cur = subroot;
  while (cur->right) {
    cur = cur->right;
  }
  return cur;
}

void set_left_child(struct node *parent, struct node *child) {
  parent->left = child;
  child->parent = parent;
}

void set_right_child(struct node *parent, struct node *child) {
  parent->right = child;
  child->parent = parent;
}

/* Node equality function. Returns false if node1 or node2 == NULL*/
bool node_equals(struct node *node1, struct node *node2) {
  if (node1 == NULL || node2 == NULL) {
    return false;
  }
  return node1->value == node2->value;
}

/* Returns true if node is a leaf node. False otherwise.
 * PRE: node != NULL. */
bool is_leaf_node(struct node *node) {
  assert (node != NULL);

  return node->left == NULL && node->right == NULL;
}

/* Returns true if node has only got a left child. False otherwise.
 * PRE: node != NULL. */
bool has_only_left_child(struct node *node) {
  assert (node != NULL);

  return node->left != NULL && node->right == NULL;
}

/* Returns true if node has only got a right child. False otherwise.
 * PRE: node != NULL. */
bool has_only_right_child(struct node *node) {
  assert (node != NULL);

  return node->left == NULL && node->right != NULL;
}

/* Returns true if node has two children. False otherwise.
 * PRE: node != NULL. */
bool has_two_children(struct node *node) {
  assert (node != NULL);

  return node->left != NULL && node->right != NULL;
}

/* Returns true if node is the left child of its parent node.
 * If parent node doesn't exist, returns false. Returns false in
 * all other cases.
 * PRE: node != NULL. */
bool is_left_of_parent(struct node *node) {
  assert (node != NULL);

  struct node *parent = node->parent;
  return parent && node_equals(node, parent->left);
}

/* Returns true if node is the right child of its parent node.
 * If parent node doesn't exist, returns false. Returns false in
 * all other cases.
 * PRE: node != NULL. */
bool is_right_of_parent(struct node *node) {
  assert (node != NULL);

  struct node *parent = node->parent;
  return parent && node_equals(node, parent->right);
}

/* Destroys a node and frees its memory.
 * PRE: node != NULL. */
void destroy_node(struct node *node) {
  assert (node != NULL);

  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  free (node);
}

/* Recursively frees a node and all of its sub nodes. */
void delete_subtree(struct node *subtree_node) {
  if (!subtree_node) {
    return;
  }

  struct node *left_node = subtree_node->left;
  struct node *right_node = subtree_node->right;

  if (left_node) {
    delete_subtree(left_node);
  }
  if (right_node) {
    delete_subtree(right_node);
  }
  destroy_node(subtree_node);
}

/* Frees the memory of a tree and it's children nodes.
 * PRE: tree != NULL. */
void delete_tree(struct BST *tree) {
  assert (tree != NULL);

  delete_subtree(tree->root);
  free(tree);
}


