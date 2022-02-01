#include <stdlib.h>
#include <stdbool.h>

typedef struct key{
    int key;
} key;

key *inzialize_key(int chiave);

void set_key(key *chiave, int new_value);

int get_key(key *chiave);

int compare_key(key *chiave_1, key *chiave_2);

void delete_key(key *chiave);