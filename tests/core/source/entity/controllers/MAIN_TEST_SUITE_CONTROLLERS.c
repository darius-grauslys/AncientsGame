#include <entity/controllers/MAIN_TEST_SUITE_CONTROLLERS.h>

INCLUDE_SUB_SUITES(CONTROLLERS, 5,
INCLUDE_SUITE(collidable_entity_handlers),
INCLUDE_SUITE(controller_dummy),
INCLUDE_SUITE(entity_handlers),
INCLUDE_SUITE(controller_player),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(CONTROLLERS, END_TESTS);

