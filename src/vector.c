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

static inline void* _arr_elem_ptr(void* arr, size_t i, size_t el_size) {
    return (char *)arr + i * el_size;
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
    if (first >= v->size || first >= last || last > v->size) return -1;

    if (last < v->size)
        memmove(_vec_elem_ptr(v, first), _vec_elem_ptr(v, last), (last - first + 1) * v->elem_size);
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

int vecmax(Vector* a, int (*value)(void*, void* ctx), void* ctx, int* out, size_t* i) {
    if (!a || !value || vecsize(a) < 1) return -1;

    int max = value(vecat(a, 0), ctx);
    int pos = 0;
    for (size_t i = 1; i < vecsize(a); i++) {
        int another = value(vecat(a, i), ctx);
        if (another > max) {
            max = another;
            pos = i;
        }
    }

    *out = max;
    *i = pos;

    return 0;
}

int vecmin(Vector* a, int (*value)(void*, void* ctx), void* ctx, int* out, size_t* i) {
    if (!a || !value || vecsize(a) < 1) return -1;

    int min = value(vecat(a, 0), ctx);
    int pos = 0;
    for (size_t i = 1; i < vecsize(a); i++) {
        int another = value(vecat(a, i), ctx);
        if (another < min) {
            min = another;
            pos = i;
        }
    }

    *out = min;
    *i = pos;

    return 0;
}

static void _swap(void* a, void* b, size_t el_s) {
    char* A = (char*)a;
    char* B = (char*)b;
    char C[el_s];

    memcpy(C, A, el_s);
    memcpy(A, B, el_s);
    memcpy(B, C, el_s);
}

static size_t _partition(void* arr, size_t low, size_t high, size_t el_s,
                         int (*value)(void*, void* ctx), void* ctx) {
    void* element = _arr_elem_ptr(arr, high, el_s);
    int pivot = value(element, ctx);
    size_t i = low;

    for (size_t j = low; j < high; j++) {
        void* arr_j = _arr_elem_ptr(arr, j, el_s);
        if (value(arr_j, ctx) < pivot) {
            void* arr_i = _arr_elem_ptr(arr, i, el_s);
            _swap(arr_i, arr_j, el_s);
            i++;
        }
    }
    void* arr_i = _arr_elem_ptr(arr, i, el_s);
    void* arr_high = _arr_elem_ptr(arr, high, el_s);
    _swap(arr_i, arr_high, el_s);
    return i;
}

static void _quick_sort(void* arr, size_t low, size_t high, size_t el_s,
                        int (*value)(void*, void* ctx), void* ctx) {
    if (low < high) {
        size_t pi = _partition(arr, low, high, el_s, value, ctx);
        if (pi > low)
            _quick_sort(arr, low, pi - 1, el_s, value, ctx);
        _quick_sort(arr, pi + 1, high, el_s, value, ctx);
    }
}

int vecsort(Vector* a, int (*value)(void*, void* ctx), void* ctx) {
    if (!a || !value) return -1;

    _quick_sort(a->data, 0, a->size-1, a->elem_size, value, ctx);

    return 0;
}

Vector* vecfromarr(void* arr, size_t len, size_t el_size) {
    if (!arr) return NULL;

    Vector* a = vector(el_size);
    a->elem_size = el_size;
    a->size = len;
    if (vecres(a, len) == -1) {
        vecdes(a);
        return NULL;
    }
    memcpy(a->data, arr, len*el_size);

    return a;
}

void* vectoarr(Vector* a) {
    if (!a) return NULL;

    void* arr = malloc(a->size*a->elem_size);
    if (!arr) return NULL;
    memcpy(arr, a->data, a->size*a->elem_size);

    return arr;
}

size_t vecsize(Vector *v) { return v->size; }
size_t veccap(Vector *v) { return v->capacity; }
bool vecemp(Vector *v) { return v->size == 0; }
