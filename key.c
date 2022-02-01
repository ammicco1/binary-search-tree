#include "key.h"

key *inzialize_key(int chiave){
    key *tmp = (key *) malloc(sizeof(key));
    tmp -> key = chiave;

    return tmp;
}

void set_key(key *chiave, int new_value){
    chiave -> key = new_value;
}

int get_key(key *chiave){
    return chiave -> key;
}

int compare_key(key *chiave_1, key *chiave_2){
    if(chiave_1 -> key > chiave_2 -> key){
        return 1;
    }else if(chiave_1 -> key < chiave_2 -> key){
        return -1;
    }else{
        return 0;
    }
}

void delete_key(key *chiave){
    free(chiave);
}
