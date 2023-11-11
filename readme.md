# Binary Search Tree

Simple C implementation of a binary search tree. 
The tree is defined as a struct of the type: 
```c
struct bst{
    struct bst *parent;
    struct bst *left;
    struct bst *right;

    int key; 
    void *value;
} 
```

Where: 
 - parent is a pointer to the parent node
 - left is a pointer to the left child
 - right is a pointer to the right child 
 - key is an integer value
 - value can be everything. In main.c it can be a string

There are 4 basic operation: 
 - initialize, that create the bst
 - insert, to insert a new node
 - delete, to delete a node by key
 - search, to search a node by key 

Try it with: 
```bash
$ make 
$ ./main
```

Or include it in your projects. 

Enjoy :) 