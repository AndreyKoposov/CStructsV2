#include <CUnit/Basic.h>

#include "structs/btree.h"


void test_btree_insert(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;

    // Act
    btreeins(t, &a);

    // Assert
    CU_ASSERT_EQUAL(btreesize(t), 1);

    // Clean up
    btreedes(t);
}

void test_btree_search(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 4;
    btreeins(t, &a);

    // Act
    int* _a = btreesrch(t, &a);
    int* _b = btreesrch(t, &b);

    // Assert
    CU_ASSERT_EQUAL(*_a, a);
    CU_ASSERT_PTR_NULL(_b);

    // Clean up
    btreedes(t);
}