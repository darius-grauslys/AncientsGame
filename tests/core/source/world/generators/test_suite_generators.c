#include <world/generators/generators.h>

INCLUDE_SUB_SUITES(generators, 2,
INCLUDE_SUITE(test_suite_generator_flat_world.c),
END_SUITES);

DEFINE_SUITE_WITH__SUB_SUITES(generators, END_TESTS);

