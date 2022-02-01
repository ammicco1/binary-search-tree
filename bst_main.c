#include "./bst.h"
#include <stdio.h>

int main(int argc, char **argv){

    int choise, key;
    bool init = false;
    bst *tree;

    while(1){
        printf("\n---------------------------------------------\n");
        printf("WHAT DO YOU WANT TO DO?\n");
        printf("\t- 1:  INIZIALIZE A BST\n");
        printf("\t- 2:  ADD A NODE TO THE TREE\n");
        printf("\t- 3:  DELETE A NODE\n");
		printf("\t- 4:  GET THE MAX KEY\n");
        printf("\t- 5:  GET THE MIN KEY\n");
        printf("\t- 6:  NODE INCLUDED?\n");
        printf("\t- 7:  INORDER TREE WALK\n");
        printf("---------------------------------------------\n");
        printf("\nCHOISE: "); scanf("%d", &choise);

        switch(choise){
            case 1: if(!init){
						printf("\nINSERT THE FIRST KEY: "); scanf("%d", &key);
                        tree = inizialize_bst(inizialize_element(inzialize_key(key)));
                        init = true; printf("DONE!\n");
                    }else{
                        printf("THE LIST ALREADY EXISTS!\n");
                    } break;
            case 2: if(init){
						printf("\nINSERT THE NEW NODE'S KEY: "); scanf("%d", &key);
                    	tree_insert(tree, inizialize_element(inzialize_key(key)));
                    	printf("DONE!\n");
					}else{
						printf("INIZIALIZE THE LIST FIRST!\n");
					} break;
            case 3: if(init){
						printf("\nINSERT THE KEY OF THE NODE TO DELETE: "); scanf("%d", &key);
                    	tree_delete(tree, inizialize_element(inzialize_key(key)));
                    	printf("DONE!\n");
					}else{
						printf("INIZIALIZE THE LIST FIRST!\n");
					} break;
            case 4: if(init){
						printf("\nTHE MAX ELEMENT IS: %d\n", get_node_key(max(tree)));
					}else{
						printf("INIZIALIZE THE LIST FIRST!\n");
					} break;
            case 5: if(init){
						printf("\nTHE MIN ELEMENT IS: %d\n", get_node_key(min(tree)));
					}else{
						printf("INIZIALIZE THE LIST FIRST!\n");
					} break;
            case 6: if(init){
                        printf("\nINSERT THE KEY OF THE NODE YOU WANT TO SEARC: "); scanf("%d", &key);
                    	if(include_node(tree, inizialize_element(inzialize_key(key)))){
                            printf("THE NODE IS IN THE TREE\n");
                        }else{
                            printf("THE NODE ISN'T IN THE TREE\n");
                        }
                    }else{
                        printf("INIZIALIZE THE LIST FIRST!\n");
                    } break;
            case 7: if(init){
                        printf("\n");
						inorder_tree_walk(tree, "root");
                        printf("\n");
					}else{
						printf("INIZIALIZE THE LIST FIRST!\n");
					} break;
        }
    }

    return 0;
}
