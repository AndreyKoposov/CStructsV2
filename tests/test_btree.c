#include <CUnit/Basic.h>

#include <stdlib.h>

#include "structs/btree.h"
#include "utils/comparators.h"


static int _cmp_scaled(void *a, void *b, void *ctx)
{
    int mul = ctx ? *(int *)ctx : 1;
    int x = *(int *)a * mul, y = *(int *)b * mul;
    return (x > y) - (x < y);
}

static void _assert_sorted(const int *expected, size_t n, BTree *t)
{
    CU_ASSERT_EQUAL_FATAL(btreesize(t), n);
    void *raw = btreetoarr(t);
    CU_ASSERT_PTR_NOT_NULL_FATAL(raw);
    int *out = (int *)raw;
    for (size_t i = 0; i < n; ++i)
        CU_ASSERT_EQUAL(out[i], expected[i]);
    free(raw);   /* btreetoarr возвращает свежий массив */
}

static void _sum_into(void *el, void *ctx)
{
    *(int *)ctx += *(int *)el;
}

static int _tree_sum(BTree *t)
{
    int s = 0;
    btreefor(t, _sum_into, &s);
    return s;
}

static void _sum(void* data, void* ctx) {
    int* val = data;
    int* sum = ctx;

    *sum += *val;
}

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

void test_btree_delete_1(void) {
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

void test_btree_delete_2(void) {
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
    int status = btreedel(t, &a);
    bool cont1 = btreecont(t, &a);

    bool cont2 = btreecont(t, &c);
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

void test_btree_delete_3(void) {
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
    int status = btreedel(t, &e);
    bool cont1 = btreecont(t, &e);

    bool cont2 = btreecont(t, &c);
    bool cont3 = btreecont(t, &b);
    bool cont4 = btreecont(t, &d);
    bool cont5 = btreecont(t, &a);
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

void test_btree_delete_4(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    int e = 1;
    int f = 4;
    int g = 9;
    int h = 8;
    int i = 7;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);
    btreeins(t, &d);
    btreeins(t, &e);
    btreeins(t, &f);
    btreeins(t, &g);
    btreeins(t, &h);
    btreeins(t, &i);

    // Act
    int status = btreedel(t, &h);
    bool cont1 = btreecont(t, &h);

    bool cont2 = btreecont(t, &c);
    bool cont3 = btreecont(t, &b);
    bool cont4 = btreecont(t, &d);
    bool cont5 = btreecont(t, &a);
    bool cont6 = btreecont(t, &f);
    bool cont7 = btreecont(t, &g);
    bool cont8 = btreecont(t, &i);
    bool cont9 = btreecont(t, &e);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_FALSE(cont1);
    CU_ASSERT_EQUAL(btreesize(t), 8);

    CU_ASSERT_TRUE(cont2);
    CU_ASSERT_TRUE(cont3);
    CU_ASSERT_TRUE(cont4);
    CU_ASSERT_TRUE(cont5);
    CU_ASSERT_TRUE(cont6);
    CU_ASSERT_TRUE(cont7);
    CU_ASSERT_TRUE(cont8);
    CU_ASSERT_TRUE(cont9);

    // Clean up
    btreedes(t);
}

void test_btree_delete_5(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    int e = 1;
    int f = 4;
    int g = 9;
    int h = 8;
    int i = 7;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);
    btreeins(t, &d);
    btreeins(t, &e);
    btreeins(t, &f);
    btreeins(t, &g);
    btreeins(t, &h);
    btreeins(t, &i);

    // Act
    int status1 = btreedel(t, &h);
    bool cont1 = btreecont(t, &h);

    int status2 = btreedel(t, &a);
    bool cont2 = btreecont(t, &a);

    int status3 = btreedel(t, &c);
    bool cont3 = btreecont(t, &c);

    bool cont4 = btreecont(t, &b);
    bool cont5 = btreecont(t, &d);
    bool cont6 = btreecont(t, &f);
    bool cont7 = btreecont(t, &g);
    bool cont8 = btreecont(t, &i);
    bool cont9 = btreecont(t, &e);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);
    CU_ASSERT_EQUAL(status3, 0);

    CU_ASSERT_FALSE(cont1);
    CU_ASSERT_FALSE(cont2);
    CU_ASSERT_FALSE(cont3);

    CU_ASSERT_EQUAL(btreesize(t), 6);

    CU_ASSERT_TRUE(cont4);
    CU_ASSERT_TRUE(cont5);
    CU_ASSERT_TRUE(cont6);
    CU_ASSERT_TRUE(cont7);
    CU_ASSERT_TRUE(cont8);
    CU_ASSERT_TRUE(cont9);

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

void test_btree_min_max(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    int e = 4;
    int f = 13;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);
    btreeins(t, &d);
    btreeins(t, &e);
    btreeins(t, &f);

    // Act
    int min, max;
    int status1 = btreemin(t, &min);
    int status2 = btreemax(t, &max);

    // Assert
    CU_ASSERT_EQUAL(status1, 0);
    CU_ASSERT_EQUAL(status2, 0);

    CU_ASSERT_EQUAL(b, min);
    CU_ASSERT_EQUAL(f, max);

    // Clean up
    btreedes(t);
}

void test_btree_for(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    int e = 4;
    int f = 13;

    btreeins(t, &a);
    btreeins(t, &b);
    btreeins(t, &c);
    btreeins(t, &d);
    btreeins(t, &e);
    btreeins(t, &f);

    // Act
    int sum = 0;
    int status = btreefor(t, _sum, &sum);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    CU_ASSERT_EQUAL(sum, a+b+c+d+e+f);

    // Clean up
    btreedes(t);
}

void test_btree_or(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);
    BTree* t2 = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 10;
    int e = 4;
    int f = 13;

    btreeins(t1, &a);
    btreeins(t1, &b);
    btreeins(t1, &c);
    btreeins(t2, &d);
    btreeins(t2, &e);
    btreeins(t2, &f);

    // Act
    int status = btreeor(t1, t2);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    
    CU_ASSERT_TRUE(btreecont(t1, &a));
    CU_ASSERT_TRUE(btreecont(t1, &b));
    CU_ASSERT_TRUE(btreecont(t1, &c));
    CU_ASSERT_TRUE(btreecont(t1, &d));
    CU_ASSERT_TRUE(btreecont(t1, &e));
    CU_ASSERT_TRUE(btreecont(t1, &f));

    // Clean up
    btreedes(t1);
    btreedes(t2);
}

void test_btree_and(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);
    BTree* t2 = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 3;
    int e = 2;
    int f = 13;

    btreeins(t1, &a);
    btreeins(t1, &b);
    btreeins(t1, &c);
    btreeins(t2, &d);
    btreeins(t2, &e);
    btreeins(t2, &f);

    // Act
    int status = btreeand(t1, t2);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    
    CU_ASSERT_TRUE(btreecont(t1, &a));
    CU_ASSERT_TRUE(btreecont(t1, &b));
    
    CU_ASSERT_FALSE(btreecont(t1, &c));
    CU_ASSERT_FALSE(btreecont(t1, &f));

    // Clean up
    btreedes(t1);
    btreedes(t2);
}

void test_btree_xor(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);
    BTree* t2 = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 3;
    int e = 2;
    int f = 13;

    btreeins(t1, &a);
    btreeins(t1, &b);
    btreeins(t1, &c);
    btreeins(t2, &d);
    btreeins(t2, &e);
    btreeins(t2, &f);

    // Act
    int status = btreexor(t1, t2);

    // Assert
    CU_ASSERT_EQUAL(status, 0);
    
    CU_ASSERT_TRUE(btreecont(t1, &c));
    CU_ASSERT_TRUE(btreecont(t1, &f));
    
    CU_ASSERT_FALSE(btreecont(t1, &a));
    CU_ASSERT_FALSE(btreecont(t1, &b));

    // Clean up
    btreedes(t1);
    btreedes(t2);
}

void test_btree_in(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);
    BTree* t2 = btree(sizeof(int), comparator_int, NULL);
    BTree* t3 = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;
    int c = 5;
    int d = 11;
    int e = 7;
    int f = 13;

    btreeins(t1, &a);
    btreeins(t1, &b);
    btreeins(t1, &c);
    btreeins(t1, &d);

    btreeins(t2, &a);
    btreeins(t2, &b);
    btreeins(t2, &c);

    btreeins(t3, &a);
    btreeins(t3, &b);
    btreeins(t3, &e);
    btreeins(t3, &f);

    // Act
    bool status1 = btreein(t2, t1);
    bool status2 = btreein(t3, t1);

    // Assert
    CU_ASSERT_TRUE(status1);
    CU_ASSERT_FALSE(status2);

    // Clean up
    btreedes(t1);
    btreedes(t2);
    btreedes(t3);
}

void test_btree_clear(void) {
    // Arrange
    BTree* t = btree(sizeof(int), comparator_int, NULL);
    int a = 3;
    int b = 2;

    btreeins(t, &a);
    btreeins(t, &b);

    // Act
    int status = btreeclear(t);

    // Assert
    CU_ASSERT_EQUAL(status, 0);

    CU_ASSERT_EQUAL(btreesize(t), 0);

    // Clean up
    btreedes(t);
}

void test_btree_swap(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);
    BTree* t2 = btree(sizeof(int), comparator_int, NULL);

    int a = 3;
    int b = 2;
    int d = 10;

    btreeins(t1, &a);
    btreeins(t1, &b);

    btreeins(t2, &d);

    // Act
    int status = btreeswp(t1, t2);

    // Assert
    CU_ASSERT_EQUAL(status, 0);

    CU_ASSERT_EQUAL(btreesize(t1), 1);
    CU_ASSERT_EQUAL(btreesize(t2), 2);

    CU_ASSERT_TRUE(btreecont(t1, &d));
    CU_ASSERT_TRUE(btreecont(t2, &a));
    CU_ASSERT_TRUE(btreecont(t2, &b));

    // Clean up
    btreedes(t1);
    btreedes(t2);
}

void test_btree_move(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);
    BTree* t2 = btree(sizeof(int), comparator_int, NULL);

    int a = 3;
    int b = 2;
    int d = 10;

    btreeins(t1, &a);
    btreeins(t1, &b);
    btreeins(t1, &d);

    // Act
    int status = btreemove(t2, t1);

    // Assert
    CU_ASSERT_EQUAL(status, 0);

    CU_ASSERT_EQUAL(btreesize(t2), 3);
    CU_ASSERT_EQUAL(btreesize(t1), 0);

    CU_ASSERT_TRUE(btreecont(t2, &d));
    CU_ASSERT_TRUE(btreecont(t2, &a));
    CU_ASSERT_TRUE(btreecont(t2, &b));

    CU_ASSERT_FALSE(btreecont(t1, &a));

    // Clean up
    btreedes(t1);
    btreedes(t2);
}

void test_btree_to_array(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);

    int a = 3;
    int b = 2;
    int d = 10;

    btreeins(t1, &a);
    btreeins(t1, &b);
    btreeins(t1, &d);

    // Act
    int* arr = btreetoarr(t1);

    // Assert
    CU_ASSERT_PTR_NOT_NULL_FATAL(arr);

    CU_ASSERT_EQUAL(arr[0], 2);
    CU_ASSERT_EQUAL(arr[1], 3);
    CU_ASSERT_EQUAL(arr[2], 10);

    // Clean up
    btreedes(t1);
    free(arr);
}

void test_btree_from_array(void) {
    // Arrange
    int arr[5] = {1,3,2,5,4};

    // Act
    BTree* t = btreefromarr(arr, 5, sizeof(int), comparator_int, NULL);

    // Assert
    CU_ASSERT_PTR_NOT_NULL_FATAL(t);

    CU_ASSERT_EQUAL(btreesize(t), 5);

    int a = 1;
    int b = 3;
    int c = 2;
    int d = 5;
    int e = 4;

    CU_ASSERT_TRUE(btreecont(t, &a));
    CU_ASSERT_TRUE(btreecont(t, &b));
    CU_ASSERT_TRUE(btreecont(t, &c));
    CU_ASSERT_TRUE(btreecont(t, &d));
    CU_ASSERT_TRUE(btreecont(t, &e));

    // Clean up
    btreedes(t);
}

void test_btree_equals(void) {
    // Arrange
    BTree* t1 = btree(sizeof(int), comparator_int, NULL);
    BTree* t2 = btree(sizeof(int), comparator_int, NULL);
    BTree* t3 = btree(sizeof(int), comparator_int, NULL);

    int a = 3;
    int b = 2;
    int d = 10;

    btreeins(t1, &a);
    btreeins(t1, &b);
    btreeins(t1, &d);

    btreeins(t2, &a);
    btreeins(t2, &b);
    btreeins(t2, &d);

    btreeins(t3, &a);
    btreeins(t3, &b);

    // Act
    bool status1 = btreeeq(t1, t2);
    bool status2 = btreeeq(t1, t3);

    // Assert
    CU_ASSERT_TRUE(status1);
    CU_ASSERT_FALSE(status2);

    // Clean up
    btreedes(t1);
    btreedes(t2);
    btreedes(t3);
}

void test_btree_basic_lifecycle(void) {
    BTree *t = btree(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(t);

    CU_ASSERT_EQUAL(btreesize(t), 0);

    int v[] = { 50, 30, 70, 20, 40, 60, 80 };
    for (size_t i = 0; i < 7; ++i)
        CU_ASSERT_EQUAL(btreeins(t, &v[i]), 0);

    CU_ASSERT_EQUAL(btreesize(t), 7);

    /* containment */
    for (size_t i = 0; i < 7; ++i)
        CU_ASSERT_TRUE(btreecont(t, &v[i]));

    int missing = 99;
    CU_ASSERT_FALSE(btreecont(t, &missing));

    /* повторная вставка дубликата должна быть отвергнута (множество) */
    CU_ASSERT_NOT_EQUAL(btreeins(t, &v[0]), 0);
    CU_ASSERT_EQUAL(btreesize(t), 7);

    /* min/max */
    int mn = 0, mx = 0;
    CU_ASSERT_EQUAL(btreemin(t, &mn), 0);
    CU_ASSERT_EQUAL(btreemax(t, &mx), 0);
    CU_ASSERT_EQUAL(mn, 20);
    CU_ASSERT_EQUAL(mx, 80);

    /* at по возрастанию: 20,30,40,50,60,70,80 */
    int expected[] = { 20, 30, 40, 50, 60, 70, 80 };
    for (size_t i = 0; i < 7; ++i) {
        int out = 0;
        CU_ASSERT_EQUAL(btreeat(t, i, &out), 0);
        CU_ASSERT_EQUAL(out, expected[i]);
    }
    /* at вне диапазона */
    int out;
    CU_ASSERT_NOT_EQUAL(btreeat(t, 7, &out), 0);

    /* обход: сумма всех элементов */
    CU_ASSERT_EQUAL(_tree_sum(t), 20+30+40+50+60+70+80);

    /* min/max на пустом дереве */
    BTree *e = btree(sizeof(int), comparator_int, NULL);
    CU_ASSERT_NOT_EQUAL(btreemin(e, &mn), 0);
    CU_ASSERT_NOT_EQUAL(btreemax(e, &mx), 0);
    btreedes(e);

    btreedes(t);
}

void test_btree_delete_cases(void) {
    BTree *t = btree(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(t);

    int v[] = { 50, 30, 70, 20, 40, 60, 80, 35, 45 };
    for (size_t i = 0; i < 9; ++i)
        CU_ASSERT_EQUAL(btreeins(t, &v[i]), 0);
    CU_ASSERT_EQUAL(btreesize(t), 9);

    /* лист */
    int leaf = 20;
    CU_ASSERT_EQUAL(btreedel(t, &leaf), 0);
    CU_ASSERT_FALSE(btreecont(t, &leaf));
    CU_ASSERT_EQUAL(btreesize(t), 8);

    /* узел с одним ребёнком (35 — лист, 40 — с детьми 35,45) */
    int one = 40;
    CU_ASSERT_EQUAL(btreedel(t, &one), 0);
    CU_ASSERT_FALSE(btreecont(t, &one));
    CU_ASSERT_EQUAL(btreesize(t), 7);

    /* узел с двумя детьми (50 — корень) */
    int root = 50;
    CU_ASSERT_EQUAL(btreedel(t, &root), 0);
    CU_ASSERT_FALSE(btreecont(t, &root));
    CU_ASSERT_EQUAL(btreesize(t), 6);

    /* удаление отсутствующего */
    int missing = 999;
    CU_ASSERT_EQUAL(btreedel(t, &missing), 0);
    CU_ASSERT_EQUAL(btreesize(t), 6);

    /* после всех удалений дерево всё ещё отсортировано и цело */
    int expected[] = { 30, 35, 45, 60, 70, 80 };
    _assert_sorted(expected, 6, t);

    btreedes(t);
}

void test_btree_subset(void) {
    int big_arr[] = { 1, 2, 3, 4, 5 };
    int sub_arr[] = { 2, 4 };
    int disjoint_arr[] = { 7, 8 };
    int self_arr[] = { 1, 2, 3, 4, 5 };

    BTree *big = btreefromarr(big_arr, 5, sizeof(int), comparator_int, NULL);
    BTree *sub = btreefromarr(sub_arr, 2, sizeof(int), comparator_int, NULL);
    BTree *dis = btreefromarr(disjoint_arr, 2, sizeof(int), comparator_int, NULL);
    BTree *self = btreefromarr(self_arr, 5, sizeof(int), comparator_int, NULL);

    CU_ASSERT_TRUE(btreein(sub, big));      /* подмножество */
    CU_ASSERT_FALSE(btreein(big, sub));     /* не наоборот */
    CU_ASSERT_FALSE(btreein(dis, big));     /* непересекающиеся */
    CU_ASSERT_TRUE(btreein(big, self));     /* равные множества — подмножество */
    CU_ASSERT_TRUE(btreein(self, big));

    /* пустое множество — подмножество любого */
    BTree *empty = btree(sizeof(int), comparator_int, NULL);
    CU_ASSERT_TRUE(btreein(empty, big));
    CU_ASSERT_FALSE(btreein(big, empty));   /* если big непусто */

    btreedes(big);
    btreedes(sub);
    btreedes(dis);
    btreedes(self);
    btreedes(empty);
}

void test_btree_copy_semantics(void) {
    int mul = -1;
    int vals[] = { 5, 3, 8, 1, 9 };

    BTree *src = btree(sizeof(int), _cmp_scaled, &mul);
    CU_ASSERT_PTR_NOT_NULL_FATAL(src);
    for (size_t i = 0; i < 5; ++i)
        CU_ASSERT_EQUAL(btreeins(src, &vals[i]), 0);

    /* clone: независимая копия, равная по содержимому */
    BTree *clone = btreeclone(src);
    CU_ASSERT_PTR_NOT_NULL_FATAL(clone);
    CU_ASSERT_TRUE(btreeeq(src, clone));

    /* изменение клона не влияет на оригинал */
    int extra = 100;
    CU_ASSERT_EQUAL(btreeins(clone, &extra), 0);
    CU_ASSERT_FALSE(btreeeq(src, clone));
    CU_ASSERT_EQUAL(btreesize(src), 5);
    CU_ASSERT_EQUAL(btreesize(clone), 6);

    /* swap: обмен содержимым */
    BTree *other = btree(sizeof(int), _cmp_scaled, &mul);
    CU_ASSERT_PTR_NOT_NULL_FATAL(other);
    CU_ASSERT_EQUAL(btreeswp(src, other), 0);
    CU_ASSERT_EQUAL(btreesize(src), 0);
    CU_ASSERT_EQUAL(btreesize(other), 5);
    CU_ASSERT_TRUE(btreeeq(other, clone) == false); /* clone имеет 6 */

    /* move: владение переезжает, src обнуляется */
    BTree *moved = btree(sizeof(int), _cmp_scaled, &mul);
    CU_ASSERT_PTR_NOT_NULL_FATAL(moved);
    CU_ASSERT_EQUAL(btreemove(moved, other), 0);
    CU_ASSERT_EQUAL(btreesize(moved), 5);
    CU_ASSERT_EQUAL(btreesize(other), 0);
    CU_ASSERT_TRUE(btreeeq(moved, clone) == false);

    /* проверяем, что cmp_scaled с mul=-1 доехал:
       min/max инвертированы относительно натурального порядка.
       При mul=-1 «минимум» cmp_scaled — это 9, «максимум» — 1. */
    int mn = 0, mx = 0;
    CU_ASSERT_EQUAL(btreemin(moved, &mn), 0);
    CU_ASSERT_EQUAL(btreemax(moved, &mx), 0);
    CU_ASSERT_EQUAL(mn, 9);
    CU_ASSERT_EQUAL(mx, 1);

    btreedes(src);
    btreedes(clone);
    btreedes(other);
    btreedes(moved);
}

void test_btree_array_roundtrip(void) {
    int arr[] = { 4, 1, 3, 2, 5 };
    BTree *t = btreefromarr(arr, 5, sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(t);
    CU_ASSERT_EQUAL(btreesize(t), 5);

    /* модификация исходного массива не влияет */
    arr[0] = 999;
    int check = 4;
    CU_ASSERT_TRUE(btreecont(t, &check));

    /* toarr возвращает отсортированный массив */
    int expected[] = { 1, 2, 3, 4, 5 };
    _assert_sorted(expected, 5, t);

    /* пустой массив -> пустое дерево */
    BTree *e = btreefromarr(NULL, 0, sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(e);
    CU_ASSERT_EQUAL(btreesize(e), 0);

    /* btreetoarr пустого дерева — либо NULL, либо пустой буфер */
    void *raw = btreetoarr(e);
    if (raw) free(raw);

    btreedes(t);
    btreedes(e);
}

void test_btree_error_paths(void) {
    BTree *t = btree(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(t);

    int x = 1, out = 0;

    /* del/at/min/max/cont на пустом */
    CU_ASSERT_EQUAL(btreedel(t, &x), 0);
    CU_ASSERT_NOT_EQUAL(btreeat(t, 0, &out), 0);
    CU_ASSERT_NOT_EQUAL(btreemin(t, &out), 0);
    CU_ASSERT_NOT_EQUAL(btreemax(t, &out), 0);
    CU_ASSERT_FALSE(btreecont(t, &x));

    /* eq пустых */
    BTree *e = btree(sizeof(int), comparator_int, NULL);
    CU_ASSERT_TRUE(btreeeq(t, e));

    /* eq разного размера */
    btreeins(t, &x);
    CU_ASSERT_FALSE(btreeeq(t, e));
    btreeins(e, &x);
    CU_ASSERT_TRUE(btreeeq(t, e));

    /* fromarr с len=0 */
    BTree *z = btreefromarr(NULL, 0, sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(z);
    CU_ASSERT_EQUAL(btreesize(z), 0);

    /* clone пустого */
    BTree *zc = btreeclone(z);
    CU_ASSERT_PTR_NOT_NULL_FATAL(zc);
    CU_ASSERT_TRUE(btreeeq(z, zc));

    btreedes(t);
    btreedes(e);
    btreedes(z);
    btreedes(zc);
}

void test_btree_end_to_end(void) {
    /* «теги статьи»: два набора, объединяем, фильтруем, сравниваем */

    int tags_a[] = { 10, 20, 30, 40 };
    int tags_b[] = { 30, 40, 50, 60 };

    BTree *a = btreefromarr(tags_a, 4, sizeof(int), comparator_int, NULL);
    BTree *b = btreefromarr(tags_b, 4, sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(a);
    CU_ASSERT_PTR_NOT_NULL_FATAL(b);

    /* общие теги: and */
    BTree *common = btreeclone(a);
    CU_ASSERT_EQUAL(btreeand(common, b), 0);
    int expected_common[] = { 30, 40 };
    _assert_sorted(expected_common, 2, common);

    /* объединение */
    BTree *united = btreeclone(a);
    CU_ASSERT_EQUAL(btreeor(united, b), 0);
    CU_ASSERT_EQUAL(btreesize(united), 6);

    /* асимметричная разность */
    BTree *sym = btreeclone(a);
    CU_ASSERT_EQUAL(btreexor(sym, b), 0);
    int expected_sym[] = { 10, 20, 50, 60 };
    _assert_sorted(expected_sym, 4, sym);

    /* common — подмножество united, но не наоборот */
    CU_ASSERT_TRUE(btreein(common, united));
    CU_ASSERT_FALSE(btreein(united, common));

    /* удаляем один общий тег из united и проверяем, что common теперь
       не подмножество */
    int drop = 30;
    CU_ASSERT_EQUAL(btreedel(united, &drop), 0);
    CU_ASSERT_FALSE(btreein(common, united));

    /* клонируем united, двигаем в новый, сравниваем */
    BTree *snapshot = btreeclone(united);
    CU_ASSERT_TRUE(btreeeq(united, snapshot));

    BTree *moved = btree(sizeof(int), comparator_int, NULL);
    CU_ASSERT_PTR_NOT_NULL_FATAL(moved);
    CU_ASSERT_EQUAL(btreemove(moved, snapshot), 0);
    CU_ASSERT_EQUAL(btreesize(snapshot), 0);
    CU_ASSERT_TRUE(btreeeq(united, moved));

    /* очистка */
    CU_ASSERT_EQUAL(btreeclear(united), 0);
    CU_ASSERT_EQUAL(btreesize(united), 0);

    btreedes(a);
    btreedes(b);
    btreedes(common);
    btreedes(united);
    btreedes(sym);
    btreedes(snapshot);
    btreedes(moved);
}