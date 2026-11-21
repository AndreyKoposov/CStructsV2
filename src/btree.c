#include <stdlib.h>
#include <string.h>

#include "structs/vector.h"
#include "structs/btree.h"


typedef struct node {
    void* data;
    struct node* left;
    struct node* right;
} Node;

typedef struct btree {
    Node* head;
    size_t size;
    size_t el_size;
    comparator comp;
    void* ctx;
} BTree;

Node* _create_node(BTree* t, void* data) {
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->data = malloc(t->el_size);
    if (!node->data) {
        free(node);
        return NULL;
    }

    memcpy(node->data, data, t->el_size);

    node->left = NULL;
    node->right = NULL;

    return node;
}


BTree* btree(size_t el_size, comparator comp, void* ctx) {
    BTree* t = malloc(sizeof(BTree));
    if (!t) return NULL;

    t->head = NULL;
    t->size = 0;
    t->el_size = el_size;
    t->comp = comp;
    t->ctx = ctx;
    
    return t;
}

void btreedes(BTree* t) {
    if (!t) return;
    if (!t->head) {
        free(t);
        return;
    }

    Vector* v = vector(sizeof(Node*));
    vecpush(v, t->head);

    Node* tmp;
    while (vecsize(v) > 0) {
        vecpop(v, &tmp);

        if (tmp->left) vecpush(v, tmp->left);
        if (tmp->right) vecpush(v, tmp->right);

        free(tmp->data);
        free(tmp);
    }
    vecdes(v);
    free(t);
}

void* btreesrch(const BTree* t, const void* data) {
    if (!t || !data || !t->head) return NULL;

    Node* tmp = t->head;
    while (tmp) {
        int c = t->comp(data, tmp->data, t->ctx);
        if (c == 0) return tmp->data;
        tmp = c < 0 ? tmp->left : tmp->right;
    }

    return NULL;
}

int btreeins(BTree* t, const void* data) {
    if (!t) return -1;

    if (!t->head) {
        t->head = _create_node(t, data);
        if (!t->head) return -1;
        t->size++;
        return 0;
    }

    Node* tmp = t->head;
    while (tmp) {
        int c = t->comp(data, tmp->data, t->ctx);
        if (c == 0) return -1;
        
        if (c < 0 && !tmp->left) {
            tmp->left = _create_node(t, data);
            if (!tmp->left) return -1;
            t->size++;
            return 0;
        }
        if (c > 0 && !tmp->right) {
            tmp->right = _create_node(t, data);
            if (!tmp->right) return -1;
            t->size++;
            return 0;
        }

        tmp = c < 0 ? tmp->left : tmp->right;
    }

    return -1;
}

size_t btreesize(const BTree* t) { if (t) return t->size; }