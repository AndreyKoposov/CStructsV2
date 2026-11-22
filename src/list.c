#include <string.h>
#include <stdlib.h>

#include "structs/list.h"


typedef struct list_node {
    void* data;
    struct list_node* next;
} LNode;

typedef struct list {
    LNode* first;
    LNode* last;
    size_t size;
    size_t el_size;
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


List* list(size_t el_size) {
    if (el_size == 0) return NULL;

    List* l = malloc(sizeof(List));
    if (!l) return NULL;

    l->first = NULL;
    l->last = NULL;
    l->size = 0;
    l->el_size = el_size;

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
        if (!tmp)
            return -1;
        prev = tmp;
        tmp = tmp->next;
    }

    if (out)
        memcpy(out, tmp->data, l->el_size);

    LNode* next = tmp->next;
    free(tmp->data);
    free(tmp);

    if (l->size == 1) {
        l->first= NULL;
    }
    if (l->size == 2) {
        l->last = NULL;
        prev->next = next;
    }
    if (l->size > 2) {
        prev->next = next;
    }

    l->size--;

    return 0;
}

size_t listsize(List* l) { return l->size; }