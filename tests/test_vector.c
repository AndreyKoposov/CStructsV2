#include <stdlib.h>
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
    Vector* v = veccre(sizeof(Integer));

    // Act
    vecdes(v);

    // Assert
    CU_ASSERT(1);
}   

void test_reserve(void) {
    // Arrange
    Vector* v = veccre(sizeof(Integer));

    // Act
    int status = vecres(v, 10);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_EQUAL(vecsize(v), 0);
    CU_ASSERT_EQUAL(veccap(v), 16);

    // Clean up
    vecdes(v);
}

void test_shrink(void) {
    // Arrange
    Vector* v = veccre(sizeof(Integer));
    vecres(v, 10);

    // Act
    int status = vecshr(v);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_EQUAL(vecsize(v), 0);
    CU_ASSERT_EQUAL(veccap(v), 0);

    // Clean up
    vecdes(v);
}
