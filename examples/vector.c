#include <stdio.h>
#include <string.h>
#include <structs/vector.h>

typedef struct { double x, y, z; } Vec3;

static void print_vec3(const void *elem, void *ctx) {
    const Vec3 *p = elem;
    int *idx = ctx;
    printf("  [%d] = (%.1f, %.1f, %.1f)\n", (*idx)++, p->x, p->y, p->z);
}

int main(void) {
    /* int */
    Vector *vi = vector(sizeof(int), comparator_int, NULL);
    for (int i = 0; i < 5; i++) vecpush(vi, &i);
    printf("int vector: size=%zu cap=%zu\n", vecsize(vi), veccap(vi));
    int sum = 0;
    vecfor(vi, (void (*)(void*, void*))NULL, NULL); /* no-op */
    for (size_t i = 0; i < vecsize(vi); i++) sum += *(int *)vecat(vi, i);
    printf("  sum = %d\n", sum);
    veccle(vi);
    vecdes(vi);

    /* Vec3 */
    Vector *v3 = vector(sizeof(Vec3), NULL, NULL);
    Vec3 pts[] = {{1,0,0}, {0,1,0}, {0,0,1}};
    for (int i = 0; i < 3; i++) vecpush(v3, &pts[i]);

    printf("Vec3 vector:\n");
    int idx = 0;
    vecfor(v3, (void (*)(void*, void*))print_vec3, &idx);

    vecdes(v3);
    return 0;
}