#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stddef.h>

#include "utils/comparators.h"


typedef struct btree BTree;

// Возвращает указатель на новое дерево
BTree* btree(size_t el_size, comparator comp, void* ctx);
// Уничтожает дерево
void btreedes(BTree* t);
// Возвращает число узлов дерева
size_t btreesize(BTree* t);
// Возвращает true, если данные содержатся в дереве
bool btreecont(BTree* t, void* data);
// Вставляет значение в дерево
int btreeins(BTree* t, void* data);
// Удаляет элемент из дерева
int btreedel(BTree* t, void* data);
// Объединяет два множества, результат хранится в t1
int btreeor(BTree* t1, BTree* t2);
// Выяисляет пересечение множеств, результат хранится в t1
int btreeand(BTree* t1, BTree* t2);
// Исключающее ИЛИ для двух множеств, результат хранится в t1
int btreexor(BTree* t1, BTree* t2);
// Возвращает true, если t1 является подмножество t2
bool btreein(BTree* t1, BTree* t2);
// Итератор
int btreefor(BTree* t, void (*fn)(void*, void*), void* ctx);
// Возвращает элемент по индексу i
int btreeat(BTree* t, size_t i, void* out);
// Возвращает максимальное значение в дереве
int btreemax(BTree* t, void* out);
// Возвращает минимальное значение в дереве
int btreemin(BTree* t, void* out);
// Меняет данные деревьев местами
int btreeswp(BTree* t1, BTree* t2);
// Обнуляет дерево
int btreeclear(BTree* t);
// Возвращает указатель на клон дерева
BTree* btreeclone(BTree* t);
// Передает владение от t2 к t1, t2 обнуляется
int btreemove(BTree* t1, BTree* t2);
// Возвращает отсортированный массив из значений дерева
void* btreetoarr(BTree* t);
// Возвращает дерево, состоящее из элементов массива
BTree* btreefromarr(void* arr, size_t len, size_t el_size, comparator comp, void* ctx);
// Возвращает true, если множества совпадают
bool btreeeq(BTree* t1, BTree* t2);


#endif