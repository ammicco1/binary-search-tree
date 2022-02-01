#include "key.h"
#include "stdlib.h"

typedef struct element{
    key *chiave;
} element;

element *inizialize_element(key *chiave);

void set_element_key(element *element, key *new_key);

int get_element_key(element *element);

int compare_element(element *element_1, element *elemnent_2);

void delete_element(element *element);