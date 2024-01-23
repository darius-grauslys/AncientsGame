
#include <munit.h>
#include <defines.h>

#include <test_suite_ancient_game.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    MunitSuite test_suite;

    init_test_suite__ancients_game(&test_suite);

    return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
