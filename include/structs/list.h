#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>


typedef struct list List;

List* list(size_t el_size);
void listdes(List* l);
size_t listsize(List* l);
void  listcle(List *l); 

int listpushf(List *l, void *data);
int listpushb(List *l, void *data);
int listins(List *l, size_t i, void *data);

int listpopf(List *l, void* data);
int listpopb(List *l, void* data);
int listremove(List *l, size_t i, void* data);

int listfind(List *l, void *data);
bool listcont(List *l, void *data);
bool listempty(List *l);


#endif