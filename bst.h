#include <stdlib.h>
#include <string.h>

struct bst{
    struct bst *parent;
    struct bst *left;
    struct bst *right;

    int key; 
    void *value;
};

struct bst *bst_initialize(int key, void *value, size_t value_len);

struct bst *bst_search(struct bst *root, int key); 

int bst_insert(struct bst *root, int key, void *value, size_t value_len);

int bst_delete(struct bst *root, int key);