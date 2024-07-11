#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "process/process.h"
#include "process/process_manager.h"
#include "sort/sort_list/sort_list_manager.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "world/generators/generator_test_world.h"
#include "world/path_finding/path.h"
#include "world/path_finding/path_list.h"
#include "world/path_finding/path_list_manager.h"
#include "world/path_finding/process/process_path_finding.h"
#include "world/tile.h"
#include "world/world.h"
#include "world/world_parameters.h"
#include <world/path_finding/process/test_suite_world_path_finding_process_process_path_finding.h>

#include <world/path_finding/process/process_path_finding.c>

extern Vector__3i32F8 __DEGREE_TO_2i32F10__LOOKUP_TABLE[256];

TEST_FUNCTION(m_process__path_find__trivial) {
    Game game;

    initialize_game(
            &game, 
            0);

    initialize_world(
            get_p_world_from__game(&game), 
            0);

    move_chunk_manager(
            &game.world.chunk_manager, 
            &game.world.world_parameters, 
            DIRECTION__NORTH_WEST,
            2);

    Vector__3i32 starting_point__3i32 =
            get_vector__3i32(0, -1, 0);
    Vector__3i32 destination__3i32 =
                get_vector__3i32(0, 9, 0);
    i32F4 destination_squared_radius__i32F4 = 0b10010;

    Path_List *p_path_list =
        allocate_and_initialize_path_list_with__managers(
                get_p_path_list_manager_from__game(&game),
                get_p_sort_list_manager_from__game(&game),
                starting_point__3i32,
                destination__3i32,
                destination_squared_radius__i32F4);

    munit_assert_ptr(
            p_path_list,
            !=,
            0);

    Process_Manager *p_process_manager =
        get_p_process_manager_from__game(&game);
    Quantity__u32 quantity_of__steps_per_cycle = 8;
    Process *p_process =
        allocate_process_in__process_manager(
                p_process_manager);
    initialize_process_for__path_finding(
            p_process, 
            p_path_list, 
            quantity_of__steps_per_cycle);

    register_process_as__critical_in__process_manager(
            p_process_manager,
            &game, 
            p_process);

    Quantity__u32 quantity_of__steps = 0;
    do {
        poll_process_manager(
                p_process_manager,
                &game);
        if (is_process__complete(p_process)) {
            break;
        }
    } while (quantity_of__steps++ < BIT(20));

    munit_assert_uint32(
            quantity_of__steps, 
            <=, 
            BIT(20));

    Path *p_path =
                &p_path_list->paths[0];
    munit_assert_int(
            i32_to__i32F4(
                get_distance_squared_of__vector_3i32(
                    subtract_vectors__3i32(
                        *p_path->p_path_node__newest__3i32,
                        destination__3i32))),
            <=,
            destination_squared_radius__i32F4);



    return MUNIT_OK;
}

TEST_FUNCTION(m_process__path_find__wall_in_between) {
    Game game;

    initialize_game(
            &game, 
            0);

    initialize_world(
            get_p_world_from__game(&game), 
            0);

    move_chunk_manager(
            &game.world.chunk_manager, 
            &game.world.world_parameters, 
            DIRECTION__NORTH_WEST,
            2);

    Tile *p_tile =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__game(&game), 
                get_vector__3i32F4_using__i32(0, 0, 0));

    set_tile__is_unpassable(p_tile, true);

    Vector__3i32 starting_point__3i32 =
            get_vector__3i32(4, -9, 0);
    Vector__3i32 destination__3i32 =
                get_vector__3i32(4, 12, 0);
    i32F4 destination_squared_radius__i32F4 = 0b10010;

    Path_List *p_path_list =
        allocate_and_initialize_path_list_with__managers(
                get_p_path_list_manager_from__game(&game),
                get_p_sort_list_manager_from__game(&game),
                starting_point__3i32,
                destination__3i32,
                destination_squared_radius__i32F4);

    munit_assert_ptr(
            p_path_list,
            !=,
            0);

    Process_Manager *p_process_manager =
        get_p_process_manager_from__game(&game);
    Quantity__u32 quantity_of__steps_per_cycle = 8;
    Process *p_process =
        allocate_process_in__process_manager(
                p_process_manager);
    initialize_process_for__path_finding(
            p_process, 
            p_path_list, 
            quantity_of__steps_per_cycle);

    register_process_as__critical_in__process_manager(
            p_process_manager,
            &game, 
            p_process);

    Quantity__u32 quantity_of__steps = 0;
    do {
        poll_process_manager(
                p_process_manager,
                &game);
        if (is_process__complete(p_process)) {
            break;
        }
    } while (quantity_of__steps++ < BIT(20));

    munit_assert_uint32(
            quantity_of__steps, 
            <=, 
            BIT(20));

    Path *p_path =
                &p_path_list->paths[0];
    munit_assert_int(
            i32_to__i32F4(
                get_distance_squared_of__vector_3i32(
                    subtract_vectors__3i32(
                        *p_path->p_path_node__newest__3i32,
                        destination__3i32))),
            <=,
            destination_squared_radius__i32F4);



    return MUNIT_OK;
}

DEFINE_SUITE(process_path_finding, 
        INCLUDE_TEST__STATELESS
            (m_process__path_find__wall_in_between),
        INCLUDE_TEST__STATELESS
            (m_process__path_find__trivial),
        END_TESTS)
