#include <stdlib.h>
#include <CUnit/Basic.h>

#include "structs/list.h"
#include "utils/comparators.h"


static void _sum(void* data, void* ctx) {
    int* n = data;
    int* sum = ctx;
    *sum += *n;
}

static void _sum_into(void *el, void *ctx)
{
    *(int *)ctx += *(int *)el;
}

static int _list_sum(List *l)
{
    int s = 0;
    listfor(l, _sum_into, &s);
    return s;
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

void test_list_copy(void) {
    // Arrange
    List* l1 = list(sizeof(int), comparator_int, NULL);
    List* l2 = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;

    listpushb(l1, &a);
    listpushb(l1, &b);
    listpushb(l1, &c);

    listpushb(l2, &c);
    
    // Act
    int status = listcpy(l2, l1);

    // Assert
    int* q1 = listat(l1, 1);
    int* q2 = listat(l2, 1);

    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_EQUAL(listsize(l1), listsize(l2));
    CU_ASSERT_EQUAL(*q1, *q2);

    // Clean up
    listdes(l1);
    listdes(l2);
}

void test_list_swap(void) {
    // Arrange
    List* l1 = list(sizeof(int), comparator_int, NULL);
    List* l2 = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;

    listpushb(l1, &a);
    listpushb(l1, &b);
    listpushb(l1, &c);

    listpushb(l2, &c);

    size_t s1 = listsize(l1);
    size_t s2 = listsize(l2);
    
    // Act
    int status = listswp(l1, l2);

    // Assert
    int* q1 = listat(l1, 0);
    int* q2 = listat(l2, 0);

    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_EQUAL(listsize(l1), s2);
    CU_ASSERT_EQUAL(listsize(l2), s1);
    CU_ASSERT_EQUAL(*q1, 5);
    CU_ASSERT_EQUAL(*q2, 3);

    // Clean up
    listdes(l1);
    listdes(l2);
}

void test_list_move(void) {
    // Arrange
    List* l1 = list(sizeof(int), comparator_int, NULL);
    List* l2 = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;

    listpushb(l1, &a);
    listpushb(l1, &b);
    listpushb(l1, &c);

    listpushb(l2, &c);

    size_t s1 = listsize(l1);
    
    // Act
    int status = listmove(l2, l1);

    // Assert
    int* q1 = listat(l2, 0);

    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_EQUAL(listsize(l1), 0);
    CU_ASSERT_EQUAL(listsize(l2), s1);
    CU_ASSERT_EQUAL(*q1, a);

    // Clean up
    listdes(l1);
    listdes(l2);
}

void test_list_equals(void) {
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

    listpushb(l3, &b);
    listpushb(l3, &a);
    listpushb(l3, &c);
    
    // Act
    bool eq1 = listeq(l1, l2, NULL);
    bool eq2 = listeq(l1, l3, NULL);

    // Assert
    CU_ASSERT(eq1);
    CU_ASSERT(!eq2);

    // Clean up
    listdes(l1);
    listdes(l2);
    listdes(l3);
}

void test_list_min_max(void) {
    // Arrange
    List* l1 = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = -2;
    int e = 15;

    listpushb(l1, &a);
    listpushb(l1, &b);
    listpushb(l1, &c);
    listpushb(l1, &d);
    listpushb(l1, &e);

    int max, min;
    size_t max_pos, min_pos;

    // Act
    int status1 = listmax(l1, &max, &max_pos);
    int status2 = listmin(l1, &min, &min_pos);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);

    CU_ASSERT_EQUAL(max, 15);
    CU_ASSERT_EQUAL(max_pos, 4);

    CU_ASSERT_EQUAL(min, -2);
    CU_ASSERT_EQUAL(min_pos, 3);

    // Clean up
    listdes(l1);
}

void test_list_sort(void) {
    // Arrange
    List* l1 = list(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = -2;
    int e = 15;

    listpushb(l1, &a);
    listpushb(l1, &b);
    listpushb(l1, &c);
    listpushb(l1, &d);
    listpushb(l1, &e);

    // Act
    int status = listsort(l1);

    // Assert
    CU_ASSERT_EQUAL(status, 0);

    CU_ASSERT_EQUAL(*(int*)listat(l1, 0), -2);
    CU_ASSERT_EQUAL(*(int*)listat(l1, 1), 2);
    CU_ASSERT_EQUAL(*(int*)listat(l1, 2), 3);
    CU_ASSERT_EQUAL(*(int*)listat(l1, 3), 5);
    CU_ASSERT_EQUAL(*(int*)listat(l1, 4), 15);

    // Clean up
    listdes(l1);
}

void test_list_to_array(void) {
    // Arrange
    List* l = list(sizeof(int), comparator_int, NULL);
    int a = 0, b = 1, c = 2, d = 3, e= 4;

    listpushb(l, &a);
    listpushb(l, &b);
    listpushb(l, &c);
    listpushb(l, &d);
    listpushb(l, &e);

    // Act
    int* arr = listtoarr(l);

    // Assert
    CU_ASSERT_EQUAL(arr[0], *(int*)listat(l, 0));
    CU_ASSERT_EQUAL(arr[1], *(int*)listat(l, 1));
    CU_ASSERT_EQUAL(arr[2], *(int*)listat(l, 2));
    CU_ASSERT_EQUAL(arr[3], *(int*)listat(l, 3));
    CU_ASSERT_EQUAL(arr[4], *(int*)listat(l, 4));

    // Clean up
    free(arr);
    listdes(l);
}

void test_list_from_array(void) {
    // Arrange
    int a[] = {1,2,3,4,5};

    // Act
    List* l = listfromarr(a, 5, sizeof(int), comparator_int, NULL);

    // Assert
    CU_ASSERT_PTR_NOT_NULL(l);

    CU_ASSERT_EQUAL(*(int*)listat(l, 0), a[0]);
    CU_ASSERT_EQUAL(*(int*)listat(l, 1), a[1]);
    CU_ASSERT_EQUAL(*(int*)listat(l, 2), a[2]);
    CU_ASSERT_EQUAL(*(int*)listat(l, 3), a[3]);
    CU_ASSERT_EQUAL(*(int*)listat(l, 4), a[4]);

    // Clean up
    listdes(l);
}

void test_list_link(void) {
    // Arrange
    List* l1 = list(sizeof(int), comparator_int, NULL);
    List* l2 = list(sizeof(int), comparator_int, NULL);

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    listpushb(l1, &a);
    listpushb(l1, &b);

    listpushb(l2, &c);
    listpushb(l2, &d);

    // Act
    int status = listlink(l1, l2);

    // Assert
    CU_ASSERT_EQUAL(status, 0);

    CU_ASSERT_EQUAL(*(int*)listat(l1, 0), 1);
    CU_ASSERT_EQUAL(*(int*)listat(l1, 3), 4);

    // Clean up
    listdes(l1);
}

void test_list_basic_lifecycle(void)
{
    List *l = list(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(l);

    CU_ASSERT_EQUAL(listsize(l), 0);
    CU_ASSERT_TRUE(listempty(l));
    CU_ASSERT_PTR_NULL(listfront(l));
    CU_ASSERT_PTR_NULL(listback(l));

    int a = 10, b = 20, c = 30;
    CU_ASSERT_EQUAL(listpushf(l, &a), 0);   /* [10] */
    CU_ASSERT_EQUAL(listpushb(l, &b), 0);   /* [10,20] */
    CU_ASSERT_EQUAL(listpushf(l, &c), 0);   /* [30,10,20] */

    CU_ASSERT_EQUAL(listsize(l), 3);
    CU_ASSERT_FALSE(listempty(l));

    CU_ASSERT_EQUAL(*(int *)listfront(l), 30);
    CU_ASSERT_EQUAL(*(int *)listback(l),  20);
    CU_ASSERT_EQUAL(*(int *)listat(l, 1), 10);

    int out = 0;
    CU_ASSERT_EQUAL(listget(l, 2, &out), 0);
    CU_ASSERT_EQUAL(out, 20);

    /* get вне диапазона */
    CU_ASSERT_NOT_EQUAL(listget(l, 3, &out), 0);

    /* at вне диапазона */
    CU_ASSERT_PTR_NULL(listat(l, 3));

    /* очистка */
    listcle(l);
    CU_ASSERT_EQUAL(listsize(l), 0);
    CU_ASSERT_TRUE(listempty(l));

    listdes(l);
}

void test_list_middle_operations(void)
{
    List *l = list(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(l);

    for (int i = 0; i < 6; ++i)
        CU_ASSERT_EQUAL(listpushb(l, &i), 0);   /* [0..5] */

    /* insert в начало */
    int neg = -1;
    CU_ASSERT_EQUAL(listins(l, 0, &neg), 0);    /* [-1,0,1,2,3,4,5] */
    CU_ASSERT_EQUAL(*(int *)listfront(l), -1);

    /* insert в середину */
    int x = 99;
    CU_ASSERT_EQUAL(listins(l, 3, &x), 0);      /* [-1,0,1,99,2,3,4,5] */
    CU_ASSERT_EQUAL(*(int *)listat(l, 3), 99);

    /* insert в конец (позиция == size) */
    int y = 100;
    CU_ASSERT_EQUAL(listins(l, listsize(l), &y), 0);
    CU_ASSERT_EQUAL(*(int *)listback(l), 100);

    /* insert за границу — ошибка */
    CU_ASSERT_NOT_EQUAL(listins(l, listsize(l) + 1, &y), 0);

    /* popf */
    int out = 0;
    CU_ASSERT_EQUAL(listpopf(l, &out), 0);
    CU_ASSERT_EQUAL(out, -1);
    CU_ASSERT_EQUAL(listsize(l), 8);

    /* remove из середины */
    CU_ASSERT_EQUAL(listremove(l, 2, &out), 0);  /* удалили 99 */
    CU_ASSERT_EQUAL(out, 99);

    /* erase по индексу */
    CU_ASSERT_EQUAL(listerase(l, 0), 0);         /* удалили 0 */

    /* eraser диапазона [1, 3) */
    CU_ASSERT_EQUAL(listeraser(l, 1, 3), 0);

    /* проверяем итоговый размер и согласованность first/last */
    size_t n = listsize(l);
    CU_ASSERT_EQUAL(*(int *)listfront(l), 1);
    CU_ASSERT_EQUAL(*(int *)listback(l), 100);
    /* сумма size должна совпадать с ручным подсчётом через at */
    int acc = 0;
    for (size_t i = 0; i < n; ++i) acc += *(int *)listat(l, i);
    CU_ASSERT_EQUAL(acc, _list_sum(l));

    /* remove вне диапазона */
    CU_ASSERT_NOT_EQUAL(listremove(l, n, &out), 0);

    /* eraser с некорректными границами */
    CU_ASSERT_NOT_EQUAL(listeraser(l, 2, 1), 0);
    CU_ASSERT_NOT_EQUAL(listeraser(l, 0, n + 1), 0);

    listdes(l);
}

