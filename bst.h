#include "./element.h"
#include <stdio.h>

typedef struct bst{
    struct bst *parent;
    struct bst *left, *right;
    element *elem;
} bst;

bst *inizialize_bst(element *elem);

void preorder_tree_walk(bst *tree, char *str);

bst *tree_search(bst *tree, key *chiave);

bst *max(bst *tree);

bst *min(bst *tree);

bst *successor(bst *tree);

bst *predecessor(bst *tree);

void tree_insert(bst *tree, element *elem);

bst *tree_delete(bst *tree, key *chiave);

bst *get_root(bst *tree);

bool include_node(bst *tree, key *chiave);

int compare_node(bst *node, bst *node2);

int get_node_key(bst *node);

int height(bst *tree);

void save_tree(bst *tree, FILE *fp, int left_right);

bst *open_tree(FILE *fp);

void destroy_bst(bst *tree);