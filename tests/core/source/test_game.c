#include <game.c>

#include <test_util.h>
#include <collisions/test_suite_collisions.h>

MunitTest main_tests[] = {
    END_TESTS
};
MunitSuite sub_suites[2];
const char *main_suite__prefix = "ancients_game";

void init_test_suite__ancients_game(MunitSuite *test_suite) {
    test_suite->prefix = main_suite__prefix;
    test_suite->tests = main_tests;
    test_suite->iterations = 1;
    test_suite->options = MUNIT_SUITE_OPTION_NONE;
    test_suite->suites = sub_suites;
    include_test_suite__collision_manager(
            &sub_suites[0]);
    sub_suites[1] = END_SUITES;
}
