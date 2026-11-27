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

int btreeor(BTree* t1, BTree* t2);
int btreeand(BTree* t1, BTree* t2);
bool btreein(BTree* t1, BTree* t2);
bool btreexor(BTree* t1, BTree* t2);

int btreefor(BTree* t, void (*fn)(void*, void*), void* ctx);
int btreeat(BTree* t, size_t i, void* out);
int btreemax(BTree* t, void* out);
int btreemin(BTree* t, void* out);

int btreeswp(BTree* t1, BTree* t2);
int btreeclear(BTree* t);
BTree* btreeclone(BTree* t);


#endif