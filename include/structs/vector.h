#include <stdlib.h>
#include <stdbool.h>

#ifndef VECTOR_H
#define VECTOR_H


typedef struct vector Vector;

Vector* vector(size_t elem_size);
void vecdes(Vector *v);
size_t vecsize(const Vector *v);
size_t veccap(const Vector *v);
bool vecemp(const Vector *v);
int vecres(Vector *v, size_t new_cap);
int vecshr(Vector *v);
void* vecat(const Vector* v, size_t i);
void* vecfront(const Vector* v);
void* vecback(const Vector* v);
int vecpush(Vector* v, void* el);
int vecpop(Vector* v, void* out);
int vecget(const Vector* v, size_t i, void* out);
void veccle(Vector* v);
void vecfor(Vector* v, void (*fn)(void* el, void* ctx), void* ctx);

#endif