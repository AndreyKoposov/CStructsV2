#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stddef.h>

#include "utils/comparators.h"


typedef struct btree BTree;

BTree* btree(size_t el_size, comparator comp, void* ctx);
void btreedes(BTree* t);
size_t btreesize(BTree* t);
bool btreecont(BTree* t, void* data);
int btreeins(BTree* t, void* data);
int btreedel(BTree* t, void* data);
BTree* btreeclone(BTree* t);


#endif