#include <world/MAIN_TEST_SUITE_WORLD.h>

INCLUDE_SUB_SUITES(WORLD, 7,
INCLUDE_SUITE(tile),
INCLUDE_SUITE(chunk),
INCLUDE_SUITE(world),
INCLUDE_SUITE(world_parameters),
INCLUDE_SUITE(chunk_manager),
INCLUDE_SUITE(GENERATORS),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(WORLD, END_TESTS);
