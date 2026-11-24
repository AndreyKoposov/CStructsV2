#include <string.h>
#include <stdlib.h>

#include "structs/list.h"
#include "structs/vector.h"


typedef struct list_node {
    void* data;
    struct list_node* next;
} LNode;

typedef struct list {
    LNode* first;
    LNode* last;
    size_t size;
    size_t el_size;
    comparator comp;
    void* ctx;
} List;

static LNode* _create_node(List* l, void* data) {
    LNode* n = malloc(sizeof(LNode));
    if (!n) return NULL;

    n->data = malloc(sizeof(l->el_size));
    if (!n->data) {
        free(n);
        return NULL;
    }

    memcpy(n->data, data, l->el_size);
    n->next = NULL;

    return n;
}

static void _destroy_node(List* l, LNode* n, LNode* prev) {
    LNode* next = n->next;
    free(n->data);
    free(n);

    if (l->size == 1) {
        l->first= NULL;
    }
    if (l->size == 2) {
        l->last = NULL;
        if (prev)
            prev->next = next;
    }
    if (l->size > 2) {
        if (prev)
            prev->next = next;
    }

    l->size--;
}

static int _add_node(List* l, LNode* n) {
    if (!l || !n) return -1;

    if (l->size == 0)
        l->first = n;
    if (l->size == 1) {
        l->first->next = n;
        l->last = n;
    }
    if (l->size > 1) {
        l->last->next = n;
        l->last = n;
    }

    l->size++;

    return 0;
}

static List* _list_from_node(LNode* n, size_t el_size, comparator comp, void* ctx) {
    List* l = list(el_size, comp, ctx);

    if (_add_node(l, n) == -1) return NULL;

    return l;
}

static List* _link_lists_sorted(List* l1, List* l2) {
    if (!l1 || !l2 || l1->el_size != l2->el_size) return NULL;

    List* l3 = list(l1->el_size, l1->comp, l1->ctx);

    LNode* n1 = l1->first;
    LNode* n2 = l2->first;
    while (n1 && n2) {
        if (l1->comp(n1->data, n2->data, l1->ctx) == -1) {
            _add_node(l3, n1);
            n1 = n1->next;
        }
        else {
            _add_node(l3, n2);
            n2 = n2->next;
        }
    }
    while (n2) {
        _add_node(l3, n2);
        n2 = n2->next;
    }
    while (n1) {
        _add_node(l3, n1);
        n1 = n1->next;
    }

    free(l1);
    free(l2);

    return l3;
}


List* list(size_t el_size, comparator comp, void* ctx) {
    if (el_size == 0) return NULL;

    List* l = malloc(sizeof(List));
    if (!l) return NULL;

    l->first = NULL;
    l->last = NULL;
    l->size = 0;
    l->el_size = el_size;
    l->comp = comp;
    l->ctx = ctx;

    return l;
}

void listdes(List* l) {
    if (!l) return;

    LNode* n = l->first;
    LNode* tmp;
    while (n) {
        tmp = n->next;
        free(n->data);
        free(n);
        n = tmp;
    }

    free(l);
}

void  listcle(List *l) {
    if (!l) return;

    LNode* n = l->first;
    LNode* tmp;
    while (n) {
        tmp = n->next;
        free(n->data);
        free(n);
        l->size--;
        n = tmp;
    }

    l->first = NULL;
    l->last = NULL;
}

int listpushf(List *l, void *data) {
    if (!l || !data) return -1;

    LNode* n = _create_node(l, data);
    if (!n) return -1;

    if (l->size >= 1)
        n->next = l->first;
    l->first = n;
    l->size++;

    return 0;
}

int listpushb(List *l, void *data) {
    if (!l || !data) return -1;

    LNode* n = _create_node(l, data);
    if (!n) return -1;

    if (l->size == 0)
        l->first = n;

    if (l->size == 1) {
        l->first->next = n;
        l->last = n;
    }

    if (l->size > 1) {
        l->last->next = n;
        l->last = n;
    }

    l->size++;

    return 0;
}

int listins(List *l, size_t i, void *data) {
    if (!l || !data || i >= l->size) return -1;

    LNode* tmp = l->first;
    LNode* prev = NULL;
    for (size_t c = 0; c < i; c++) {
        if (!tmp)
            return -1;
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == l->first)
        return listpushf(l, data);
    if (tmp == l->last)
        return listpushb(l, data);
    
    LNode* n = _create_node(l, data);
    if (!n) return -1;

    n->next = tmp;
    prev->next = n;
    l->size++;

    return 0;
}

int listpopf(List *l, void* out) {
    if (!l || l->size == 0) return -1;

    if (out)
        memcpy(out, l->first->data, l->el_size);

    LNode* first = l->first->next;
    free(l->first->data);
    free(l->first);
    l->first = first;
    l->size--;

    return 0;
}

int listremove(List *l, size_t i, void* out) {
    if (!l || i >= l->size) return -1;

    LNode* tmp = l->first;
    LNode* prev = NULL;
    for (size_t c = 0; c < i; c++) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (out)
        memcpy(out, tmp->data, l->el_size);

    _destroy_node(l, tmp, prev);

    return 0;
}

int listfind(List *l, void *data, size_t* out) {
    if (!l || !data || !l->comp) return -1;

    LNode* n = l->first;
    size_t c = 0;
    while (n) {
        if (l->comp(n->data, data, l->ctx) == 0) {
            if (out)
                *out = c;
            return 0;
        }
        n = n->next;
        c++;
    }

    return -1;
}

void* listat(List *l, size_t i) {
    if (!l || i >= l->size) return NULL;

    LNode* next = l->first;
    for (size_t c = 0; c < i; c++) {
        if (!next) return NULL;
        next = next->next;
    }

    return next->data;
}

void* listfront(List *l) {
    if (!l || l->size == 0) return NULL;
    
    return l->first->data;
}

void* listback(List *l) {
    if (!l || l->size == 0) return NULL;

    if (l->size == 1) return l->first->data;
    else return l->last->data;
}

int listget(List* l, size_t i, void* out) {
    if (!l || !out) return -1;

    void* data = listat(l, i);
    if (!data) return -1;
    memcpy(out, data, l->el_size);

    return 0;
}

void listfor(List* l, void (*fn)(void* el, void* ctx), void* ctx) {
    if (!l || !fn) return;

    LNode* n = l->first;
    while (n) {
        fn(n->data, ctx);
        n = n->next;
    }
}

int listerase(List* l, size_t i) {
    return listremove(l, i, NULL);
}

int listeraser(List* l, size_t first, size_t last) {
    if (!l || first >= l->size || first >= last || last > l->size) return -1;

    LNode* tmp = l->first;
    LNode* prev = NULL;
    size_t c = 0;
    for (; c < first; c++) {
        prev = tmp;
        tmp = tmp->next;
    }
    for (; c < last; c++) {
        LNode* next = tmp->next;
        _destroy_node(l, tmp, NULL);
        tmp = next;
    }
    if (prev)
        prev->next = tmp;

    return 0;
}

List* listclone(List* src) {
    if (!src) return NULL;

    List* new = list(src->el_size, src->comp, src->ctx);
    if (!new) return NULL;

    LNode* n = src->first;
    while (n) {
        listpushb(new, n->data);
        n = n->next;
    }

    return new;
}

int listcpy(List* dst, List* src) {
    if (!dst || !src || src->el_size != dst->el_size) return -1;

    listcle(dst);
    LNode* n_src = src->first;
    while (n_src) {
        listpushb(dst, n_src->data);
        n_src = n_src->next;
    }

    return 0;
}

int listswp(List* a, List* b) {
    if (!a || !b) return -1;

    LNode* tmp_first = a->first;
    LNode* tmp_last  = a->last;
    size_t tmp_el_size = a->el_size;
    size_t tmp_size = a->size;
    comparator tmp_comp = a->comp;
    void* tmp_ctx = a->ctx;

    a->first = b->first;
    a->last = b->last;
    a->el_size = b->el_size;
    a->size = b->size;
    a->comp = b->comp;
    a->ctx = b->ctx;

    b->first = tmp_first;
    b->last = tmp_last;
    b->el_size = tmp_el_size;
    b->size = tmp_size;
    b->comp = tmp_comp;
    b->ctx = tmp_ctx;

    return 0;
}

int listmove(List* dst, List* src) {
    if (!dst || !src) return -1;

    dst->el_size = src->el_size;
    dst->comp = src->comp;
    dst->ctx = src->ctx;
    listcpy(dst, src);

    listcle(src);

    return 0;
}

bool listeq(List* l1, List* l2, void* ctx) {
    if (!l1 || !l2 ||  
        l1->size != l2->size ||
        l1->el_size != l2->el_size) return false;

    LNode* n1 = l1->first;
    LNode* n2 = l2->first;
    while (n1 && n2) {
        if (l1->comp(n1->data, n2->data, ctx) != 0)
            return false;
        n1 = n1->next;
        n2 = n2->next;
    }

    return true;
}

int listmax(List* l, void* out, size_t* i) {
    if (!l || l->size == 0 || !out) return -1;

    void* max = l->first->data;
    size_t pos = 0;
    size_t counter = 1;
    LNode* n = l->first->next;
    while (n) {
        if (l->comp(n->data, max, l->ctx) == 1) {
            max =n->data;
            pos = counter;
        }
        n = n->next;
        counter++;
    }

    memcpy(out, max, l->el_size);
    if (i)
        *i = pos;

    return 0;
}

int listmin(List* l, void* out, size_t* i) {
    if (!l || l->size == 0 || !out) return -1;

    void* min = l->first->data;
    size_t pos = 0;
    size_t counter = 1;
    LNode* n = l->first->next;
    while (n) {
        if (l->comp(n->data, min, l->ctx) == -1) {
            min =n->data;
            pos = counter;
        }
        n = n->next;
        counter++;
    }

    memcpy(out, min, l->el_size);
    if (i)
        *i = pos;

    return 0;
}

int listsort(List* l) {
    if (!l) return -1;
    if (l->size == 0) return 0;

    Vector* stack = vector(sizeof(List*), NULL, NULL);

    LNode* n = l->first;
    LNode* tmp = NULL;
    List* part = NULL;
    while (n) {
        tmp = n;
        n = n->next;
        tmp->next = NULL;

        part = _list_from_node(tmp, l->el_size, l->comp, l->ctx);
        vecpush(stack, &part);

        while (vecsize(stack) >= 2) {
            List** top1 = vecat(stack, vecsize(stack)-1);
            List** top2 = vecat(stack, vecsize(stack)-2);

            if ((*top1)->size != (*top2)->size) break;

            List *l1, *l2, *l3;
            vecpop(stack, &l1);
            vecpop(stack, &l2);

            l3 = _link_lists_sorted(l1, l2);
            vecpush(stack, &l3);
        }
    }

    List* l1, *l2, *l3;
    while (vecsize(stack) > 1) {
        vecpop(stack, &l1);
        vecpop(stack, &l2);

        l3 = _link_lists_sorted(l1, l2);
        vecpush(stack, &l3);
    }

    List* merged;
    vecpop(stack, &merged);
    listswp(merged, l);

    vecdes(stack);
    free(merged);

    return 0;
}

void* listtoarr(List* l) {
    if (!l) return NULL;

    char* arr = malloc(l->size * l->el_size);
    if (!arr) return NULL;

    LNode* n = l->first;
    size_t counter = 0;
    while (n) {
        memcpy(arr + counter*l->el_size, n->data, l->el_size);
        n = n->next;
        counter++;
    }

    return arr;
}

List* listfromarr(void* arr, size_t len, size_t el_size, comparator comp, void* ctx) {
    if (!arr) return NULL;

    List* l = list(el_size, comp, ctx);

    char* bytes = arr;
    char* buffer = malloc(el_size);
    if  (!buffer) return NULL;

    for (size_t i = 0; i < len; i++) {
        memcpy(buffer, bytes + i*el_size, el_size);
        listpushb(l, buffer);
    }

    free(buffer);

    return l;
}

int listlink(List* l1, List* l2) {
    if (!l1 || !l2 || l1->el_size != l2->el_size) return -1;
    if (l1->size == 0 && l2->size == 0) return 0;

    if (l1->size == 0)
        l1->first = l2->first;
    if (l1->size == 1)
        l1->first->next = l2->first;
    if (l1->size > 1)
        l1->last->next = l2->first;

    l1->last = l2->last;
    l1->size += l2->size;

    free(l2);

    return 0;
}

size_t listsize(List* l) { return l->size; }
bool listempty(List *l) { return l->size == 0; }