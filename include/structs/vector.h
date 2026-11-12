#ifndef VECTOR_H
#define VECTOR_H


typedef struct vector Vector;

Vector* veccre(size_t elem_size);
void vecdes(Vector *v);
size_t vecsize(const Vector *v);
size_t veccap(const Vector *v);
int vecemp(const Vector *v);
int vecres(Vector *v, size_t new_cap);
int vecshr(Vector *v);
// void* vecat(Vector* v, size_t i);
// void* vecpush(Vector* v, void* el);
// void* vecfront(Vector* v);
// void* vecback(Vector* v);

#endif