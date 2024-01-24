#include </ancients_game.h>

INCLUDE_SUB_SUITES(ancients_game, 12,
INCLUDE_SUITE(test_suite_game.c),

INCLUDE_SUITE(input),

INCLUDE_SUITE(rendering),

INCLUDE_SUITE(world),

INCLUDE_SUITE(inventory),

INCLUDE_SUITE(debug),

INCLUDE_SUITE(entity),

INCLUDE_SUITE(ui),

INCLUDE_SUITE(collisions),

INCLUDE_SUITE(multiplayer),

INCLUDE_SUITE(scene),
END_SUITES);

DEFINE_SUITE_WITH__SUB_SUITES(ancients_game, END_TESTS);

