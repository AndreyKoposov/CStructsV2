#include <stdint.h>
#include <string.h>

#include "structs/vector.h"

#define RESERVE_FACTOR 2


typedef struct vector {
    void   *data;
    size_t  size;
    size_t  capacity;
    size_t  elem_size;
} Vector;

static int _vec_realloc(Vector* v, size_t new_cap) {
    // Проверка входных даных
    if (!v) return -1;
    if (new_cap < v->size) return -1;
    if (new_cap == v->capacity) return 0;

    // Обнуление вектора
    if (new_cap == 0) {
        free(v->data);
        v->data = NULL;
        v->capacity = 0;

        return 0;
    }
    
    // Проверка на переполнение
    if (new_cap > SIZE_MAX / v->elem_size) return -1;

    // Расширение буфера
    void* new_data = realloc(v->data, new_cap*v->elem_size);
    if (!new_data) return -1;

    v->data = new_data;
    v->capacity = new_cap;

    return 0;
}

static inline void* _vec_elem_ptr(Vector *v, size_t i) {
    return (char *)v->data + i * v->elem_size;
}

Vector* vector(size_t elem_size) {
    if (elem_size == 0) return NULL;

    Vector* v = malloc(sizeof(Vector));
    if (!v) return NULL;

    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->elem_size = elem_size;

    return v;
}

void vecdes(Vector *v) {
    if (!v) return;
    free(v->data);
    free(v);
}

int vecres(Vector *v, size_t new_cap) {
    if (!v) return -1;
    if (new_cap == 0)
        return _vec_realloc(v, 0);

    size_t cap = v->capacity ? v->capacity : 1;

    // Увеличиваем размер вектора
    while (cap < new_cap) {
        if (cap > SIZE_MAX / v->elem_size / RESERVE_FACTOR) {
            cap = new_cap;
            break;
        }
        cap *= RESERVE_FACTOR;
    }

    return _vec_realloc(v, cap);
}

int vecshr(Vector *v) {
    if (!v) return -1;

    return _vec_realloc(v, v->size);
}

void* vecat(Vector* v, size_t i) {
    if (v->size == 0 || i >= v->size) 
        return NULL;
    else
        return _vec_elem_ptr(v, i);
}

void* vecfront(Vector* v) {
    return vecat(v, 0);
}

void* vecback(Vector* v) {
    return vecat(v, v->size-1);
}

int vecpush(Vector* v, void* el) {
    if (!v || !el) return -1;

    if (v->capacity == v->size) {
        if (vecres(v, v->size + 1) == -1) {
            return -1;
        }
    }
    memcpy(_vec_elem_ptr(v, v->size), el, v->elem_size);
    v->size++;

    return 0;
}

int vecpop(Vector* v, void* out) {
    if (!v || v->size == 0) return -1;
    if (out)
        memcpy(out, vecback(v), v->elem_size);

    v->size--;

    return 0;
}

int vecget(Vector* v, size_t i, void* out) {
    if (!v || !out || v->size == 0) return -1;

    memcpy(out, vecat(v, i), v->elem_size);

    return 0;
}

void veccle(Vector* v) {
    if (!v) return;
    v->size = 0;
}

void vecfor(Vector* v, void (*fn)(void* el, void* ctx), void* ctx) {
    if (!v || !fn) 
        return;
    for (size_t i = 0; i < v->size; i++)
        fn(_vec_elem_ptr(v, i), ctx);
}

int vecinsert(Vector* v, size_t i, const void *el) {
    if (!v || !el) return -1;
    if (i > v->size) return -1;

    if (v->capacity == v->size) {
        if (vecres(v, v->size + 1) == -1) {
            return -1;
        }
    }

    memmove(_vec_elem_ptr(v, i+1), _vec_elem_ptr(v, i), (v->size - i) * v->elem_size);
    memcpy(_vec_elem_ptr(v, i), el, v->elem_size);
    v->size++;

    return 0;
}

int vecerase(Vector* v, size_t i) {
    if (!v) return -1;
    if (i >= v->size) return -1;

    memmove(_vec_elem_ptr(v, i), _vec_elem_ptr(v, i+1), (v->size - i) * v->elem_size);
    v->size--;

    return 0;
}

int veceraser(Vector* v, size_t first, size_t last) {
    if (!v) return -1;
    if (first >= v->size || first >= last) return -1;

    memmove(_vec_elem_ptr(v, first), _vec_elem_ptr(v, last-1), (last - first) * v->elem_size);
    v->size -= last - first;

    return 0;
}

Vector* vecclone(Vector *src) {
    if (!src) return NULL;

    Vector* out = vector(src->elem_size);
    if (!out) return NULL;

    if (vecres(out, src->size) == -1) return NULL;

    memcpy(out->data, src->data, src->size * src->elem_size);
    out->size = src->size;

    return out;
}

int veccpy(Vector* dst, Vector* src) {
    if (!dst || !src) return -1;
    if (dst->elem_size != src->elem_size) return -1;
    if (src->size > dst->capacity)
        if (vecres(dst, src->size) == -1)
            return -1;

    memcpy(dst->data, src->data, src->size * src->elem_size);
    dst->size = src->size;

    return 0;
}

int vecswp(Vector* a, Vector* b) {
    if (!a || !b) return -1;

    size_t tmp_size = a->size;
    void* tmp_data = a->data;
    size_t tmp_cap = a->capacity;
    size_t tmp_el = a->elem_size;

    a->capacity = b->capacity;
    a->size = b->size;
    a->elem_size = b->elem_size;
    a->data = b->data;

    b->capacity = tmp_cap;
    b->size = tmp_size;
    b->elem_size = tmp_el;
    b->data = tmp_data;

    return 0;
}

bool vecequ(Vector* a, Vector* b, bool (*eq)(void*, void*, void* ctx), void* ctx) {
    if (!a || !b) return false;
    if (vecsize(a) != vecsize(b)) return false;
    if (a->elem_size != b->elem_size) return false;

    for (size_t i = 0; i < a->size; i++)
        if (!eq(vecat(a, i), vecat(b, i), ctx))
            return false;

    return true;
}

int vecmove(Vector* dst, Vector* src) {
    if (!dst || !src) return -1;
    if (dst->elem_size != src->elem_size) return -1;
    if (dst == src) return 0;

    free(dst->data);
    dst->data = src->data;
    dst->size = src->size;
    dst->capacity = src->capacity;

    src->size = 0;
    src->capacity = 0;
    src->data = NULL;

    return 0;
}

size_t vecsize(Vector *v) { return v->size; }
size_t veccap(Vector *v) { return v->capacity; }
bool vecemp(Vector *v) { return v->size == 0; }
