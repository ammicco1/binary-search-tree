#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

int main(int argc, char **argv){
    struct bst *my_bst, *tmp;
    int choice = 0;
    int key; 
    char *buff = (char *) malloc(sizeof(char) * 256);

    printf("BINARY SEARCH TREE TESTING\n--------------------------\nInitilize the tree. First key: ");
    scanf(" %d", &key);  
    printf("First value (str): ");
    scanf(" %s", buff);

    my_bst = bst_initialize(key, buff, sizeof(char) * strlen(buff) + 1);

    while(1){
        printf("\nSelect an action:\n - 1: Insert a node\n - 2: Delete a node\n - 3: Search a node\n\n");
        scanf(" %d", &choice);

        switch(choice){
            case 1: 
                printf("Key: "); 
                scanf(" %d", &key); 
                
                printf("Value (str): "); 
                scanf(" %s", buff); 

                if(bst_search(my_bst, key)){
                    fprintf(stderr, "\nInsert error - already used key\n");
                    break;
                }
                
                if(bst_insert(my_bst, key, buff, sizeof(char) * strlen(buff) + 1) == 0){
                    printf("\nInsert ok\n");
                }else{
                    fprintf(stderr, "\nInsert error\n");
                }
                
                break;
            case 2: 
                printf("Key: ");
                scanf(" %d", &key);

                if(!bst_search(my_bst, key)){
                    fprintf(stderr, "\nDelete error - no node with this key\n");
                    break;
                }

                if(bst_delete(my_bst, key) == 0){
                    printf("\nDelete ok\n");
                }else{
                    fprintf(stderr, "\nDelete error\n");
                }

                break;
            case 3:
                printf("Key: ");
                scanf(" %d", &key);

                tmp = bst_search(my_bst, key);

                if(tmp){
                    printf("\n%d -> %s\n", tmp -> key, (char *) tmp -> value);
                }else{
                    fprintf(stderr, "\nSearch error\n");
                }

                break;
        }
    }

    return 0;
}