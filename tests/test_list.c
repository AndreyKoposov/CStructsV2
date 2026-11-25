#include <stdlib.h>
#include <CUnit/Basic.h>

#include "structs/list.h"
#include "utils/comparators.h"


static int _cmp_scaled(void *a, void *b, void *ctx)
{
    int mul = ctx ? *(int *)ctx : 1;
    int x = *(int *)a * mul, y = *(int *)b * mul;
    return (x > y) - (x < y);
}

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

static void _assert_list_equals(List *l, const int *expected, size_t n)
{
    CU_ASSERT_EQUAL_FATAL(listsize(l), n);
    for (size_t i = 0; i < n; ++i) {
        int v = 0;
        CU_ASSERT_EQUAL_FATAL(listget(l, i, &v), 0);
        CU_ASSERT_EQUAL(v, expected[i]);
    }
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

void test_list_find_minmax_sort(void) {
    List *l = list(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(l);

    int data[] = { 5, 3, 9, 3, 1, 9, 7 };
    for (size_t i = 0; i < sizeof(data)/sizeof(data[0]); ++i)
        CU_ASSERT_EQUAL(listpushb(l, &data[i]), 0);

    /* find: первое вхождение 3 — индекс 1 */
    int target = 3;
    size_t pos = (size_t)-1;
    CU_ASSERT_EQUAL(listfind(l, &target, &pos), 0);
    CU_ASSERT_EQUAL(pos, 1);

    /* find несуществующего */
    int missing = 42;
    CU_ASSERT_NOT_EQUAL(listfind(l, &missing, &pos), 0);

    /* max: 9, первый индекс 2 */
    int maxv = 0; size_t maxi = (size_t)-1;
    CU_ASSERT_EQUAL(listmax(l, &maxv, &maxi), 0);
    CU_ASSERT_EQUAL(maxv, 9);
    CU_ASSERT_EQUAL(maxi, 2);

    /* min: 1, индекс 4 */
    int minv = 0; size_t mini = (size_t)-1;
    CU_ASSERT_EQUAL(listmin(l, &minv, &mini), 0);
    CU_ASSERT_EQUAL(minv, 1);
    CU_ASSERT_EQUAL(mini, 4);

    /* sort */
    CU_ASSERT_EQUAL(listsort(l), 0);
    int sorted[] = { 1, 3, 3, 5, 7, 9, 9 };
    _assert_list_equals(l, sorted, 7);

    /* после сортировки min/max на краях */
    CU_ASSERT_EQUAL(listmin(l, &minv, &mini), 0);
    CU_ASSERT_EQUAL(mini, 0);
    CU_ASSERT_EQUAL(listmax(l, &maxv, &maxi), 0);
    CU_ASSERT_EQUAL(maxi, 5);

    /* max/min на пустом */
    listcle(l);
    CU_ASSERT_NOT_EQUAL(listmax(l, &maxv, &maxi), 0);
    CU_ASSERT_NOT_EQUAL(listmin(l, &minv, &mini), 0);

    listdes(l);
}

void test_list_copy_semantics(void) {
    int mul = -1;

    List *src = list(sizeof(int), _cmp_scaled, &mul);
    CU_ASSERT_PTR_NOT_NULL_FATAL(src);

    for (int i = 1; i <= 5; ++i)
        CU_ASSERT_EQUAL(listpushb(src, &i), 0);

    /* clone: независимая копия + comp/ctx сохранены */
    List *clone = listclone(src);
    CU_ASSERT_PTR_NOT_NULL_FATAL(clone);
    CU_ASSERT_TRUE(listeq(src, clone, NULL));

    /* изменяем clone — src не должен меняться */
    int z = 100;
    CU_ASSERT_EQUAL(listpushb(clone, &z), 0);
    CU_ASSERT_FALSE(listeq(src, clone, NULL));
    CU_ASSERT_EQUAL(listsize(src), 5);
    CU_ASSERT_EQUAL(listsize(clone), 6);

    /* copy: dst получает данные src, comp/ctx тоже */
    List *dst = list(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(dst);
    CU_ASSERT_EQUAL(listcpy(dst, src), 0);
    CU_ASSERT_TRUE(listeq(dst, src, NULL));

    /* swap */
    CU_ASSERT_EQUAL(listswp(dst, clone), 0);
    CU_ASSERT_EQUAL(listsize(dst), 6);
    CU_ASSERT_EQUAL(listsize(clone), 5);
    CU_ASSERT_TRUE(listeq(clone, src, NULL));

    /* move: dst получает владение, src обнуляется */
    List *moved = list(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(moved);
    CU_ASSERT_EQUAL(listmove(moved, src), 0);
    CU_ASSERT_TRUE(listeq(moved, clone, NULL));
    CU_ASSERT_EQUAL(listsize(src), 0);
    CU_ASSERT_TRUE(listempty(src));

    /* проверяем, что comp_scaled реально доехал: сортировка по убыванию
       (mul = -1), а не по возрастанию */
    CU_ASSERT_EQUAL(listsort(moved), 0);
    /* при mul=-1 «возрастание» = 5,4,3,2,1 */
    CU_ASSERT_TRUE(*(int *)listat(moved, 0) > *(int *)listat(moved, listsize(moved) - 1));

    listdes(src);
    listdes(clone);
    listdes(dst);
    listdes(moved);
}

void test_list_array_roundtrip(void) {
    int arr[] = { 4, 1, 3, 2, 5 };

    List *l = listfromarr(arr, 5, sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(l);
    CU_ASSERT_EQUAL(listsize(l), 5);
    CU_ASSERT_EQUAL(*(int *)listat(l, 0), 4);
    CU_ASSERT_EQUAL(*(int *)listback(l), 5);

    /* модификация исходного массива не влияет (глубокая копия) */
    arr[0] = 999;
    CU_ASSERT_EQUAL(*(int *)listat(l, 0), 4);

    /* сортируем и извлекаем в массив */
    CU_ASSERT_EQUAL(listsort(l), 0);

    void *raw = listtoarr(l);
    CU_ASSERT_PTR_NOT_NULL_FATAL(raw);
    int *out = (int *)raw;
    for (int i = 0; i < 5; ++i)
        CU_ASSERT_EQUAL(out[i], i + 1);

    /* если listtoarr возвращает свежий malloc — освобождаем;
       если внутренний указатель — не трогаем. Проверим, что это не
       тот же буфер, что listat(0) */
    if (out != (int *)listat(l, 0))
        free(out);

    listdes(l);
}

void test_list_error_paths(void) {
    List *l = list(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(l);

    int x = 1, out = 0;

    /* popf из пустого */
    CU_ASSERT_NOT_EQUAL(listpopf(l, &out), 0);

    /* remove/erase/eraser на пустом */
    CU_ASSERT_NOT_EQUAL(listremove(l, 0, &out), 0);
    CU_ASSERT_NOT_EQUAL(listerase(l, 0), 0);
    CU_ASSERT_NOT_EQUAL(listeraser(l, 0, 1), 0);

    /* insert в пустой по индексу 0 — допустимо, но по индексу 5 — нет */
    CU_ASSERT_NOT_EQUAL(listins(l, 5, &x), 0);

    /* eq списков разной длины */
    List *a = list(sizeof(int), comparator_int, NULL);
    List *b = list(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(a);
    CU_ASSERT_PTR_NOT_NULL_FATAL(b);
    listpushb(a, &x);
    CU_ASSERT_FALSE(listeq(a, b, NULL));
    listpushb(b, &x);
    CU_ASSERT_TRUE(listeq(a, b, NULL));

    /* clone пустого */
    listpopf(b, NULL);
    List *e = listclone(b);
    CU_ASSERT_PTR_NOT_NULL_FATAL(e);
    CU_ASSERT_TRUE(listempty(e));
    CU_ASSERT_TRUE(listeq(e, b, NULL));

    /* listfromarr с len = 0 */
    List *z = listfromarr(NULL, 0, sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NULL(z);

    /* listtoarr пустого — либо NULL, либо валидный пустой буфер */
    void *raw = listtoarr(z);
    (void)raw;

    listdes(l);
    listdes(a);
    listdes(b);
    listdes(e);
    listdes(z);
}

void test_list_end_to_end(void) {
    /* сценарий: «журнал событий» — накапливаем, фильтруем, сортируем,
       клонируем снимок, сливаем с дополнительным журналом */

    int initial[] = { 10, -5, 7, 0, 3, -1, 8 };
    List *log = listfromarr(initial, 7, sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(log);

    /* добавим ещё событий в начало и конец */
    int first = 100;
    listpushf(log, &first);
    int last_arr[] = { 4, -2, 6 };
    for (int i = 0; i < 3; ++i)
        listpushb(log, &last_arr[i]);

    CU_ASSERT_EQUAL(listsize(log), 11);

    /* удалим отрицательные через итерацию с конца:
       listremove сохраняет стабильность индексов, идём с конца */
    for (size_t i = listsize(log); i > 0; --i) {
        int v = 0;
        CU_ASSERT_EQUAL(listget(log, i - 1, &v), 0);
        if (v < 0)
            CU_ASSERT_EQUAL(listerase(log, i - 1), 0);
    }

    /* все >= 0 */
    for (size_t i = 0; i < listsize(log); ++i)
        CU_ASSERT_TRUE(*(int *)listat(log, i) >= 0);

    /* сортируем */
    CU_ASSERT_EQUAL(listsort(log), 0);
    for (size_t i = 1; i < listsize(log); ++i) {
        int prev = 0, cur = 0;
        listget(log, i - 1, &prev);
        listget(log, i, &cur);
        CU_ASSERT_TRUE(prev <= cur);
    }

    /* клонируем снимок */
    List *snapshot = listclone(log);
    CU_ASSERT_PTR_NOT_NULL_FATAL(snapshot);
    CU_ASSERT_TRUE(listeq(log, snapshot, NULL));

    /* сливаем с дополнительным журналом */
    int extra[] = { 50, 2, 70 };
    List *extra_l = listfromarr(extra, 3, sizeof(int), comparator_int, NULL);
    CU_ASSERT_EQUAL(listlink(snapshot, extra_l), 0);
    CU_ASSERT_EQUAL(listsize(snapshot), listsize(log) + 3);

    /* min/max на объединённом */
    int mn = 0, mx = 0; size_t mni, mxi;
    CU_ASSERT_EQUAL(listmin(snapshot, &mn, &mni), 0);
    CU_ASSERT_EQUAL(listmax(snapshot, &mx, &mxi), 0);
    CU_ASSERT_EQUAL(mn, 0);
    CU_ASSERT_EQUAL(mx, 100);

    listdes(log);
    listdes(snapshot);
}
