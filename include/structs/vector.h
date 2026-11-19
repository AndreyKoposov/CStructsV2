#include <stdlib.h>
#include <stdbool.h>

#ifndef VECTOR_H
#define VECTOR_H


typedef struct vector Vector;

Vector* vector(size_t elem_size);
void vecdes(Vector *v);
size_t vecsize(Vector *v);
size_t veccap(Vector *v);
bool vecemp(Vector *v);
int vecres(Vector *v, size_t new_cap);
int vecshr(Vector *v);
void* vecat(Vector* v, size_t i);
void* vecfront(Vector* v);
void* vecback(Vector* v);
int vecpush(Vector* v, void* el);
int vecpop(Vector* v, void* out);
int vecget(Vector* v, size_t i, void* out);
void veccle(Vector* v);
void vecfor(Vector* v, void (*fn)(void* el, void* ctx), void* ctx);
int vecinsert(Vector* v, size_t i, const void *el);
int vecerase(Vector* v, size_t i);
int veceraser(Vector* v, size_t first, size_t last);
Vector* vecclone(Vector *src);
int veccpy(Vector* dst, Vector* src);
int vecswp(Vector* a, Vector* b);
bool vecequ(Vector* a, Vector* b, bool (*eq)(void*, void*, void* ctx), void* ctx);
int vecmove(Vector* dst, Vector* src);

#endif