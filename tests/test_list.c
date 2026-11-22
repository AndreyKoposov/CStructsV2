#include <CUnit/Basic.h>

#include "structs/list.h"


void test_list_push(void) {
    // Arrange
    List* l = list(sizeof(int));
    int a = 3;
    int b = 2;
    int c = 5;

    // Act
    int status1 = listpushf(l, &a);
    int status2 = listpushb(l, &b);
    int status3 = listpushf(l, &c);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);
    CU_ASSERT_EQUAL(listsize(l), 3);

    // Clean up
    listdes(l);
}

void test_list_insert(void) {
    // Arrange
    List* l = list(sizeof(int));
    int a = 3;
    int b = 2;
    int c = 5;

    // Act
    int status1 = listpushb(l, &a);
    int status2 = listins(l, 0, &b);
    int status3 = listins(l, 1, &c);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);
    CU_ASSERT_EQUAL(listsize(l), 3);

    // Clean up
    listdes(l);
}

void test_list_pop(void) {
    // Arrange
    List* l = list(sizeof(int));
    int a = 3;
    int b = 2;
    int c = 5;
    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    
    // Act
    int status1 = listpopf(l, &a);
    int status2 = listpopf(l, &b);
    int status3 = listpopf(l, &c);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);

    CU_ASSERT_EQUAL(listsize(l), 0);

    CU_ASSERT_EQUAL(a, 3);
    CU_ASSERT_EQUAL(b, 2);
    CU_ASSERT_EQUAL(c, 5);

    // Clean up
    listdes(l);
}

void test_list_remove(void) {
    // Arrange
    List* l = list(sizeof(int));
    int a = 3;
    int b = 2;
    int c = 5;
    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    
    // Act
    int status1 = listremove(l, 1, &a);
    int status2 = listremove(l, 1, &b);
    int status3 = listremove(l, 0, &c);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);

    CU_ASSERT_EQUAL(listsize(l), 0);

    CU_ASSERT_EQUAL(a, 2);
    CU_ASSERT_EQUAL(b, 5);
    CU_ASSERT_EQUAL(c, 3);

    // Clean up
    listdes(l);
}