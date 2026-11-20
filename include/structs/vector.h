#include <stdlib.h>
#include <stdbool.h>

#ifndef VECTOR_H
#define VECTOR_H


typedef struct vector Vector;

// Создает вектор с элементами размера elem_size
Vector* vector(size_t elem_size);
// Уничтожает вектор v
void vecdes(Vector *v);
// Возвращает размер вектора v
size_t vecsize(Vector *v);
// Возвращает вместимость вектора v
size_t veccap(Vector *v);
// Возвращает true, если вектор v пуст, иначе - false
bool vecemp(Vector *v);
// Резервирует память, увеличивая вместимость вектора v до new_cap
int vecres(Vector *v, size_t new_cap);
// Сжимает вместиомсть вектора v до его размера
int vecshr(Vector *v);
// Возвращает ссылку элемента в позиции i векотра v
void* vecat(Vector* v, size_t i);
// Возвращает ссылку на первый элемент вектора v
void* vecfront(Vector* v);
// Возвращает ссылку на последний элемент вектора v
void* vecback(Vector* v);
// Добавляет данные по адресу el в конец вектора v
int vecpush(Vector* v, void* el);
// Удаляет последний элемент вектора v и записывает данные по адресу out
int vecpop(Vector* v, void* out);
// Возвращает копию данных вектора v в позиции i по адресу out
int vecget(Vector* v, size_t i, void* out);
// Обнуляет вектор v
void veccle(Vector* v);
// Вызывает функцию fn с параметрами ctx для каждого элемента вектора v
void vecfor(Vector* v, void (*fn)(void* el, void* ctx), void* ctx);
// Вставляет в вектор v на позицию i данные по адресу el
int vecinsert(Vector* v, size_t i, const void *el);
// Удаляет из вектора v элемент в позиции i
int vecerase(Vector* v, size_t i);
// Удаляет из вектора v элементы, начиная с first и заканчивая last (не включительно)
int veceraser(Vector* v, size_t first, size_t last);
// Возвращает глубокую копию вектора src
Vector* vecclone(Vector *src);
// Копирует данные из вектора src в вектор dst
int veccpy(Vector* dst, Vector* src);
// Меняет вектора a и b местами
int vecswp(Vector* a, Vector* b);
// Сравнивает вектор a с вектором b используя компаратор eq с параметрами ctx
bool vecequ(Vector* a, Vector* b, bool (*eq)(void*, void*, void* ctx), void* ctx);
// Передает владение вектором src вектору dst, src обнуляется
int vecmove(Vector* dst, Vector* src);
// Возвращает максимальное значение вектора в out и его позицию в i
int vecmax(Vector* a, int (*value)(void*, void* ctx), void* ctx, int* out, size_t* i);
// Возвращает минимальное значение вектора в out и его позицию в i
int vecmin(Vector* a, int (*value)(void*, void* ctx), void* ctx, int* out, size_t* i);
// Сортирует вектор a с помощью функции value
int vecsort(Vector* a, int (*value)(void*, void* ctx), void* ctx);
// Возвращает указатель на вектор длиной len с элементами размером el_size на основании массива arr
Vector* vecfromarr(void* arr, size_t len, size_t el_size);
// Возвращает указатель на массив с данными вектора a
void* vectoarr(Vector* a);

#endif