#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

#include "utils/comparators.h"


typedef struct list List;

List* list(size_t el_size, comparator comp, void* ctx);
void listdes(List* l);
size_t listsize(List* l);
void  listcle(List *l); 

int listpushf(List *l, void *data);
int listpushb(List *l, void *data);
int listins(List *l, size_t i, void *data);

int listpopf(List *l, void* out);
int listremove(List *l, size_t i, void* out);

int listfind(List *l, void *data, size_t* out);
bool listempty(List *l);


#endif