#include <MAIN_TEST_SUITE_ANCIENTS_GAME.h>

INCLUDE_SUB_SUITES(ANCIENTS_GAME, 21,
INCLUDE_SUITE(main),
INCLUDE_SUITE(vectors),
INCLUDE_SUITE(random),
INCLUDE_SUITE(degree),
INCLUDE_SUITE(game),
INCLUDE_SUITE(INPUT),
INCLUDE_SUITE(RENDERING),
INCLUDE_SUITE(WORLD),
INCLUDE_SUITE(INVENTORY),
INCLUDE_SUITE(SORT),
INCLUDE_SUITE(DEBUG),
INCLUDE_SUITE(SERIALIZATION),
INCLUDE_SUITE(GAME_ACTION),
INCLUDE_SUITE(ENTITY),
INCLUDE_SUITE(UI),
INCLUDE_SUITE(COLLISIONS),
INCLUDE_SUITE(MULTIPLAYER),
INCLUDE_SUITE(RAYCAST),
INCLUDE_SUITE(PROCESS),
INCLUDE_SUITE(SCENE),NULL);

DEFINE_SUITE_WITH__SUB_SUITES(ANCIENTS_GAME, END_TESTS);

