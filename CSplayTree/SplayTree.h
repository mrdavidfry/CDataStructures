#include <stdbool.h>
// Frame table: Use an array

// Splay trees are good for caching
// We make the node we are looking for the root node

struct Node
  {
    struct Node *left_node;
    struct Node *right_node;
    struct Node *parent_node;
    unsigned int address;
  };

struct SplayTree
  {
    struct Node *root_node;
    unsigned int stored_nodes; /* Used to check if size has exceeded number
                                  of addresses that can be stored. */
  };

struct Node *rotate_left (struct SplayTree *tree, struct Node *subtree_root);
struct Node *rotate_right (struct SplayTree *tree, struct Node *subtree_root);

void insert (struct SplayTree *tree, unsigned int address);
struct Node *find(struct SplayTree *tree, unsigned int address);
bool remove_address(struct SplayTree *tree, unsigned int address);
struct Node *join(struct SplayTree *tree, struct Node *smaller_subtree, struct Node *larger_subtree);

struct Node *get_min(struct Node* subtree_node);
struct Node *get_max(struct Node* subtree_node);

struct SplayTree *create_tree (unsigned int address);
struct Node *create_node (unsigned int address, struct Node *parent_node);

void splay_node (struct SplayTree *tree, struct Node *node);

bool is_zig_zig (struct Node *node, struct Node *parent, struct Node *grandparent);
bool is_zig_zag (struct Node *node, struct Node *parent, struct Node *grandparent);

void delete_node(struct Node *node);
void delete_subtree(struct Node *subtree_node);
void delete_tree (struct SplayTree * tree);

unsigned int get_address (struct Node *node);

bool node_equals(struct Node *node_a, struct Node *node_b);

void print_tree(struct SplayTree *tree);
void print2DUtil(struct Node *root, int space);