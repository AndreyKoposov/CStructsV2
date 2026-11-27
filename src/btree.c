#include <stdlib.h>
#include <string.h>

#include "structs/vector.h"
#include "structs/list.h"
#include "structs/btree.h"


typedef struct btree_node {
    void* data;
    struct btree_node* left;
    struct btree_node* right;
} BNode;

typedef struct btree {
    BNode* head;
    size_t size;
    size_t el_size;
    comparator comp;
    void* ctx;
} BTree;

typedef struct _trees {
    BTree* t1;
    BTree* t2;
    BTree* t3;
} _Trees;

static void _or(void* data, void* ctx) {
    BTree* t = ctx;
    btreeins(t, data);
}

static void _and(void* data, void* ctx) {
    _Trees* trees = ctx;
    
    if (btreecont(trees->t1, data) && btreecont(trees->t2, data))
        btreeins(trees->t3, data);
}

static void _xor(void* data, void* ctx) {
    _Trees* trees = ctx;
    
    if (!btreecont(trees->t1, data) || !btreecont(trees->t2, data))
        btreeins(trees->t3, data);
}

static void _free_node(BTree* t, BNode* n) {
    free(n->data);
    free(n);
    t->size--;
}

static BNode* _node_at(BTree* t, BNode* begin, size_t index) {
    if (!t || !t->head || !begin || index >= btreesize(t)) return NULL;

    Vector* stack = vector(sizeof(BNode*), NULL, NULL);
    BNode* current = begin;
    size_t i = 0;

    while (current || vecsize(stack) > 0) {
        while (current) {
            vecpush(stack, &current);
            current = current->left;
        }
        vecpop(stack, &current);
        if (i++ == index) break;
        current = current->right;
    }
    vecdes(stack);

    return current;
}

static int _pop_node(BTree* t, BNode* begin) {
    if (!t || !t->head || !begin) return -1;

    typedef struct _post_order_element {
        BNode* node;
        bool visited;
    } _POE;

    Vector* stack = vector(sizeof(_POE), NULL, NULL);
    _POE tmp = {begin, false};

    vecpush(stack, &tmp);
    while(vecsize(stack) > 0) {
        vecpop(stack, &tmp);

        if (!tmp.visited) {
            tmp.visited = true;
            vecpush(stack, &tmp);

            if (tmp.node->right) {
                _POE new = {tmp.node->right, false};
                vecpush(stack, &new);
            }

            if (tmp.node->left) {
                _POE new = {tmp.node->left, false};
                vecpush(stack, &new);
            }
        } else {
            _free_node(t, tmp.node);
        }
    }

    vecdes(stack);

    return 0;
}

static BNode* _create_node(BTree* t, void* data) {
    BNode* node = malloc(sizeof(BNode));
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

static void _delete_node(BTree* t, BNode* n, BNode* prev) {
    if (!n->left && !n->right) {
        if (!prev) t->head = NULL;
        else if (prev->left == n) prev->left = NULL;
        else prev->right = NULL;
    }
    else
    if (!n->left || !n->right) {
        BNode* child = n->left ? n->left : n->right;
        if (!prev) t->head = child;
        else if (prev->left == n) prev->left = child;
        else prev->right = child;
    }
    else {
        BNode* successor_parent = n;
        BNode* successor = successor_parent->right;
        while (successor->left) {
            successor_parent = successor;
            successor = successor->left;
        }
        BNode* succ_right = successor->right;

        if (n->right != successor) {
            successor_parent->left = succ_right;
            successor->right = n->right;
        }

        successor->left = n->left;

        if (!prev) t->head = successor;
        else if (prev->left == n) prev->left = successor;
        else prev->right = successor;
    }

    _free_node(t, n);
}


BTree* btree(size_t el_size, comparator comp, void* ctx) {
    BTree* t = malloc(sizeof(BTree));
    if (!t || el_size == 0) return NULL;

    t->head = NULL;
    t->size = 0;
    t->el_size = el_size;
    t->comp = comp;
    t->ctx = ctx;
    
    return t;
}

void btreedes(BTree* t) {
    if (!t) return;
    
    if (t->head)
        _pop_node(t, t->head);
    free(t);
}

int btreeins(BTree* t, void* data) {
    if (!t) return -1;

    if (!t->head) {
        t->head = _create_node(t, data);
        if (!t->head) return -1;
        t->size++;
        return 0;
    }

    BNode* tmp = t->head;
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

bool btreecont(BTree* t, void* data) {
    if (!t || !data || !t->head) return false;

    BNode* n = t->head;
    while (n) {
        int c = t->comp(data, n->data, t->ctx);
        if (c == 0) return true;
        n = c < 0 ? n->left : n->right;
    }

    return false;
}

int btreedel(BTree* t, void* data) {
    if (!t || !data) return -1;
    if (!t->head) return 0;

    bool found = false;
    BNode* prev = NULL;
    BNode* n = t->head;
    while (n && !found) {
        int c = t->comp(data, n->data, t->ctx);
        if (c == 0)
            found = true;
        else {
            prev = n;
            n = c < 0 ? n->left : n->right;
        }
    }

    if (found)
        _delete_node(t, n, prev);

    return 0;
}

BTree* btreeclone(BTree* t) {
    if (!t) return NULL;

    typedef struct _Frame {
        BNode* origin;
        BNode* clone;
    } _Frame;

    BTree* clone = btree(t->el_size, t->comp, t->ctx);
    if (!t->head) return clone;

    Vector* stack = vector(sizeof(_Frame), NULL, NULL);
    _Frame tmp = {t->head, _create_node(clone, t->head->data)};

    clone->head = tmp.clone;
    clone->size = t->size;

    vecpush(stack, &tmp);
    while(vecsize(stack) > 0) {
        vecpop(stack, &tmp);

        if (tmp.origin->right) {
            _Frame right = {tmp.origin->right, _create_node(clone, tmp.origin->right->data)};
            tmp.clone->right = right.clone;
            vecpush(stack, &right);
        }
        if (tmp.origin->left) {
            _Frame left = {tmp.origin->left, _create_node(clone, tmp.origin->left->data)};
            tmp.clone->left = left.clone;
            vecpush(stack, &left);
        }
    }

    vecdes(stack);

    return clone;
}

int btreeat(BTree* t, size_t i, void* out) {
    if (!t || !out) return -1;

    BNode* n = _node_at(t, t->head, i);
    if (!n) return -1;
    memcpy(out, n->data, t->el_size);

    return 0;
}

int btreemin(BTree* t, void* out) {
    if (!t || !t->head || !out) return -1;

    BNode* min = t->head;
    while (min->left)
        min = min->left;

    memcpy(out, min->data, t->el_size);

    return 0;
}

int btreemax(BTree* t, void* out) {
    if (!t || !t->head || !out) return -1;

    BNode* max = t->head;
    while (max->right)
        max = max->right;

    memcpy(out, max->data, t->el_size);

    return 0;
}

int btreefor(BTree* t, void (*fn)(void*, void*), void* ctx) {
    if (!t || !fn) return -1;
    if (!t->head) return 0;

    List* queue = list(sizeof(BNode*), NULL, NULL);
    BNode* tmp = NULL;

    listpushb(queue, &t->head);
    while (listsize(queue) > 0) {
        listpopf(queue, &tmp);

        fn(tmp->data, ctx);

        if (tmp->left) listpushb(queue, &tmp->left);
        if (tmp->right) listpushb(queue, &tmp->right);
    }

    listdes(queue);

    return 0;
}

int btreeswp(BTree* t1, BTree* t2) {
    if (!t1 || !t2) return -1;

    BNode* tmp_head = t1->head;
    size_t tmp_size = t1->size;
    size_t tmp_el_size = t1->el_size;
    comparator tmp_comp = t1->comp;
    void* tmp_ctx = t1->ctx;

    t1->head =t2->head;
    t1->size = t2->size;
    t1->el_size = t2->el_size;
    t1->comp = t2->comp;
    t1->ctx = t2->ctx;

    t2->head = tmp_head;
    t2->size = tmp_size;
    t2->el_size = tmp_el_size;
    t2->comp = tmp_comp;
    t2->ctx = tmp_ctx;

    return 0;
}

int btreeclear(BTree* t) {
    if (!t) return -1;
    if (!t->head) return 0;

    if (t->head)
        _pop_node(t, t->head);
    t->head = NULL;

    return 0;
}

int btreemove(BTree* t1, BTree* t2) {
    if (!t1 || !t2 || t1->el_size != t2->el_size) return -1;

    btreeclear(t1);
    t1->head = t2->head;
    t1->size = t2->size;
    t1->comp = t2->comp;
    t1->ctx = t2->ctx;

    t2->head = NULL;
    t2->size = 0;

    return 0;
}

int btreeor(BTree* t1, BTree* t2) {
    if (!t1 || !t2 || t1->el_size != t2->el_size) return -1;
    if (!t1->head && !t2->head) return 0;

    return btreefor(t2, _or, t1);
}

int btreeand(BTree* t1, BTree* t2) {
    if (!t1 || !t2 || t1->el_size != t2->el_size) return -1;
    if (!t1->head && !t2->head) return 0;

    BTree* t3 = btree(t1->el_size, t1->comp, t1->ctx);
    _Trees trees = {t1, t2, t3};

    btreefor(t1, _and, &trees);
    btreeswp(t1, t3);
    btreedes(t3);

    return 0;
}

int btreexor(BTree* t1, BTree* t2) {
    if (!t1 || !t2 || t1->el_size != t2->el_size) return -1;
    if (!t1->head && !t2->head) return 0;

    BTree* t3 = btree(t1->el_size, t1->comp, t1->ctx);
    _Trees trees = {t1, t2, t3};

    btreefor(t1, _xor, &trees);
    btreefor(t2, _xor, &trees);
    btreeswp(t1, t3);
    btreedes(t3);

    return 0;
}

bool btreein(BTree* t1, BTree* t2) {
    if (!t1 || !t2) return false;
    if (!t1->head) return true;

    Vector* stack = vector(sizeof(BNode*), NULL, NULL);
    BNode* next = t1->head;

    vecpush(stack, &next);
    while (vecsize(stack) > 0) {
        vecpop(stack, &next);

        if (!btreecont(t2, next->data)) {
            vecdes(stack);
            return false;
        }

        if (next->right) vecpush(stack, &next->right);
        if (next->left) vecpush(stack, &next->left);
    }
    vecdes(stack);

    return true;
}

void* btreetoarr(BTree* t) {
    if (!t) return NULL;

    char* arr = malloc(t->size * t->el_size);
    if (!arr) return NULL;
    if (!t->head) return arr;

    Vector* stack = vector(sizeof(BNode*), NULL, NULL);
    BNode* current = t->head;
    size_t i = 0;

    while (current || vecsize(stack) > 0) {
        while (current) {
            vecpush(stack, &current);
            current = current->left;
        }
        vecpop(stack, &current);
        memcpy(arr + i*t->el_size, current->data, t->el_size);
        i++;
        current = current->right;
    }
    vecdes(stack);

    return arr;
}

BTree* btreefromarr(void* arr, size_t len, size_t el_size, comparator comp, void* ctx) {
    if (!arr) return NULL;

    BTree* t = btree(el_size, comp, ctx);
    char* c_arr = arr;

    for (size_t i = 0; i < len; i++)
        btreeins(t, c_arr + i*el_size);

    return t;
}

bool btreeeq(BTree* t1, BTree* t2) {
    if (!t1 || !t2) return false;

    return btreein(t1, t2) && btreein(t2, t1);
}

size_t btreesize(BTree* t) { return t->size; }
