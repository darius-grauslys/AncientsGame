#include <entity/handlers/body/MAIN_TEST_SUITE_ENTITY_HANDLERS_BODY.h>

INCLUDE_SUB_SUITES(ENTITY_HANDLERS_BODY, 3,
INCLUDE_SUITE(body_handler__living),
INCLUDE_SUITE(body_handler__undead),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(ENTITY_HANDLERS_BODY, END_TESTS);

