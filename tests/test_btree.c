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

void test_btree_contains(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 4;
    int c = 5;
    btreeins(t, &a);
    btreeins(t, &c);

    // Act
    bool status1 = btreecont(t, &a);
    bool status2 = btreecont(t, &c);
    bool status3 = btreecont(t, &b);

    // Assert
    CU_ASSERT_TRUE(status1);
    CU_ASSERT_TRUE(status2);
    CU_ASSERT_FALSE(status3);

    // Clean up
    btreedes(t);
}

void test_btree_clone(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);

    // Act
    BTree* clone = btreeclone(t);

    // Assert
    CU_ASSERT_EQUAL(btreesize(t), btreesize(clone));

    // Clean up
    btreedes(t);
    btreedes(clone);
}
