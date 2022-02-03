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

void preorder_tree_walk(bst *bst_x, char *str){
    int par; 
    bst *tmp; 
    if(bst_x != NULL){
        tmp = bst_x -> parent;
        if(tmp == NULL){
            par = -1;
        }else{
            par = get_node_key(tmp);
        }

        if(par == -1){
            printf("node: %d %s\n", get_element_key(bst_x -> elem), str);
        }else{
            printf("node: %d %s %d\n", get_element_key(bst_x -> elem), str, par);
        }
        
        preorder_tree_walk(bst_x -> left, "left child of");
        preorder_tree_walk(bst_x -> right, "right child of");
    }
}

bst *tree_search(bst *bst_x, key *chiave){
    if(bst_x == NULL || get_node_key(bst_x) == chiave -> key){
        return bst_x;
    }else{
        if(compare_key((bst_x -> elem) -> chiave, chiave) == -1){
            return tree_search(bst_x -> right, chiave);
        }else{
            return tree_search(bst_x -> left, chiave);
        }
    }
}

bst *min(bst *bst_x){
    while(bst_x -> left != NULL){
        bst_x = bst_x -> left;
    } 

    return bst_x;
}

bst *max(bst *bst_x){
    while(bst_x -> right != NULL){
        bst_x = bst_x -> right;
    } 

    return bst_x;
}

bst *successor(bst *bst_x){
    bst *tmp; 

    if(bst_x -> right != NULL){
        return min(bst_x -> right);
    }

    tmp = bst_x -> parent;

    while(tmp != NULL && bst_x == tmp -> right){
        bst_x = tmp;
        tmp = bst_x -> parent;
    }

    return tmp;
}

bst *predecessor(bst *bst_x){
    bst *tmp; 

    if(bst_x -> left != NULL){
        return min(bst_x -> left);
    }

    tmp = bst_x -> parent;

    while(tmp != NULL && bst_x == tmp -> left){
        bst_x = tmp;
        tmp = bst_x -> parent;
    }

    return tmp;
}

void tree_insert(bst *bst_x, element *elem){
    bst *root = bst_x;
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
        bst_x = ins;
    }else if(compare_node(ins, tmp) == -1){
        tmp -> left = ins;
    }else{
        tmp -> right = ins;
    }
}

bst *tree_delete(bst *bst_x, key *chiave){
    bst *succ;

    if(compare_key(chiave, bst_x -> elem -> chiave) == 1){
        tree_delete(bst_x -> right, chiave);
    }else if(compare_key(chiave, bst_x -> elem -> chiave) == -1){
        tree_delete(bst_x -> left, chiave);
    }else{
        if(!bst_x -> right && !bst_x -> left && !bst_x -> parent){
            return NULL;
        }else if(!bst_x -> right && !bst_x -> left){
            if(bst_x -> parent -> left && compare_node(bst_x -> parent -> left, bst_x) == 0){
                bst_x -> parent -> left = NULL;
            }else if(bst_x -> parent -> right && compare_node(bst_x -> parent -> right, bst_x) == 0){
                bst_x -> parent -> right = NULL;
            }
        }else if(!bst_x -> right && bst_x -> left){
            if(bst_x -> parent -> left && compare_node(bst_x -> parent -> left, bst_x) == 0){
                bst_x -> parent -> left = bst_x -> left;
                bst_x -> left -> parent = bst_x -> parent;
            }else if(bst_x -> parent -> right && compare_node(bst_x -> parent -> right, bst_x) == 0){
                bst_x -> parent -> right = bst_x -> left;
                bst_x -> left -> parent = bst_x -> parent;
            }
        }else if(bst_x -> right && !bst_x -> left){
            if(bst_x -> parent -> left && compare_node(bst_x -> parent -> left, bst_x) == 0){
                bst_x -> parent -> left = bst_x -> right;
                bst_x -> right -> parent = bst_x -> parent;
            }else if(bst_x -> parent -> right && compare_node(bst_x -> parent -> right, bst_x) == 0){
                bst_x -> parent -> right = bst_x -> right;
                bst_x -> right -> parent = bst_x -> parent;
            }
        }else{
            succ = successor(bst_x);
            bst_x -> elem = succ -> elem;
            tree_delete(bst_x -> right, bst_x -> elem -> chiave);  
        }
    }

    return get_root(bst_x);
}

bst *get_root(bst *bst_x){
    if(bst_x -> parent){
        get_root(bst_x -> parent);
    }else{
        return bst_x;
    }

    return NULL;
}

bool include_node(bst *bst_x, key *chiave){
    bst *tmp = tree_search(bst_x, chiave);

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

int height(bst *bst_x){
    int rh = 0, lh = 0;

    if(!bst_x){
        return 0;
    }else{
        lh = height(bst_x -> left);
        rh = height(bst_x -> right);

        return lh > rh ? lh + 1 : rh + 1;
    }
}

/*
    this function saves a tree in a file. every node is rappresented by 3 number: 
     - node key.
     - parent key. the root has -1.
     - an int that represent if the node is a left child (-1) or a right child (1). the root has 0.

    in this case the element of a node is the key, so i save only the key.


    the firt time i call the function i call it with "w" as mod, in this way i overwrite old files, the recursive calls are invocated with "a",
    and also i call the function with "left_right" = 0.
*/

void save_tree(bst *bst_x, char *file_path, char *mod, int left_right){
    FILE *fp = fopen(file_path, mod);

    if(bst_x -> parent){
        fprintf(fp, "%d %d %d\n", get_node_key(bst_x), get_node_key(bst_x -> parent), left_right);
    }else{
        fprintf(fp, "%d -1 0\n", get_node_key(bst_x));
    }

    if(bst_x -> right && bst_x -> left){
        save_tree(bst_x -> left, file_path, "a", -1);
        save_tree(bst_x -> right, file_path, "a", 1);
    }else if(bst_x -> right && !bst_x -> left){
        save_tree(bst_x -> right, file_path, "a", 1);
    }else if(bst_x -> left && !bst_x -> right){
        save_tree(bst_x -> left, file_path, "a", -1);
    }
}

/*
    this function open a bst from a file where you have previously saved an old bst with the function "save_tree"
*/

bst *open_tree(char *file_path){
    int n, node, parent, lr, i = 0;
    int *keys, *parents, *left_right;
    char ch;
    FILE *fp = fopen(file_path, "r");
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

    i = 0;

    do{
        if(parents[i] == -1){
            tree = inizialize_bst(inizialize_element(inizialize_key(keys[i])));
        }
        i++;
    }while(parents[i] != -1);

    for(i = 0; i < n; i++){
        if(parents[i] != -1){
            tree_insert(tree, inizialize_element(inizialize_key(keys[i])));
        }
    }

    return tree;
}