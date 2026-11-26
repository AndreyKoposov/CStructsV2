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

typedef struct _post_order_element {
    BNode* node;
    bool visited;
} _POE;

typedef struct _frame {
    BNode* origin;
    BNode* clone;
} _Frame;


static int _dfs_inorder(BTree* t, void (*fn)(BNode*, BTree*, size_t, void*), void* ctx) {
    if (!t || !fn) return -1;
    if (!t->head) return 0;

    Vector* stack = vector(sizeof(BNode*), NULL, NULL);
    BNode* current = t->head;
    size_t i = 0;

    while (current || vecsize(stack) > 0) {
        while (current) {
            vecpush(stack, current);
            current = current->left;
        }
        vecpop(stack, &current);
        fn(current, t, i, ctx);
        i++;
        current = current->right;
    }
    vecdes(stack);

    return 0;
}

static int _dfs_postorder(BTree* t, void (*fn)(BNode*, BTree* , void*), void* ctx) {
    if (!t || !fn) return -1;
    if (!t->head) return 0;

    Vector* stack = vector(sizeof(_POE), NULL, NULL);
    _POE tmp = {t->head, false};

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
        } else
            fn(tmp.node, t, ctx);
    }

    vecdes(stack);

    return 0;
}

static int _bfs(BTree* t, void (*fn)(BNode*, BTree* , void*), void* ctx) {
    if (!t || !fn) return -1;
    if (!t->head) return 0;

    List* queue = list(sizeof(BNode*), NULL, NULL);
    BNode* tmp = NULL;

    listpushb(queue, &t->head);
    while (listsize(queue) > 0) {
        listpopf(queue, &tmp);

        fn(tmp, t, ctx);

        if (tmp->left) listpushb(queue, &tmp->left);
        if (tmp->right) listpushb(queue, &tmp->right);
    }

    listdes(queue);

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

static void _free_node(BNode* n, BTree* t, void* ctx) {
    (void)ctx;

    t->size--;
    free(n->data);
    free(n);
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
    
    _dfs_postorder(t, _free_node, NULL);
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

BTree* btreeclone(BTree* t) {
    if (!t) return NULL;

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

size_t btreesize(BTree* t) { return t->size; }
