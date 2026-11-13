#include <stdint.h>

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

Vector* veccre(size_t elem_size) {
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
        if (cap > SIZE_MAX / RESERVE_FACTOR) {
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

// void* vecat(Vector* v, size_t i) {

// }

// void* vecpush(Vector* v, void* el) {
    
// }

// void* vecfront(Vector* v) {
    
// }

// void* vecback(Vector* v) {
    
// }

size_t vecsize(const Vector *v) { return v->size; }
size_t veccap(const Vector *v) { return v->capacity; }
bool vecemp(const Vector *v) { return v->size == 0; }
