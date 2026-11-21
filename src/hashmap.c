#include <stdlib.h>
#include <string.h>

#include <structs/hashmap.h>

#define LOAD_FACTOR 0.75
#define INIT_BUCKETS 16


typedef struct node {
    struct node* left;
    struct node* right;
    size_t code;
    unsigned char data[];
} Node;

typedef struct hashmap
{
    Node** buckets;
    size_t b_size;
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
    if (head) {
        tmp = head;
        _free_node(head->left);
        _free_node(head->right);
        free(tmp);
    }
}

static size_t _get_hash(HashMap* m, size_t hashcode) {
    return hashcode & (m->b_size-1);
}


HashMap* hashmap(size_t k_size, size_t v_size, hash_fn hash, eq_fn eq, void* ctx) {
    if (k_size == 0 || v_size == 0 || !hash || !eq) return NULL;

    HashMap* m = malloc(sizeof(HashMap));
    if (!m) return NULL;

    m->buckets = NULL;
    m->b_size = 0;
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
        for (size_t i = 0; i < m->b_size; i++)
            _free_node(m->buckets[i]);
        free(m->buckets);
    }

    free(m);
}

int mapput(HashMap* m, const void* key, const void* value) {
    if (!m || !key || !value) return -1;

    if (!m->buckets) {
        m->buckets = calloc(INIT_BUCKETS, sizeof(Node*));
        if (!m->buckets) return -1;
        m->b_size = INIT_BUCKETS;
    }

    size_t code = m->hash(key, m->ctx);
    size_t index = _get_hash(m, code);

    if (m->buckets[index] == NULL) {
        Node* n = malloc(sizeof(Node) + m->key_size + m->value_size);
        if (!n) return -1;
    
        n->code = code;
        n->left = NULL;
        n->right = NULL;

        memcpy(n->data, key, m->key_size);
        memcpy(n->data + m->key_size, value, m->value_size);

        m->buckets[index] = n;
    }
    else {
        // TODO
    }

    return 0;
}

void* mapget(const HashMap* m, const void* key) {

}