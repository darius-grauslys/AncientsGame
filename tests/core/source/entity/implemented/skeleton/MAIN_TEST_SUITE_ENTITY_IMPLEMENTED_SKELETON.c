#include <entity/implemented/skeleton/MAIN_TEST_SUITE_ENTITY_IMPLEMENTED_SKELETON.h>

INCLUDE_SUB_SUITES(ENTITY_IMPLEMENTED_SKELETON, 3,
INCLUDE_SUITE(entity__skeleton),
INCLUDE_SUITE(ENTITY_IMPLEMENTED_SKELETON_AI),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(ENTITY_IMPLEMENTED_SKELETON, END_TESTS);
