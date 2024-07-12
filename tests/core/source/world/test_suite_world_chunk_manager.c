#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "raycast/ray.h"
#include "test_util.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include <world/test_suite_world_chunk_manager.h>
#include <world/generators/generator_test_world.h>
#include <world/world_parameters.h>

#include <world/chunk_manager.c>

TEST_FUNCTION(initialize_chunk_manager) {
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
                &chunk_manager.chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            munit_assert_ptr(
                    p_chunk_map_node
                        ->p_north__chunk_map_node,
                    !=,
                    0);
            munit_assert_ptr(
                    p_chunk_map_node
                        ->p_south__chunk_map_node,
                    !=,
                    0);
            munit_assert_ptr(
                    p_chunk_map_node
                        ->p_east__chunk_map_node,
                    !=,
                    0);
            munit_assert_ptr(
                    p_chunk_map_node
                        ->p_west__chunk_map_node,
                    !=,
                    0);
        }
    }

    return MUNIT_OK;
}

TEST_FUNCTION(initialize_chunk_manager__local_connections) {
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
                &chunk_manager.chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_north__chunk_map_node
                        ->p_south__chunk_map_node);
            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_east__chunk_map_node
                        ->p_west__chunk_map_node);
            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_south__chunk_map_node
                        ->p_north__chunk_map_node);
            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_west__chunk_map_node
                        ->p_east__chunk_map_node);

            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_east__chunk_map_node
                        ->p_north__chunk_map_node
                        ->p_west__chunk_map_node
                        ->p_south__chunk_map_node);
            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_west__chunk_map_node
                        ->p_north__chunk_map_node
                        ->p_east__chunk_map_node
                        ->p_south__chunk_map_node);
            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_east__chunk_map_node
                        ->p_south__chunk_map_node
                        ->p_west__chunk_map_node
                        ->p_north__chunk_map_node);
            munit_assert_ptr(
                    p_chunk_map_node,
                    ==,
                    p_chunk_map_node
                        ->p_west__chunk_map_node
                        ->p_south__chunk_map_node
                        ->p_east__chunk_map_node
                        ->p_north__chunk_map_node);
        }
    }

    return MUNIT_OK;
}

TEST_FUNCTION(initialize_chunk_manager__full_range) {
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    Chunk_Manager__Chunk_Map_Node *p_chunk_map_node__origin =
            chunk_manager.chunk_map;

    for (Signed_Index__i32 y=0; y <=
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
            p_chunk_map_node__origin;

        for (Signed_Index__i32 y__sub=0; y__sub<y; y__sub++) {
            p_chunk_map_node =
                p_chunk_map_node->p_north__chunk_map_node;
        }

        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {

            p_chunk_map_node =
                p_chunk_map_node->p_east__chunk_map_node;
        }

        for (Signed_Index__i32 y__sub=0; y__sub<y; y__sub++) {
            p_chunk_map_node =
                p_chunk_map_node->p_south__chunk_map_node;
        }

        munit_assert_ptr(
                p_chunk_map_node,
                ==,
                p_chunk_map_node__origin);
    }

    return MUNIT_OK;
}

TEST_FUNCTION(get_chunk_index_from__chunk_manager) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Vector__3i32 vector__3i32 =
                get_vector__3i32(x,-y,0);

            Chunk *p_chunk =
                &chunk_manager.chunks[
                    (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - y - 1) 
                        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Index__u32 index =
                get_chunk_index_from__chunk_manager(
                        &chunk_manager,
                        vector__3i32);

            munit_assert_int(
                    p_chunk
                    - chunk_manager.chunks,
                    ==,
                    index);
        }
    }

    return MUNIT_OK;
}

TEST_FUNCTION(get_p_chunk_from__chunk_manager_using__i32) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Vector__3i32 vector__3i32 =
                get_vector__3i32(x,y,0);

            Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
                &chunk_manager.chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Chunk *p_chunk =
                get_p_chunk_from__chunk_manager_using__i32(
                        &chunk_manager,
                        vector__3i32.x__i32,
                        vector__3i32.y__i32,
                        0);

            munit_assert_ptr(
                    p_chunk_map_node->p_chunk__here,
                    ==,
                    p_chunk);
        }
    }

    return MUNIT_SKIP;
}

TEST_FUNCTION(move_chunk_manager) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    return MUNIT_SKIP;
}

TEST_FUNCTION(poll_chunk_manager_for__chunk_movement) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    return MUNIT_SKIP;
}

TEST_FUNCTION(poll_chunk_manager_for__tile_collision) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    return MUNIT_SKIP;
}

MunitResult assert_p_tile_is_in__p_chunk(
        Tile *p_tile,
        Chunk *p_chunk) {
    for (Index__u16 index_of__tile = 0;
            index_of__tile
            < (sizeof(p_chunk->tiles) / sizeof(Tile));
            index_of__tile++) {
        if (p_tile == &p_chunk->tiles[index_of__tile])
            return MUNIT_OK;
    }
    return MUNIT_FAIL;
}

TEST_FUNCTION(get_p_tile_from__chunk_node) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Vector__3u8 vector__3u8 =
                get_vector__3u8(x,y,0);

            Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
                &chunk_manager.chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Tile *p_tile =
                get_p_tile_from__chunk_node(
                        p_chunk_map_node, 
                        vector__3u8
                        );

            munit_assert(
                    assert_p_tile_is_in__p_chunk(
                        p_tile, 
                        p_chunk_map_node->p_chunk__here)
                    == MUNIT_OK);

            munit_assert_ptr(
                    p_tile,
                    ==,
                    &p_chunk_map_node->p_chunk__here->tiles[
                        y * CHUNK_WIDTH__IN_TILES
                        + x]);
        }
    }

    return MUNIT_OK;
}

TEST_FUNCTION(get_p_tile_from__chunk_node_using__u8) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Vector__3u8 vector__3u8 =
                get_vector__3u8(x,y,0);

            Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
                &chunk_manager.chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Tile *p_tile =
                get_p_tile_from__chunk_node(
                        p_chunk_map_node, 
                        vector__3u8
                        );
            Tile *p_tile_using__u8 =
                get_p_tile_from__chunk_node_using__u8(
                        p_chunk_map_node, 
                        x, y
                        );

            munit_assert(
                    assert_p_tile_is_in__p_chunk(
                        p_tile_using__u8, 
                        p_chunk_map_node->p_chunk__here)
                    == MUNIT_OK);

            munit_assert_ptr(
                    p_tile,
                    ==,
                    p_tile_using__u8);
        }
    }

    return MUNIT_OK;
}

TEST_FUNCTION(get_p_tile_from__chunk_manager) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    // for (Signed_Index__i32 y=0; y < 
    //         CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
    //     for (Signed_Index__i32 x=0; x <
    //             CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
    //         Vector__3i32F4 vector__3i32F4 =
    //             get_vector__3i32F4_using__i32(x,y,0);

    //         Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
    //             &chunk_manager.chunk_map[
    //                 y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
    //                     + x
    //             ];

    //         Tile *p_tile =
    //             get_p_tile_from__chunk_manager(
    //                     &chunk_manager,
    //                     vector__3i32F4);

    //         munit_assert(
    //                 assert_p_tile_is_in__p_chunk(
    //                     p_tile, 
    //                     p_chunk_map_node->p_chunk__here)
    //                 == MUNIT_OK);

    //         munit_assert_ptr(
    //                 p_tile,
    //                 ==,
    //                 &p_chunk_map_node->p_chunk__here->tiles[
    //                     y * CHUNK_WIDTH__IN_TILES
    //                     + x]);
    //     }
    // }

    return MUNIT_SKIP;
}

TEST_FUNCTION(get_p_tile_from__world_using__ray_3i32F20) {
    return MUNIT_SKIP;
    Chunk_Manager chunk_manager;
    World_Parameters world_parameters;
    initialize_world_parameters(
            &world_parameters, 
            f_chunk_generator__test_world, 
            100);
    initialize_chunk_manager(
            &chunk_manager,
            &world_parameters);

    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Vector__3i32F4 vector__3i32F4 =
                get_vector__3i32F4_using__i32(x,y,0);
            Ray__3i32F20 ray__3i32F20 =
                get_ray(
                        vector__3i32F4,
                        ANGLE__0);

            Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
                &chunk_manager.chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Tile *p_tile_using__ray =
                get_p_tile_from__chunk_manager_with__ray_3i32F20(
                        &chunk_manager,
                        &ray__3i32F20);

            munit_assert(
                    assert_p_tile_is_in__p_chunk(
                        p_tile_using__ray, 
                        p_chunk_map_node->p_chunk__here)
                    == MUNIT_OK);

            munit_assert_ptr(
                    p_tile_using__ray,
                    ==,
                    &p_chunk_map_node->p_chunk__here->tiles[
                        y * CHUNK_WIDTH__IN_TILES
                        + x]);
        }
    }

    return MUNIT_OK;
}

DEFINE_SUITE(chunk_manager, 
        INCLUDE_TEST__STATELESS
            (initialize_chunk_manager),
        INCLUDE_TEST__STATELESS
            (initialize_chunk_manager__local_connections),
        INCLUDE_TEST__STATELESS
            (initialize_chunk_manager__full_range),
        INCLUDE_TEST__STATELESS
            (get_chunk_index_from__chunk_manager),
        INCLUDE_TEST__STATELESS
            (get_p_chunk_from__chunk_manager_using__i32),
        INCLUDE_TEST__STATELESS
            (get_p_tile_from__chunk_node),
        INCLUDE_TEST__STATELESS
            (get_p_tile_from__chunk_node_using__u8),
        INCLUDE_TEST__STATELESS
            (get_p_tile_from__chunk_manager),
        INCLUDE_TEST__STATELESS
            (get_p_tile_from__world_using__ray_3i32F20),
        INCLUDE_TEST__STATELESS
            (get_chunk_index_from__chunk_manager),
        END_TESTS)
