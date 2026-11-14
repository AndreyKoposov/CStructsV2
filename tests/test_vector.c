#include <stdlib.h>
#include <stdint.h>
#include <CUnit/Basic.h>

#include "structs/vector.h"


void test_create(void) {
    // Arrange

    // Act
    Vector* v = veccre(sizeof(int));

    // Assert
    CU_ASSERT_EQUAL(vecsize(v), 0);
    CU_ASSERT_EQUAL(veccap(v), 0);
    CU_ASSERT_EQUAL(vecemp(v), 1);

    // Clean up
    free(v);
}   

void test_destroy(void) {
    // Arrange
    Vector* v1 = veccre(sizeof(int));
    Vector* v2 = veccre(sizeof(int));
    Vector* v3 = veccre(sizeof(int));

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
    Vector* v1 = veccre(sizeof(int));
    Vector* v2 = veccre(sizeof(int));
    Vector* v3 = veccre(sizeof(int));
    Vector* v4 = veccre(sizeof(int));
    Vector* v5 = veccre(sizeof(int));
    Vector* v6 = veccre(sizeof(int));

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
    Vector* v1 = veccre(sizeof(int));
    Vector* v2 = veccre(sizeof(int));
    Vector* v3 = veccre(sizeof(int));
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
    Vector* v1 = veccre(sizeof(int));
    Vector* v2 = veccre(sizeof(int));
    int i = 3;
    size_t n = 10;

    // Act
    vecpush(v1, &i);

    for (size_t j = 0; j < n; j++)
        vecpush(v2, &j);

    // Assert
    int* val = vecat(v1, 0);
    CU_ASSERT_EQUAL(*val, i);

    for (size_t j = 0; j < n; j++)
        CU_ASSERT_EQUAL(*(int*)vecat(v2, j), j);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

void test_pop() {
    // Arrange
    Vector* v1 = veccre(sizeof(int));
    Vector* v2 = veccre(sizeof(int));
    int i = 5;
    size_t n = 10;

    vecpush(v1, &i);

    for (size_t j = 0; j < n; j++)
        vecpush(v2, &j);

    // Act
    int* poped = vecpop(v1);
    for (size_t j = 0; j < n; j++)
        vecpop(v2);

    // Assert
    CU_ASSERT_EQUAL(*poped, i);
    CU_ASSERT_EQUAL(vecsize(v2), 0);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}

void test_at(void) {
    // Arrange
    Vector* v1 = veccre(sizeof(int));
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
