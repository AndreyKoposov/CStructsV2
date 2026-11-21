#include <stdlib.h>

#include <structs/hashmap.h>


typedef struct node {
    struct node* next;
    size_t hash;
    unsigned char data[];
} Node;

typedef struct hashmap
{
    Node** buckets;
    size_t capacity;
    size_t size;
    size_t key_size;
    size_t value_size;
    hash_fn hash;
    eq_fn eq;
    void* ctx;
} HashMap;

static void _free_node(Node* head) {
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

HashMap* hashmap(size_t k_size, size_t v_size, hash_fn hash, eq_fn eq, void* ctx) {
    if (k_size == 0 || v_size == 0 || !hash || !eq) return NULL;

    HashMap* m = malloc(sizeof(HashMap));
    if (!m) return NULL;

    m->buckets = NULL;
    m->capacity = 0;
    m->size = 0;
    m->key_size = k_size;
    m->value_size = v_size;
    m->hash = hash;
    m->eq = eq;
    m->ctx = ctx;

    return m;
}

void mapdes(HashMap* m) {
    if (!m) return;

    if (m->buckets) {
        for (size_t i = 0; i < m->capacity; i++)
            _free_node(m->buckets[i]);
        free(m->buckets);
    }

    free(m);
}

