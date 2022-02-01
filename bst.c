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

void inorder_tree_walk(bst *bst_x, char *str){
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
        
        inorder_tree_walk(bst_x -> left, "left child of");
        inorder_tree_walk(bst_x -> right, "right child of");
    }
}

bst *tree_search(bst *bst_x, key *chiave){
    if(bst_x == NULL || get_node_key(bst_x) == chiave -> key){
        return bst_x;
    }

    if(compare_key((bst_x -> elem) -> chiave, chiave) == -1){
        tree_search(bst_x -> right, chiave);
    }else{
        tree_search(bst_x -> left, chiave);
    }

    return NULL;
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

bst *tree_delete(bst *bst_x, element *elem){
    bst *succ;

    if(compare_element(elem, bst_x -> elem) == 1){
        tree_delete(bst_x -> right, elem);
    }else if(compare_element(elem, bst_x -> elem) == -1){
        tree_delete(bst_x -> left, elem);
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
            tree_delete(bst_x -> right, bst_x -> elem);
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

bool include_node(bst *bst_x, element *elem){
    bst *tmp = tree_search(bst_x, elem -> chiave);

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