#include <world/world.h>

INCLUDE_SUB_SUITES(world, 7,
INCLUDE_SUITE(test_suite_tile.c),

INCLUDE_SUITE(test_suite_chunk.c),

INCLUDE_SUITE(test_suite_world_parameters.c),

INCLUDE_SUITE(test_suite_chunk_manager.c),

INCLUDE_SUITE(generators),
END_SUITES);

DEFINE_SUITE_WITH__SUB_SUITES(world, END_TESTS);

