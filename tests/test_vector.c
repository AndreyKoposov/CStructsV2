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
