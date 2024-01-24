#include <entity/entity.h>

INCLUDE_SUB_SUITES(entity, 4,
INCLUDE_SUITE(test_suite_entity_manager.c),

INCLUDE_SUITE(controllers),
END_SUITES);

DEFINE_SUITE_WITH__SUB_SUITES(entity, END_TESTS);

