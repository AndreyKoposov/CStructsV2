#include <CUnit/Basic.h>

#include "test_vector.h"


CU_ErrorCode cleanup() {
    CU_cleanup_registry();
    return CU_get_error();
}

int main() {
    CU_pSuite vectorS = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    vectorS = CU_add_suite("Vector", NULL, NULL);
    if (vectorS == NULL) cleanup();

    if (!CU_add_test(vectorS, "Create", test_create)) cleanup();
    if (!CU_add_test(vectorS, "Destroy", test_destroy)) cleanup();
    if (!CU_add_test(vectorS, "Reserve", test_reserve)) cleanup();
    if (!CU_add_test(vectorS, "Shrink", test_shrink)) cleanup();
    if (!CU_add_test(vectorS, "Push", test_push)) cleanup();
    if (!CU_add_test(vectorS, "Pop", test_pop)) cleanup();
    if (!CU_add_test(vectorS, "At", test_at)) cleanup();
    if (!CU_add_test(vectorS, "Back", test_back)) cleanup();
    if (!CU_add_test(vectorS, "Get", test_get)) cleanup();
    if (!CU_add_test(vectorS, "Foreach", test_for)) cleanup();
    if (!CU_add_test(vectorS, "Insert", test_insert)) cleanup();
    if (!CU_add_test(vectorS, "Erase", test_erase)) cleanup();
    if (!CU_add_test(vectorS, "Erase range", test_erase_range)) cleanup();
    if (!CU_add_test(vectorS, "Copy", test_copy)) cleanup();
    if (!CU_add_test(vectorS, "Clone", test_clone)) cleanup();
    if (!CU_add_test(vectorS, "Swap", test_swap)) cleanup();
    if (!CU_add_test(vectorS, "Equals", test_equals)) cleanup();
    if (!CU_add_test(vectorS, "Move", test_move)) cleanup();
    if (!CU_add_test(vectorS, "Max/Min", test_max_min)) cleanup();
    if (!CU_add_test(vectorS, "Sort", test_sort)) cleanup();
    if (!CU_add_test(vectorS, "From/To array", test_from_to_array)) cleanup();
    if (!CU_add_test(vectorS, "Different types", test_different_types)) cleanup();
    if (!CU_add_test(vectorS, "Basic lifecycle", test_basic_lifecycle)) cleanup();
    if (!CU_add_test(vectorS, "Modifications", test_modifications)) cleanup();
    if (!CU_add_test(vectorS, "Copy semantics", test_copy_semantics)) cleanup();
    if (!CU_add_test(vectorS, "Min/Max/Sort", test_min_max_sort)) cleanup();
    if (!CU_add_test(vectorS, "Array conversations", test_array_conversions)) cleanup();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    cleanup();
}