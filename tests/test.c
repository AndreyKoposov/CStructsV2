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

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    cleanup();
}