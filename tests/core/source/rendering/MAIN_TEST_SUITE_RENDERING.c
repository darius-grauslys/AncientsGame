#include <rendering/MAIN_TEST_SUITE_RENDERING.h>

INCLUDE_SUB_SUITES(RENDERING, 4,
INCLUDE_SUITE(animate_sprite),
INCLUDE_SUITE(sprite),
INCLUDE_SUITE(animate_entity),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(RENDERING, END_TESTS);

