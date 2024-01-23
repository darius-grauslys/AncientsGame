#include <collisions/collision_manager.c>
#include <collisions/test_suite_collisions.h>
#include <test_util.h>

TEST_FUNCTION(is_true) {
    return MUNIT_OK;
}

// DEFINE_SUITE(collision_manager, INCLUDE_TEST__STATELESS(is_true));
DEFINE_SUITE(collision_manager, END_TESTS);
