#include <string.h>
#include <CUnit/Basic.h>

#include "test_vector.h"
#include "test_btree.h"
#include "test_list.h"


CU_ErrorCode cleanup() {
    CU_cleanup_registry();
    return CU_get_error();
}

int main(int argc, char* argv[]) {
    char* suite;
    if (argc == 1)
        suite = "all";
    else
        suite = argv[1];

    CU_pSuite vectorS = NULL;
    CU_pSuite btreeS = NULL;
    CU_pSuite listS = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    vectorS = CU_add_suite("Vector", NULL, NULL);
    if (vectorS == NULL) cleanup();

    btreeS = CU_add_suite("Binary Tree", NULL, NULL);
    if (btreeS == NULL) cleanup();

    listS = CU_add_suite("List", NULL, NULL);
    if (listS == NULL) cleanup();

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
    if (!CU_add_test(vectorS, "Find", test_vector_find)) cleanup();
    if (!CU_add_test(vectorS, "Different types", test_different_types)) cleanup();
    if (!CU_add_test(vectorS, "Basic lifecycle", test_basic_lifecycle)) cleanup();
    if (!CU_add_test(vectorS, "Modifications", test_modifications)) cleanup();
    if (!CU_add_test(vectorS, "Copy semantics", test_copy_semantics)) cleanup();
    if (!CU_add_test(vectorS, "Min/Max/Sort", test_min_max_sort)) cleanup();
    if (!CU_add_test(vectorS, "Array conversations", test_array_conversions)) cleanup();
    if (!CU_add_test(vectorS, "Errors", test_error_paths)) cleanup();
    if (!CU_add_test(vectorS, "End to end", test_end_to_end)) cleanup();
    if (!CU_add_test(vectorS, "Comparator copy", test_copy_preserves_comparator_behavioral)) cleanup();

    if (!CU_add_test(btreeS, "Insert", test_btree_insert)) cleanup();
    if (!CU_add_test(btreeS, "Search", test_btree_search)) cleanup();

    if (!CU_add_test(listS, "Push front/back", test_list_push)) cleanup();
    if (!CU_add_test(listS, "Insert", test_list_insert)) cleanup();
    if (!CU_add_test(listS, "Pop front", test_list_pop)) cleanup();
    if (!CU_add_test(listS, "Remove", test_list_remove)) cleanup();
    if (!CU_add_test(listS, "Empty", test_list_empty)) cleanup();
    if (!CU_add_test(listS, "Find", test_list_find)) cleanup();
    if (!CU_add_test(listS, "At", test_list_at)) cleanup();
    if (!CU_add_test(listS, "First/Last", test_list_first_last)) cleanup();
    if (!CU_add_test(listS, "For", test_list_for)) cleanup();
    if (!CU_add_test(listS, "Erase range", test_list_eraser)) cleanup();
    if (!CU_add_test(listS, "Clone", test_list_clone)) cleanup();
    if (!CU_add_test(listS, "Copy", test_list_copy)) cleanup();
    if (!CU_add_test(listS, "Swap", test_list_swap)) cleanup();
    if (!CU_add_test(listS, "Move", test_list_move)) cleanup();
    if (!CU_add_test(listS, "Equals", test_list_equals)) cleanup();
    if (!CU_add_test(listS, "Max/Min", test_list_min_max)) cleanup();
    if (!CU_add_test(listS, "Sort", test_list_sort)) cleanup();
    if (!CU_add_test(listS, "To array", test_list_to_array)) cleanup();
    if (!CU_add_test(listS, "From array", test_list_from_array)) cleanup();
    if (!CU_add_test(listS, "Link", test_list_link)) cleanup();
    if (!CU_add_test(listS, "Basic lifecycle", test_list_basic_lifecycle)) cleanup();
    if (!CU_add_test(listS, "Middle operations", test_list_middle_operations)) cleanup();

    CU_basic_set_mode(CU_BRM_VERBOSE);

    if (strcmp(suite, "vector") == 0) CU_basic_run_suite(vectorS);
    if (strcmp(suite, "btree") == 0) CU_basic_run_suite(btreeS);
    if (strcmp(suite, "list") == 0) CU_basic_run_suite(listS);
    if (strcmp(suite, "all") == 0) CU_basic_run_tests();

    cleanup();
}