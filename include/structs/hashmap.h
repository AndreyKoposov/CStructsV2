#ifndef HASHMAP_H
#define HASHMAP_h

#include <stdbool.h>
#include <stddef.h>


typedef struct hashmap HashMap;

typedef size_t (*hash_fn)(const void* key, void* ctx);
typedef bool (*eq_fn)(const void* a, const void* b, void* ctx);

HashMap* hashmap(size_t k_size, size_t v_size, hash_fn hash, eq_fn eq, void* ctx);
void mapdes(HashMap* m);
void* mapput(HashMap* m, const void* key, const void* value);
void* mapget(const HashMap* m, const void* key);
bool mapremove(HashMap* m, const void* key);
bool mapcont(const HashMap* m, const void* key);
size_t mapsize(const HashMap* m);
void mapcle(HashMap* m);

size_t hashint(const void* key, void* ctx);
size_t hashstr(const void* key, void* ctx);


#endif