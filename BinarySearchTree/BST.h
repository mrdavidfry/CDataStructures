#ifndef BINARYSEARCHTREE_BST_H
#define BINARYSEARCHTREE_BST_H

#include <stdbool.h>

struct node {
  struct node *left;
  struct node *right;
  struct node *parent;
  int value;
};

struct BST {
  struct node *root;
  int stored_nodes;
};

struct BST *create_tree();
struct node *create_node(int value, struct node *parent);

void insert_node(struct BST *tree, int value);
struct node *find_node(struct BST *tree, int value);

void remove_node(struct BST *tree, int value);

struct node *get_min(struct BST *tree);
struct node *get_max(struct BST *tree);
struct node *get_min_subtree_node(struct node *subroot);
struct node *get_max_subtree_node(struct node *subroot);

void set_left_child(struct node *parent, struct node *child);
void set_right_child(struct node *parent, struct node *child);

bool node_equals(struct node *node1, struct node *node2);
bool is_leaf_node(struct node *node);
bool has_only_left_child(struct node *node);
bool has_only_right_child(struct node *node);
bool has_two_children(struct node *node);

bool is_left_of_parent(struct node *node);
bool is_right_of_parent(struct node *node);

void destroy_node(struct node *node);
void delete_subtree(struct node *subtree_node);
void delete_tree(struct BST *tree);

#endif BINARYSEARCHTREE_BST_H