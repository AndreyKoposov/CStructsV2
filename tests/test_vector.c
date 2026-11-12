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