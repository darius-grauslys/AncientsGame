#include <world/test_suite_chunk_manager.h>

#include <world/chunk_manager.c>

#warning Please make tests for: /home/shalidor/Projects/AncientsGame/tests/core/source/world/test_suite_chunk_manager.c

// Before writing any tests, please see the README
// found in ./tests

TEST_FUNCTION(get_chunk_index_from__chunk_manager) {
    return MUNIT_OK;
}

TEST_FUNCTION(get_chunk_from__chunk_manager) {
    return MUNIT_OK;
}

DEFINE_SUITE(chunk_manager, 
        INLCUDE_TEST
            (get_chunk_index_at__xyz_from__chunk_manager),
        INLCUDE_TEST
            (get_chunk_from__chunk_manager),
        END_TESTS)
