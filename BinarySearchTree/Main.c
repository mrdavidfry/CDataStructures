#include <stdio.h>
#include "BST.h"

int main() {
  struct BST *tree = create_tree(50);
  insert_node(tree, 25);
  insert_node(tree, 80);
  insert_node(tree, 70);
  insert_node(tree, 90);
  insert_node(tree, 10);
  insert_node(tree, 36);

  printf("\n");
  remove_node(tree, 15);
  remove_node(tree, 36);

  printf("\n");
  printf("Min value in tree: %d\n", get_min(tree)->value);
  printf("Max value in tree: %d\n", get_max(tree)->value);

  printf("\n");
  printf("Number of values in tree: %d\n", tree->stored_nodes);
}