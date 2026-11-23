#include <CUnit/Basic.h>

#include "structs/list.h"
#include "utils/comparators.h"


static void _sum(void* data, void* ctx) {
    int* n = data;
    int* sum = ctx;
    *sum += *n;
}


void test_list_push(void) {
    // Arrange
    List* l = list(sizeof(int), NULL, NULL);
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
    List* l = list(sizeof(int), NULL, NULL);
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
    List* l = list(sizeof(int), NULL, NULL);
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
    List* l = list(sizeof(int), NULL, NULL);
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

void test_list_empty(void) {
    // Arrange
    List* l = list(sizeof(int), NULL, NULL);

    // Act
    bool is_empty = listempty(l);

    // Assert
    CU_ASSERT(is_empty);

    // Clean
    listdes(l);
}

void test_list_find(void) {
    // Arrange
    List* l = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    
    // Act
    size_t pos;
    int status1 = listfind(l, &b, &pos);
    int status2 = listfind(l, &d, NULL);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, -1);

    CU_ASSERT_EQUAL(pos, 1);

    // Clean up
    listdes(l);
}

void test_list_at(void) {
    // Arrange
    List* l = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    
    // Act
    int* _a = listat(l, 0);
    int* _b = listat(l, 1);
    int* _c = listat(l, 2);
    int* _d = listat(l, 3);

    // Assert
    CU_ASSERT_EQUAL(*_a, a);
    CU_ASSERT_EQUAL(*_b, b);
    CU_ASSERT_EQUAL(*_c, c);
    CU_ASSERT_PTR_NULL(_d);

    // Clean up
    listdes(l);
}

void test_list_first_last(void) {
    // Arrange
    List* l = list(sizeof(int), comparator_int, NULL);
    List* l2 = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    
    // Act
    int* _a = listfront(l);
    int* _c = listback(l);
    int* null = listback(l2);

    // Assert
    CU_ASSERT_EQUAL(*_a, a);
    CU_ASSERT_EQUAL(*_c, c);
    CU_ASSERT_PTR_NULL(null);

    // Clean up
    listdes(l);
    listdes(l2);
}

void test_list_for(void) {
    // Arrange
    List* l = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    
    // Act
    int sum = 0;
    listfor(l, _sum, &sum);

    // Assert
    CU_ASSERT_EQUAL(sum, 10);

    // Clean up
    listdes(l);
}

void test_list_eraser(void) {
    // Arrange
    List* l1 = list(sizeof(int), comparator_int, NULL);
    List* l2 = list(sizeof(int), comparator_int, NULL);
    List* l3 = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;

    listpushb(l1, &a);
    listpushb(l1, &b);
    listpushb(l1, &c);

    listpushb(l2, &a);
    listpushb(l2, &b);
    listpushb(l2, &c);
    listpushb(l2, &a);
    listpushb(l2, &b);

    listpushb(l3, &a);

    
    // Act
    int status1 = listeraser(l1, 1, 3);
    int status2 = listeraser(l2, 1, 4);
    int status3 = listeraser(l3, 0, 1);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);

    CU_ASSERT_EQUAL(listsize(l1), 1);
    CU_ASSERT_EQUAL(listsize(l2), 2);
    CU_ASSERT_EQUAL(listsize(l3), 0);

    // Clean up
    listdes(l1);
    listdes(l2);
    listdes(l3);
}

void test_list_clone(void) {
    // Arrange
    List* l = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    
    // Act
    List* clone = listclone(l);
    int status1 = listpopf(clone, &a);
    int status2 = listpopf(clone, &b);
    int status3 = listpopf(clone, &c);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);

    CU_ASSERT_EQUAL(a, 3);
    CU_ASSERT_EQUAL(b, 2);
    CU_ASSERT_EQUAL(c, 5);

    // Clean up
    listdes(l);
    listdes(clone);
}