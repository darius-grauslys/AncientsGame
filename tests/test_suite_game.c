#include <test_suite_game.h>

#include <game.c>

#warning Please make tests for: /home/shalidor/Projects/AncientsGame/tests/core/source/test_suite_game.c

TEST_FUNCTION(is_true) {
    munit_assert_true(false);
}

// Before writing any tests, please see the README
// found in ./tests

DEFINE_SUITE(game, INCLUDE_TEST__STATELESS(is_true), END_TESTS)
