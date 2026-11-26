#include <CUnit/Basic.h>

#include "structs/btree.h"
#include "utils/comparators.h"


void test_btree_insert(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    int e = 1;
    int f = 4;

    // Act
    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);
    btreeins(t, &d);
    btreeins(t, &e);
    btreeins(t, &f);

    // Assert
    CU_ASSERT_EQUAL(btreesize(t), 6);

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

void test_btree_delete(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    int e = 1;
    int f = 4;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);
    btreeins(t, &d);
    btreeins(t, &e);
    btreeins(t, &f);

    // Act
    int status = btreedel(t, &c);
    bool cont1 = btreecont(t, &c);

    bool cont2 = btreecont(t, &a);
    bool cont3 = btreecont(t, &b);
    bool cont4 = btreecont(t, &d);
    bool cont5 = btreecont(t, &e);
    bool cont6 = btreecont(t, &f);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_FALSE(cont1);
    CU_ASSERT_EQUAL(btreesize(t), 5);

    CU_ASSERT_TRUE(cont2);
    CU_ASSERT_TRUE(cont3);
    CU_ASSERT_TRUE(cont4);
    CU_ASSERT_TRUE(cont5);
    CU_ASSERT_TRUE(cont6);

    // Clean up
    btreedes(t);
}

void test_btree_clone(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);

    // Act
    BTree* clone1 = btreeclone(t);
    BTree* clone2 = btreeclone(t);
    btreeins(clone2, &d);

    // Assert
    CU_ASSERT_EQUAL(btreesize(t), btreesize(clone1));
    CU_ASSERT_NOT_EQUAL(btreesize(t), btreesize(clone2));

    // Clean up
    btreedes(t);
    btreedes(clone1);
    btreedes(clone2);
}

void test_btree_at(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);
    btreeins(t, &d);

    // Act
    int _a, _d;
    int status1 = btreeat(t, 1, &_a);
    int status2 = btreeat(t, 3, &_d);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);

    CU_ASSERT_EQUAL(a, _a);
    CU_ASSERT_EQUAL(d, _d);

    // Clean up
    btreedes(t);
}