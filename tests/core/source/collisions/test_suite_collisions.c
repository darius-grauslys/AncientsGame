#include <collisions/collisions.h>

INCLUDE_SUB_SUITES(collisions, 3,
INCLUDE_SUITE(test_suite_collision_manager.c),

INCLUDE_SUITE(test_suite_hitbox_aabb.c),
END_SUITES);

DEFINE_SUITE_WITH__SUB_SUITES(collisions, END_TESTS);

