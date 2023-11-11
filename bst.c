#include "bst.h"

struct bst *bst_initialize(int key, void *value, size_t value_len){
    struct bst *tree = (struct bst *) malloc(sizeof(struct bst));

    tree -> parent = NULL;
    tree -> left = NULL; 
    tree -> right = NULL;

    tree -> key = key;

    tree -> value = malloc(sizeof(void *) * value_len);
    memcpy(tree -> value, value, value_len);

    return tree; 
}

struct bst *bst_search(struct bst *root, int key){
    if(root == NULL || root -> key == key){
        return root;
    }else{
        if(root -> key > key){
            return bst_search(root -> left, key);
        }else{
            return bst_search(root -> right, key);
        }
    }
}

int bst_insert(struct bst *root, int key, void *value, size_t value_len){
    struct bst *tmp = NULL, *tmp2;
    struct bst *new = (struct bst *) malloc(sizeof(struct bst));

    new -> key = key; /* insert new node values */
    new -> value = malloc(sizeof(void *) * value_len);
    memcpy(new -> value, value, value_len);
    new -> left = NULL;
    new -> right = NULL;

    tmp2 = root;

    while(tmp2){
        tmp = tmp2;

        if(new -> key < tmp2 -> key){
            tmp2 = tmp2 -> left;
        }else{
            tmp2 =  tmp2 -> right;
        }
    }

    new -> parent = tmp;

    if(tmp == NULL){
        root = new;

        return 0;
    }else if(new -> key < tmp -> key){
        tmp -> left = new;

        return 0;
    }else if(new -> key > tmp -> key){
        tmp -> right = new;

        return 0;
    }

    return 1;
}

int bst_delete(struct bst *root, int key){
    struct bst *tmp = root, *tmp2;

    while(tmp && tmp -> key != key){ /* find the node to delete */
        if(tmp -> key < key){
            tmp = tmp -> right ? tmp -> right : NULL;
        }else{
            tmp = tmp -> left ? tmp -> left : NULL;
        }
    }
    
    if(!tmp){
        return 1;
    }

    if(!tmp -> left && !tmp -> right){ /* no child */        
        if(!tmp -> parent){
            root = NULL;
        }else if(tmp -> parent -> key < tmp -> key || tmp -> parent -> key == tmp -> key){
            tmp -> parent -> right = NULL; 
        }else{
            tmp -> parent -> left = NULL;
        }
    }else if(!tmp -> left && tmp -> right){ /* only right child */
        tmp -> key = tmp -> right -> key; 
        tmp -> value = tmp -> right -> value;

        tmp -> right = tmp -> right -> right;
    }else if(tmp -> left && !tmp -> right){ /* only left child */
        tmp -> key = tmp -> left -> key;
        tmp -> value = tmp -> left -> value;

        tmp -> left = tmp -> left -> left;
    }else{ /* two child */
        tmp2 = tmp -> right; 

        while(tmp2 -> left){
            tmp2 = tmp2 -> left;
        }

        tmp -> key = tmp2 -> key; 
        tmp -> value = tmp2 -> value; 

        bst_delete(tmp -> right, tmp2 -> key);
    }

    return 0;
}
