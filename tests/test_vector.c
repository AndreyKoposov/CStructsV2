#include <stdlib.h>
#include <stdint.h>
#include <CUnit/Basic.h>

#include "structs/vector.h"


void test_create(void) {
    // Arrange

    // Act
    Vector* v = vector(sizeof(int));

    // Assert
    CU_ASSERT_EQUAL(vecsize(v), 0);
    CU_ASSERT_EQUAL(veccap(v), 0);
    CU_ASSERT_EQUAL(vecemp(v), 1);

    // Clean up
    free(v);
}   

void test_destroy(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    Vector* v3 = vector(sizeof(int));

    vecres(v2, 10);
    
    int a = 0, b = 0, c = 0;
    vecpush(v3, &a);
    vecpush(v3, &b);
    vecpush(v3, &c);

    // Act
    vecdes(v1);
    vecdes(v2);
    vecdes(v3);

    // Assert
    CU_ASSERT(1);
}   

void test_reserve(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    Vector* v3 = vector(sizeof(int));
    Vector* v4 = vector(sizeof(int));
    Vector* v5 = vector(sizeof(int));
    Vector* v6 = vector(sizeof(int));

    // Act
    int status1 = vecres(v1, 10);

    int status2 = vecres(v2, 10);
    int status3 = vecres(v2, 20);

    int status4 = vecres(v3, 100);
    int status5 = vecres(v3, 0);

    int status6 = vecres(v4, 0);

    int status7 = vecres(v5, SIZE_MAX);

    int status8 = vecres(v6, 100);
    int status9 = vecres(v6, 99);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(vecsize(v1), 0);
    CU_ASSERT_EQUAL(veccap(v1), 16);

    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);
    CU_ASSERT_EQUAL(vecsize(v2), 0);
    CU_ASSERT_EQUAL(veccap(v2), 32);

    CU_ASSERT_EQUAL(status4, 0);
    CU_ASSERT_EQUAL(status5, 0);
    CU_ASSERT_EQUAL(vecsize(v3), 0);
    CU_ASSERT_EQUAL(veccap(v3), 0);

    CU_ASSERT_EQUAL(status6, 0);
    CU_ASSERT_EQUAL(vecsize(v4), 0);
    CU_ASSERT_EQUAL(veccap(v4), 0);

    CU_ASSERT_EQUAL(status7, -1);
    CU_ASSERT_EQUAL(vecsize(v5), 0);
    CU_ASSERT_EQUAL(veccap(v5), 0);

    CU_ASSERT_EQUAL(status8, 0);
    CU_ASSERT_EQUAL(status9, 0);
    CU_ASSERT_EQUAL(vecsize(v6), 0);
    CU_ASSERT_EQUAL(veccap(v6), 128);

    // Clean up
    vecdes(v1);
    vecdes(v2);
    vecdes(v3);
    vecdes(v4);
    vecdes(v5);
    vecdes(v6);
}

void test_shrink(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    Vector* v3 = vector(sizeof(int));
    vecres(v2, 10);
    vecres(v3, 10);

    int a = 0, b = 0, c= 0;
    vecpush(v3, &a);
    vecpush(v3, &b);
    vecpush(v3, &c);

    // Act
    int status1 = vecshr(v1);
    int status2 = vecshr(v2);
    int status3 = vecshr(v3);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(vecsize(v1), 0);
    CU_ASSERT_EQUAL(veccap(v1), 0);

    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(vecsize(v2), 0);
    CU_ASSERT_EQUAL(veccap(v2), 0);

    CU_ASSERT_EQUAL(status3, 0);
    CU_ASSERT_EQUAL(vecsize(v3), 3);
    CU_ASSERT_EQUAL(veccap(v3), 3);

    // Clean up
    vecdes(v1);
    vecdes(v2);
    vecdes(v3);
}

void test_push(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    int i = 3;
    size_t n = 10;

    // Act
    vecpush(v1, &i);

    for (size_t j = 0; j < n; j++)
        vecpush(v2, &j);

    int status1 = vecpush(NULL, &i);
    int status2 = vecpush(v2, NULL);

    // Assert
    int* val = vecat(v1, 0);
    CU_ASSERT_EQUAL(*val, i);

    for (size_t j = 0; j < n; j++)
        CU_ASSERT_EQUAL(*(int*)vecat(v2, j), j);

    CU_ASSERT_EQUAL(status1, -1);
    CU_ASSERT_EQUAL(status2, -1);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

void test_pop() {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    int i = 5;
    size_t n = 10;

    vecpush(v1, &i);

    for (size_t j = 0; j < n; j++)
        vecpush(v2, &j);

    // Act
    int poped;
    vecpop(v1, &poped);

    for (size_t j = 0; j < n; j++)
        vecpop(v2, NULL);

    // Assert
    CU_ASSERT_EQUAL(poped, i);
    CU_ASSERT_EQUAL(vecsize(v2), 0);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

void test_at(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    vecres(v1, 10);

    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);

    // Act
    int* val1 = vecat(v1, 1);
    int* val2 = vecat(v1, 4);

    // Assert
    CU_ASSERT_EQUAL(*val1, a);
    CU_ASSERT_PTR_EQUAL(val2, NULL);

    // Clean up
    vecdes(v1);
}

void test_back(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));

    // Act
    int* val = vecback(v1);

    // Assert
    CU_ASSERT_PTR_EQUAL(val, NULL);

    // Clean up
    vecdes(v1);
}

void test_get(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    int a = 2;
    vecpush(v1, &a);

    // Act
    int out;
    vecget(v1, 0, &out);
    out = 4;

    int out2 = 0;
    int status = vecget(v2, 0, &out2);

    // Assert
    int* p = (int*)vecat(v1, 0);
    CU_ASSERT_EQUAL(*p, a);
    CU_ASSERT_EQUAL(status, -1);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

static void add(void* el, void* ctx) {
    int* i = el;
    int* add = ctx;

    *i += *add;
}

void test_for(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);
    int to_add = 2;
    
    // Act
    vecfor(v1, add, &to_add);

    // Assert
    for (size_t i = 0; i < vecsize(v1); i++) {
        int* actual = vecat(v1, i);
        CU_ASSERT_EQUAL(*actual, a + to_add);
    }

    // Clean up
    vecdes(v1);
}

void test_insert(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);
    
    // Act
    a = 3;
    int status1 = vecinsert(v1, 0, &a);
    int status2 = vecinsert(v1, 1, &a);
    int status3 = vecinsert(v1, vecsize(v1), &a);
    int status4 = vecinsert(v2, 10, &a);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);
    CU_ASSERT_EQUAL(status4, -1);

    CU_ASSERT_EQUAL(*(int*)vecat(v1, 0), 3);
    CU_ASSERT_EQUAL(*(int*)vecat(v1, 1), 3);
    CU_ASSERT_EQUAL(*(int*)vecat(v1, 2), 2);
    CU_ASSERT_EQUAL(*(int*)vecat(v1, 3), 2);
    CU_ASSERT_EQUAL(*(int*)vecat(v1, 4), 2);
    CU_ASSERT_EQUAL(*(int*)vecat(v1, 5), 3);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

void test_erase(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    int a = 2;
    int b = 3;
    vecpush(v1, &a);
    vecpush(v1, &b);
    vecpush(v1, &a);
    
    // Act
    int status1 = vecerase(v1, 1);
    int status2 = vecerase(v2, 15);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(vecsize(v1), 2);

    CU_ASSERT_EQUAL(*(int*)vecat(v1, 0), a);
    CU_ASSERT_EQUAL(*(int*)vecat(v1, 1), a);

    CU_ASSERT_EQUAL(status2, -1);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

void test_erase_range(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    Vector* v3 = vector(sizeof(int));
    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);

    vecpush(v2, &a);
    vecpush(v2, &a);
    vecpush(v2, &a);
    
    // Act
    int status1 = veceraser(v1, 1, 3);
    int status2 = veceraser(v2, 1, 3);
    int status3 = veceraser(v3, 2, 5);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(vecsize(v1), 3);

    CU_ASSERT_EQUAL(*(int*)vecat(v1, 0), a);
    CU_ASSERT_EQUAL(*(int*)vecat(v1, vecsize(v1)-1), a);

    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(vecsize(v2), 1);
    CU_ASSERT_EQUAL(*(int*)vecat(v2, 0), a);

    CU_ASSERT_EQUAL(status3, -1);

    // Clean up
    vecdes(v1);
    vecdes(v2);
    vecdes(v3);
}

void test_copy(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    Vector* v3 = vector(sizeof(int));
    Vector* v4 = vector(sizeof(double));

    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);

    int b = 3;
    vecpush(v2, &b);
    vecpush(v2, &b);
    vecpush(v2, &b);
    
    // Act
    int status1 = veccpy(v3, v1);
    int status2 = veccpy(v4, v2);
    int status3 = veccpy(NULL, v1);
    int status4 = veccpy(v4, NULL);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, -1);
    CU_ASSERT_EQUAL(status3, -1);
    CU_ASSERT_EQUAL(status4, -1);

    CU_ASSERT_EQUAL(*(int*)vecat(v3, 0), a);
    CU_ASSERT_EQUAL(*(int*)vecat(v3, vecsize(v3)-1), a);

    // Clean up
    vecdes(v1);
    vecdes(v2);
    vecdes(v3);
    vecdes(v4);
}

void test_clone(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));

    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);
    
    // Act
    Vector* clone = vecclone(v1);
    vecpop(v1, NULL);

    // Assert
    CU_ASSERT_EQUAL(vecsize(clone), 3);

    // Clean up
    vecdes(v1);
    vecdes(clone);
}

void test_swap(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(double));

    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);

    double b = 2;
    vecpush(v2, &b);
    vecpush(v2, &b);
    
    // Act
    int status = vecswp(v1, v2);
    vecpop(v1, NULL);

    // Assert
    CU_ASSERT_EQUAL(status, 0);

    CU_ASSERT_EQUAL(vecsize(v1), 1);
    CU_ASSERT_EQUAL(vecsize(v2), 3);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

static bool equals(void* el1, void* el2, void* ctx) {
    int* a = el1;
    int* b = el2;
    (void)ctx;

    return *a == *b;
}

void test_equals(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    Vector* v3 = vector(sizeof(int));

    int a = 3;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);

    int b = 2;
    vecpush(v2, &b);
    vecpush(v2, &b);

    int c = 3;
    vecpush(v3, &c);
    vecpush(v3, &c);
    vecpush(v3, &c);
    
    // Act
    bool res1 = vecequ(v1, v2, equals, NULL);
    bool res2 = vecequ(v1, v3, equals, NULL);

    // Assert
    CU_ASSERT_EQUAL(res1, false);
    CU_ASSERT_EQUAL(res2, true);

    // Clean up
    vecdes(v1);
    vecdes(v2);
    vecdes(v3);
}

void test_move(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));
    Vector* v3 = vector(sizeof(int));

    int a = 2;
    vecpush(v1, &a);
    vecpush(v1, &a);
    vecpush(v1, &a);

    int b = 3;
    vecpush(v2, &b);
    vecpush(v2, &b);
    size_t v2_cap = veccap(v2);

    int c = 4;
    vecpush(v3, &c);
    vecpush(v3, &c);
    vecpush(v3, &c);
    vecpush(v3, &c);
    size_t v3_cap = veccap(v3);
    
    // Act
    int status1 = vecmove(v1, v2);
    CU_ASSERT_EQUAL(veccap(v1), v2_cap);
    vecpush(v1, &c);

    CU_ASSERT_EQUAL(vecsize(v1), 3);
    CU_ASSERT_EQUAL(vecsize(v2), 0);
    CU_ASSERT_EQUAL(veccap(v2), 0);

    int status2 = vecmove(v1, v3);
    CU_ASSERT_EQUAL(veccap(v1), v3_cap);
    vecpush(v1, &c);

    CU_ASSERT_EQUAL(vecsize(v1), 5);
    CU_ASSERT_EQUAL(vecsize(v3), 0);
    CU_ASSERT_EQUAL(veccap(v3), 0);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);

    // Clean up
    vecdes(v1);
    vecdes(v2);
    vecdes(v3);
}

static int value(void* x, void* ctx) {
    (void)ctx;
    return *(int*)x;
}

void test_max_min(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    Vector* v2 = vector(sizeof(int));

    for (size_t i = 0; i < 10; i++) {
        vecpush(v1, &i);
    }
    
    // Act
    int max;
    size_t max_pos;
    int status1 = vecmax(v1, value, NULL, &max, &max_pos);

    int min;
    size_t min_pos;
    int status2 = vecmin(v1, value, NULL, &min, &min_pos);

    int status3 = vecmin(v2, value, NULL, NULL, NULL);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, -1);

    CU_ASSERT_EQUAL(max, 9);
    CU_ASSERT_EQUAL(max_pos, 9);

    CU_ASSERT_EQUAL(min, 0);
    CU_ASSERT_EQUAL(min_pos, 0);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

void test_sort(void) {
    // Arrange
    Vector* v1 = vector(sizeof(int));
    
    int arr[] = {3,2,31,4,7,9};
    int sorted[] = {2,3,4,7,9,31};
    for (size_t i = 0; i < 6; i++) {
        vecpush(v1, &arr[i]);
    }
    
    // Act
    int status = vecsort(v1, value, NULL);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    for (size_t i = 0; i < 6; i++) {
        CU_ASSERT_EQUAL(*(int*)vecat(v1, i), sorted[i]);
    }

    // Clean up
    vecdes(v1);
}

void test_from_to_array(void) {
    // Arrange
    int arr[] = {3,2,31,4,7,9};

    // Act
    Vector* v2 = vecfromarr(arr, 6, sizeof(int));
    int* arr2 = vectoarr(v2);

    // Assert
    for (int i = 0; i < 6; i++) {
        CU_ASSERT_EQUAL(arr[i], arr2[i]);
        CU_ASSERT_EQUAL(arr[i], *(int*)vecat(v2, i))
    }

    // Clean up
    vecdes(v2);
    free(arr2);
}

void test_different_types(void) {
    // Arrange
    typedef struct custom {
        int a;
        char b;
        double c;
    } Custom;

    Vector* vi = vector(sizeof(int));
    Vector* vd = vector(sizeof(double));
    Vector* vs = vector(sizeof(Custom));

    int arr[] = {5,4,3,2,1,0};

    // Act & Assert
    CU_ASSERT_EQUAL(vecemp(vi), true);

    CU_ASSERT_EQUAL(vecres(vd, 32), 0);
    CU_ASSERT_EQUAL(veccap(vd), 32);
    CU_ASSERT_EQUAL(vecsize(vd), 0);
    
    Vector* vi2 = vecfromarr(arr, 6, sizeof(int));
    CU_ASSERT_EQUAL(vecsort(vi2, value, NULL), 0);

    int* front = vecfront(vi2);
    int* back = vecback(vi2);

    CU_ASSERT_EQUAL(*front, 0);
    CU_ASSERT_EQUAL(*back, 5);

    int max, min;
    size_t i_max, i_min;
    CU_ASSERT_EQUAL(vecmax(vi2, value, NULL, &max, &i_max), 0);
    CU_ASSERT_EQUAL(vecmin(vi2, value, NULL, &min, &i_min), 0);

    CU_ASSERT_EQUAL(*front, min);
    CU_ASSERT_EQUAL(*back, max);
    CU_ASSERT_EQUAL(i_max, 5);
    CU_ASSERT_EQUAL(i_min, 0);

    for (int i = 0; i < 6; i++)
        vecpush(vi, &arr[i]);

    vecerase(vi, 1);
    int* second = vecat(vi, 1);

    CU_ASSERT_EQUAL(*second, 3);

    double dbl = 0.3f;
    vecpush(vd, &dbl);
    vecpush(vd, &dbl);
    vecpush(vd, &dbl);
    vecpush(vd, &dbl);

    double out;
    vecget(vd, 3, &out);

    CU_ASSERT_DOUBLE_EQUAL(dbl, out, 0.01);
    out = 4;
    CU_ASSERT_DOUBLE_EQUAL(*(double*)vecat(vd, 3), dbl, 0.01);

    veceraser(vd, 1, 3);
    CU_ASSERT_EQUAL(vecsize(vd), 2);

    Custom s1 = {0, 1, 2};
    vecpush(vs, &s1);
    vecpush(vs, &s1);
    vecpush(vs, &s1);

    CU_ASSERT_EQUAL(vecsize(vs), 3);

    Custom s2;
    vecpop(vs, &s2);

    CU_ASSERT_EQUAL(s2.a, 0);
    CU_ASSERT_EQUAL(s2.b, 1);
    CU_ASSERT_DOUBLE_EQUAL(s2.c, 2, 0.01);

    // Clean up
    vecdes(vi);
    vecdes(vd);
    vecdes(vs);
    vecdes(vi2);
}

void test_basic_lifecycle(void)
{
    Vector *v = vector(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(v);

    CU_ASSERT_EQUAL(vecsize(v), 0);
    CU_ASSERT_TRUE(vecemp(v));
    CU_ASSERT_EQUAL(veccap(v), 0);

    CU_ASSERT_EQUAL(vecres(v, 8), 0);
    CU_ASSERT_EQUAL(veccap(v), 8);
    CU_ASSERT_EQUAL(vecsize(v), 0);

    int a = 10, b = 20, c = 30;
    CU_ASSERT_EQUAL(vecpush(v, &a), 0);
    CU_ASSERT_EQUAL(vecpush(v, &b), 0);
    CU_ASSERT_EQUAL(vecpush(v, &c), 0);

    CU_ASSERT_EQUAL(vecsize(v), 3);
    CU_ASSERT_FALSE(vecemp(v));

    /* front / back / at */
    CU_ASSERT_EQUAL(*(int *)vecfront(v), 10);
    CU_ASSERT_EQUAL(*(int *)vecback(v), 30);
    CU_ASSERT_EQUAL(*(int *)vecat(v, 1), 20);

    /* get */
    int out = 0;
    CU_ASSERT_EQUAL(vecget(v, 2, &out), 0);
    CU_ASSERT_EQUAL(out, 30);

    /* pop */
    out = 0;
    CU_ASSERT_EQUAL(vecpop(v, &out), 0);
    CU_ASSERT_EQUAL(out, 30);
    CU_ASSERT_EQUAL(vecsize(v), 2);

    /* shrink */
    CU_ASSERT_EQUAL(vecshr(v), 0);
    CU_ASSERT_EQUAL(veccap(v), 2);
    CU_ASSERT_EQUAL(vecsize(v), 2);

    /* clear */
    veccle(v);
    CU_ASSERT_TRUE(vecemp(v));
    CU_ASSERT_EQUAL(vecsize(v), 0);

    vecdes(v);
}

static void sum_int(void *el, void *ctx)
{
    int *acc = (int *)ctx;
    *acc += *(int *)el;
}

void test_modifications(void)
{
    Vector *v = vector(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(v);

    for (int i = 0; i < 5; ++i)
        CU_ASSERT_EQUAL(vecpush(v, &i), 0);

    /* sum via vecfor */
    int acc = 0;
    vecfor(v, sum_int, &acc);
    CU_ASSERT_EQUAL(acc, 0 + 1 + 2 + 3 + 4);

    /* insert в начало */
    int neg = -1;
    CU_ASSERT_EQUAL(vecinsert(v, 0, &neg), 0);
    CU_ASSERT_EQUAL(vecsize(v), 6);
    CU_ASSERT_EQUAL(*(int *)vecfront(v), -1);

    /* insert в середину */
    int x = 100;
    CU_ASSERT_EQUAL(vecinsert(v, 3, &x), 0);
    CU_ASSERT_EQUAL(vecsize(v), 7);
    CU_ASSERT_EQUAL(*(int *)vecat(v, 3), 100);

    /* erase одного элемента */
    CU_ASSERT_EQUAL(vecerase(v, 3), 0);
    CU_ASSERT_EQUAL(vecsize(v), 6);
    CU_ASSERT_EQUAL(*(int *)vecat(v, 3), 2);

    /* erase диапазона [1, 3) */
    CU_ASSERT_EQUAL(veceraser(v, 1, 3), 0);
    CU_ASSERT_EQUAL(vecsize(v), 4);
    /* после удаления: [-1, 2, 3, 4] */
    CU_ASSERT_EQUAL(*(int *)vecat(v, 0), -1);
    CU_ASSERT_EQUAL(*(int *)vecat(v, 1), 2);
    CU_ASSERT_EQUAL(*(int *)vecat(v, 2), 3);
    CU_ASSERT_EQUAL(*(int *)vecat(v, 3), 4);

    vecdes(v);
}

