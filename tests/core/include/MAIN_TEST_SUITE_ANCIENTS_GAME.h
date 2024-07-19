#include "test_suite_main.h"
#include "test_suite_vectors.h"
#include "test_suite_random.h"
#include "test_suite_degree.h"
#include "test_suite_game.h"
#include "input/MAIN_TEST_SUITE_INPUT.h"
#include "rendering/MAIN_TEST_SUITE_RENDERING.h"
#include "world/MAIN_TEST_SUITE_WORLD.h"
#include "inventory/MAIN_TEST_SUITE_INVENTORY.h"
#include "sort/MAIN_TEST_SUITE_SORT.h"
#include "debug/MAIN_TEST_SUITE_DEBUG.h"
#include "serialization/MAIN_TEST_SUITE_SERIALIZATION.h"
#include "game_action/MAIN_TEST_SUITE_GAME_ACTION.h"
#include "entity/MAIN_TEST_SUITE_ENTITY.h"
#include "ui/MAIN_TEST_SUITE_UI.h"
#include "collisions/MAIN_TEST_SUITE_COLLISIONS.h"
#include "multiplayer/MAIN_TEST_SUITE_MULTIPLAYER.h"
#include "raycast/MAIN_TEST_SUITE_RAYCAST.h"
#include "process/MAIN_TEST_SUITE_PROCESS.h"
#include "scene/MAIN_TEST_SUITE_SCENE.h"

#include <test_util.h>

DECLARE_SUITE(ANCIENTS_GAME);

