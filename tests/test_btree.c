#include <CUnit/Basic.h>

#include "structs/btree.h"
#include "utils/comparators.h"


void test_btree_insert(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;

    // Act
    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);

    // Assert
    CU_ASSERT_EQUAL(btreesize(t), 3);

    // Clean up
    btreedes(t);
}

void test_btree_search(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 4;
    int c = 5;
    btreeins(t, &a);
    btreeins(t, &c);

    // Act
    int* _a = btreesrch(t, &a);
    int* _c = btreesrch(t, &c);
    int* _b = btreesrch(t, &b);

    // Assert
    CU_ASSERT_EQUAL(*_a, a);
    CU_ASSERT_EQUAL(*_c, c);
    CU_ASSERT_PTR_NULL(_b);

    // Clean up
    btreedes(t);
}