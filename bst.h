#include "./element.h"

typedef struct bst{
    struct bst *parent;
    struct bst *left, *right;
    element *elem;
} bst;

bst *inizialize_bst(element *elem);

void inorder_tree_walk(bst *bst_x, char *str);

bst *tree_search(bst *bst_x, key *chiave);

bst *max(bst *bst_x);

bst *min(bst *bst_x);

bst *successor(bst *bst_x);

bst *predecessor(bst *bst_x);

void tree_insert(bst *bst_x, element *elem);

bst *tree_delete(bst *bst_x, element *elem);

bst *get_root(bst *bst_x);

bool include_node(bst *bst_x, element *elem);

int compare_node(bst *node, bst *node2);

int get_node_key(bst *node);