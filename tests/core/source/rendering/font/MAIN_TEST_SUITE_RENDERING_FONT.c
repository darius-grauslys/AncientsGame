#include <rendering/font/MAIN_TEST_SUITE_RENDERING_FONT.h>

INCLUDE_SUB_SUITES(RENDERING_FONT, 4,
INCLUDE_SUITE(font),
INCLUDE_SUITE(typer),
INCLUDE_SUITE(message),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(RENDERING_FONT, END_TESTS);

