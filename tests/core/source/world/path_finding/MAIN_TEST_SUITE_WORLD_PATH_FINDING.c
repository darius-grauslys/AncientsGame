#include <world/path_finding/MAIN_TEST_SUITE_WORLD_PATH_FINDING.h>

INCLUDE_SUB_SUITES(WORLD_PATH_FINDING, 5,
INCLUDE_SUITE(path_list_manager),
INCLUDE_SUITE(path_list),
INCLUDE_SUITE(path),
INCLUDE_SUITE(WORLD_PATH_FINDING_PROCESS),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(WORLD_PATH_FINDING, END_TESTS);
