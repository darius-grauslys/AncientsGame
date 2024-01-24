#include <entity/controllers/controllers.h>

INCLUDE_SUB_SUITES(controllers, 5,
INCLUDE_SUITE(test_suite_collidable_entity_handlers.c),

INCLUDE_SUITE(test_suite_controller_dummy.c),

INCLUDE_SUITE(test_suite_entity_handlers.c),

INCLUDE_SUITE(test_suite_controller_player.c),
END_SUITES);

DEFINE_SUITE_WITH__SUB_SUITES(controllers, END_TESTS);

