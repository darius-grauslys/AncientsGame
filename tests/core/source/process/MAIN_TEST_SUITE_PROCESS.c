#include <process/MAIN_TEST_SUITE_PROCESS.h>

INCLUDE_SUB_SUITES(PROCESS, 3,
INCLUDE_SUITE(process_manager),
INCLUDE_SUITE(process),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(PROCESS, END_TESTS);

