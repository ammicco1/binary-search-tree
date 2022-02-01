#include "element.h"

element *inizialize_element(key *chiave){
    element *tmp = (element *) malloc(sizeof(element));
    tmp -> chiave = chiave;

    return tmp;
}

void set_element_key(element *element, key *new_key){
    element -> chiave = new_key;
}

int get_element_key(element *element){
    return get_key(element -> chiave);
}

int compare_element(element *element_1, element *elemnent_2){
    return compare_key(element_1 -> chiave, elemnent_2 -> chiave);
}

void delete_element(element *element){
    delete_key(element -> chiave);
    free(element);
}