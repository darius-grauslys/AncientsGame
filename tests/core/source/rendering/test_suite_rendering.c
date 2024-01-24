#include <rendering/rendering.h>

INCLUDE_SUB_SUITES(rendering, 4,
INCLUDE_SUITE(test_suite_animate_sprite.c),

INCLUDE_SUITE(test_suite_sprite.c),

INCLUDE_SUITE(test_suite_animate_entity.c),
END_SUITES);

DEFINE_SUITE_WITH__SUB_SUITES(rendering, END_TESTS);

