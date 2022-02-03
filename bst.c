#include "./bst.h"
#include <stdio.h>

bst *inizialize_bst(element *elem){
    bst *tmp = (bst *) malloc(sizeof(bst));

    tmp -> elem = elem;
    tmp -> parent = NULL;
    tmp -> left = NULL;
    tmp -> right = NULL;

    return tmp;
}

void preorder_tree_walk(bst *tree, char *str){
    int par; 
    bst *tmp; 
    if(tree != NULL){
        tmp = tree -> parent;
        if(tmp == NULL){
            par = -1;
        }else{
            par = get_node_key(tmp);
        }

        if(par == -1){
            printf("node: %d %s\n", get_element_key(tree -> elem), str);
        }else{
            printf("node: %d %s %d\n", get_element_key(tree -> elem), str, par);
        }
        
        preorder_tree_walk(tree -> left, "left child of");
        preorder_tree_walk(tree -> right, "right child of");
    }
}

bst *tree_search(bst *tree, key *chiave){
    if(tree == NULL || get_node_key(tree) == chiave -> key){
        return tree;
    }else{
        if(compare_key((tree -> elem) -> chiave, chiave) == -1){
            return tree_search(tree -> right, chiave);
        }else{
            return tree_search(tree -> left, chiave);
        }
    }
}

bst *min(bst *tree){
    while(tree -> left != NULL){
        tree = tree -> left;
    } 

    return tree;
}

bst *max(bst *tree){
    while(tree -> right != NULL){
        tree = tree -> right;
    } 

    return tree;
}

bst *successor(bst *tree){
    bst *tmp; 

    if(tree -> right != NULL){
        return min(tree -> right);
    }

    tmp = tree -> parent;

    while(tmp != NULL && tree == tmp -> right){
        tree = tmp;
        tmp = tree -> parent;
    }

    return tmp;
}

bst *predecessor(bst *tree){
    bst *tmp; 

    if(tree -> left != NULL){
        return min(tree -> left);
    }

    tmp = tree -> parent;

    while(tmp != NULL && tree == tmp -> left){
        tree = tmp;
        tmp = tree -> parent;
    }

    return tmp;
}

void tree_insert(bst *tree, element *elem){
    bst *root = tree;
    bst *tmp = NULL;
    bst *ins = (bst *) malloc(sizeof(bst));

    ins -> elem = elem;
    ins -> left = NULL;
    ins -> right = NULL;

    while(root != NULL){
        tmp = root;
        
        if(compare_node(ins, root) == -1){
            root = root -> left;
        }else{
            root =  root -> right;
        }
    }

    ins -> parent = tmp;

    if(tmp == NULL){
        tree = ins;
    }else if(compare_node(ins, tmp) == -1){
        tmp -> left = ins;
    }else{
        tmp -> right = ins;
    }
}

bst *tree_delete(bst *tree, key *chiave){
    bst *succ;

    if(compare_key(chiave, tree -> elem -> chiave) == 1){
        tree_delete(tree -> right, chiave);
    }else if(compare_key(chiave, tree -> elem -> chiave) == -1){
        tree_delete(tree -> left, chiave);
    }else{
        if(!tree -> right && !tree -> left && !tree -> parent){
            return NULL;
        }else if(!tree -> right && !tree -> left){
            if(tree -> parent -> left && compare_node(tree -> parent -> left, tree) == 0){
                tree -> parent -> left = NULL;
            }else if(tree -> parent -> right && compare_node(tree -> parent -> right, tree) == 0){
                tree -> parent -> right = NULL;
            }
        }else if(!tree -> right && tree -> left){
            if(tree -> parent -> left && compare_node(tree -> parent -> left, tree) == 0){
                tree -> parent -> left = tree -> left;
                tree -> left -> parent = tree -> parent;
            }else if(tree -> parent -> right && compare_node(tree -> parent -> right, tree) == 0){
                tree -> parent -> right = tree -> left;
                tree -> left -> parent = tree -> parent;
            }
        }else if(tree -> right && !tree -> left){
            if(tree -> parent -> left && compare_node(tree -> parent -> left, tree) == 0){
                tree -> parent -> left = tree -> right;
                tree -> right -> parent = tree -> parent;
            }else if(tree -> parent -> right && compare_node(tree -> parent -> right, tree) == 0){
                tree -> parent -> right = tree -> right;
                tree -> right -> parent = tree -> parent;
            }
        }else{
            succ = successor(tree);
            tree -> elem = succ -> elem;
            tree_delete(tree -> right, tree -> elem -> chiave);  
        }
    }

    return get_root(tree);
}

bst *get_root(bst *tree){
    if(tree -> parent){
        get_root(tree -> parent);
    }else{
        return tree;
    }

    return NULL;
}

bool include_node(bst *tree, key *chiave){
    bst *tmp = tree_search(tree, chiave);

    if(tmp){
        return true;
    }else{
        return false;
    }
}

int compare_node(bst *node, bst *node2){
    return compare_element(node -> elem, node2 -> elem);
}

int get_node_key(bst *node){
    return get_element_key(node -> elem);
}

int height(bst *tree){
    int rh = 0, lh = 0;

    if(!tree){
        return 0;
    }else{
        lh = height(tree -> left);
        rh = height(tree -> right);

        return lh > rh ? lh + 1 : rh + 1;
    }
}

/*
    this function saves a tree in a file. every node is rappresented by 3 number: 
     - node key.
     - parent key. the root has -1.
     - an int that represent if the node is a left child (-1) or a right child (1). the root has 0.

    in this case the element of a node is the key, so i save only the key.


    you have to open your file with "a" mode, so if the file is not empty remember to clear it first!
    and also call the function with "left_right" = 0.
*/

void save_tree(bst *tree, FILE *fp, int left_right){
    if(fp){
        if(tree -> parent){
            fprintf(fp, "%d %d %d\n", get_node_key(tree), get_node_key(tree -> parent), left_right);
        }else{
            fprintf(fp, "%d -1 0\n", get_node_key(tree));
        }

        if(tree -> right && tree -> left){
            save_tree(tree -> left, fp, -1);
            save_tree(tree -> right, fp, 1);
        }else if(tree -> right && !tree -> left){
            save_tree(tree -> right, fp, 1);
        }else if(tree -> left && !tree -> right){
            save_tree(tree -> left, fp, -1);
        }
    }else{
        printf("FILE ERROR!");
    }
}

/*
    this function open a bst from a file where you have previously saved an old bst with the function "save_tree"
*/

bst *open_tree(FILE *fp){
    int n, node, parent, lr, i = 0;
    int *keys, *parents, *left_right;
    char ch;
    bst *tree;

    if(!fp){
        return NULL;
    }

    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            n++;
        }
    }

    keys = malloc(sizeof(int) * n);
    parents = malloc(sizeof(int) * n);
    left_right = malloc(sizeof(int) * n);

    rewind(fp);

    while(!feof(fp)){
        fscanf(fp, "%d %d %d", &node, &parent, &lr);
        keys[i] = node;
        parents[i] = parent;
        left_right[i] = lr;
        i++;
    }
    
    for(i = 0; i < n; i++){
        if(parents[i] == -1){
            tree = inizialize_bst(inizialize_element(inizialize_key(keys[i])));
            break;
        }
    }

    for(i = 0; i < n; i++){
        if(parents[i] != -1){
            tree_insert(tree, inizialize_element(inizialize_key(keys[i])));
        }
    }

    return tree;
}

void destroy_bst(bst *tree){
    bst *tmp_l, *tmp_r; 
    if(tree != NULL){
        tmp_l = tree -> left; 
        tmp_r = tree -> right;

        free(tree);

        destroy_bst(tmp_l);
        destroy_bst(tmp_r);
    }
}