#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

#include "utils/comparators.h"


typedef struct list List;

// Возвращает указатель на список
List* list(size_t el_size, comparator comp, void* ctx);
// Уничтожает список освобождая память
void listdes(List* l);
// Возвращает размер списка
size_t listsize(List* l);
// Обнуляет список
void  listcle(List *l); 
// Добавляет элемент в начало списка
int listpushf(List *l, void *data);
// Добавляет элемент в конец списка
int listpushb(List *l, void *data);
// Добавляет элемент в позицию i
int listins(List *l, size_t i, void *data);
// Удаляет первый элемент и возвращает его данные
int listpopf(List *l, void* out);
// Удаляет элемент из позиции i
int listremove(List *l, size_t i, void* out);
// Возвращает 0 при успешном нахождении и -1 при неудаче. Записывает позицию первого найденного элемента в out
int listfind(List *l, void *data, size_t* out);
// Возвращает true, если список пуст
bool listempty(List *l);

void* listat(List *l, size_t i);
void* listfront(List *l);
void* listback(List *l);


#endif