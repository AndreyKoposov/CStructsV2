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
// Возвращает уаказатель на данные в позиции i
void* listat(List *l, size_t i);
// Возвращает указатеь на данные первого элемента
void* listfront(List *l);
// Возвращает указатеь на данные поледнего элемента
void* listback(List *l);
// Записывает данные из позиции i в out
int listget(List* l, size_t i, void* out);
// Для каждого элемента применяет функцию fn
void listfor(List* l, void (*fn)(void* el, void* ctx), void* ctx);
// Удаляет элемент в позиции i из списка l
int listerase(List* l, size_t i);
// Удаляет последовательность элементов начиная с first и заканнчивая last (не включительно)
int listeraser(List* l, size_t first, size_t last);
// Возвращает указатель на новый список, склонированный на основе списка src
List* listclone(List* src);
// Копирует данные из списка src в список dst
int listcpy(List* dst, List* src);
// Меняет списки местами
int listswp(List* dst, List* src);
// Передает владение от списка src списку dst. Список src обнуляется
int listmove(List* dst, List* src);
// Возвращает true, если списки равны, false иначе
bool listeq(List* l1, List* l2, void* ctx);

#endif