#include <inventory/MAIN_TEST_SUITE_INVENTORY.h>

INCLUDE_SUB_SUITES(INVENTORY, 8,
INCLUDE_SUITE(item_stack_manager),
INCLUDE_SUITE(inventory_manager),
INCLUDE_SUITE(item_stack_allocation_specifier),
INCLUDE_SUITE(item_stack),
INCLUDE_SUITE(inventory),
INCLUDE_SUITE(item),
INCLUDE_SUITE(equipment),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(INVENTORY, END_TESTS);

