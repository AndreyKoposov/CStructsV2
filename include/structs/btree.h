#ifndef BTREE_H
#define BTREE_H

#include <stddef.h>


typedef struct btree BTree;

typedef int (*comparator)(void* d1, void* d2, void* ctx);

BTree* btree(size_t el_size, comparator comp, void* ctx);
void btreedes(BTree* t);
size_t btreesize(BTree* t);
void* btreesrch(BTree* t, void* data);
int btreeins(BTree* t, void* data);


int comparator_int(void* d1, void* d2, void* ctx);


#endif