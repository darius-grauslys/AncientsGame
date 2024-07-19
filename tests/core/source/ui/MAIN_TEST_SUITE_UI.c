#include <ui/MAIN_TEST_SUITE_UI.h>

INCLUDE_SUB_SUITES(UI, 8,
INCLUDE_SUITE(ui_drop_zone__inventory_slot),
INCLUDE_SUITE(ui_button),
INCLUDE_SUITE(ui_slider),
INCLUDE_SUITE(ui_draggable),
INCLUDE_SUITE(ui_drop_zone),
INCLUDE_SUITE(ui_manager),
INCLUDE_SUITE(ui_element),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(UI, END_TESTS);

