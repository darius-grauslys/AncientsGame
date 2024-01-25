#include <MAIN_TEST_SUITE_ANCIENTS_GAME.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    MunitSuite test_suite;

    include_test_suite__ANCIENTS_GAME(&test_suite);

    return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
