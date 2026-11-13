#include <stdlib.h>
#include <stdint.h>
#include <CUnit/Basic.h>

#include "structs/vector.h"
#include "objects/int.h"


void test_create(void) {
    // Arrange

    // Act
    Vector* v = veccre(sizeof(Integer));

    // Assert
    CU_ASSERT_EQUAL(vecsize(v), 0);
    CU_ASSERT_EQUAL(veccap(v), 0);
    CU_ASSERT_EQUAL(vecemp(v), 1);

    // Clean up
    free(v);
}   

void test_destroy(void) {
    // Arrange
    Vector* v1 = veccre(sizeof(Integer));
    Vector* v2 = veccre(sizeof(Integer));
    vecres(v2, 10);

    // Act
    vecdes(v1);
    vecdes(v2);

    // Assert
    CU_ASSERT(1);
}   

void test_reserve(void) {
    // Arrange
    Vector* v1 = veccre(sizeof(Integer));
    Vector* v2 = veccre(sizeof(Integer));
    Vector* v3 = veccre(sizeof(Integer));
    Vector* v4 = veccre(sizeof(Integer));
    Vector* v5 = veccre(sizeof(Integer));
    Vector* v6 = veccre(sizeof(Integer));

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
    Vector* v1 = veccre(sizeof(Integer));
    Vector* v2 = veccre(sizeof(Integer));
    vecres(v2, 10);

    // Act
    int status1 = vecshr(v1);
    int status2 = vecshr(v2);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(vecsize(v1), 0);
    CU_ASSERT_EQUAL(veccap(v1), 0);

    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(vecsize(v2), 0);
    CU_ASSERT_EQUAL(veccap(v2), 0);

    // Clean up
    vecdes(v1);
    vecdes(v2);
}
