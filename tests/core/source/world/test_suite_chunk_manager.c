#include <world/test_suite_chunk_manager.h>

#include <world/world_parameters.h>
#include <world/chunk_manager.c>

TEST_FUNCTION(get_chunk_index_during__initialization) {
    uint32_t index = 
        CHUNK_MANAGER__QUANTITY_OF_CHUNKS - 1;
    uint32_t returned_index;
    for (int32_t y=0;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            y++) {
        for (int32_t x=CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW-1;
                x>=0;
                x--) {
            returned_index =
                get_chunk_index_during__initialization(x,y);
            munit_assert_uint32(returned_index, ==, index--);
        }
    }

    returned_index =
        get_chunk_index_during__initialization(-1,7);
    munit_assert_int32(
            returned_index,
            ==,
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1);
    returned_index =
        get_chunk_index_during__initialization(0,-1);
    munit_assert_int32(
            returned_index,
            ==,
            0);

    return MUNIT_OK;
}


void chunk_generator__test_f(
        World_Parameters *world_params,
        Chunk *chunk) {
    for (uint32_t i=0;
            i<CHUNK_QUANTITY_OF__TILES;
            i++) {
        init_tile(&chunk->tiles[i],
                Tile_Kind__Oak_Wood, TILE_FLAGS__NONE);
    }
    return;
}

TEST_FUNCTION(init_chunk_manager) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    munit_assert_ptr_equal(
            chunk_manager.chunk_map_node__most_north_western,
            &chunk_manager.chunk_map[0]
            );

    Chunk *current__chunk;
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node;
    for (int32_t y=0;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            y++) {
        for (int32_t x=0;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                x++) {
            current__chunk =
                &chunk_manager.chunks[
                get_chunk_index_during__initialization(x, y)
                ];
            current__chunk_map_node =
                &chunk_manager.chunk_map[
                get_chunk_index_during__initialization(x, y)
                ];

            munit_assert_ptr_equal(
                    current__chunk,
                    current__chunk_map_node->chunk__here
                    );

            munit_assert_ptr_not_equal(
                    current__chunk_map_node->chunk_map_node__north,
                    0
                    );
            munit_assert_ptr_not_equal(
                    current__chunk_map_node->chunk_map_node__east,
                    0
                    );
            munit_assert_ptr_not_equal(
                    current__chunk_map_node->chunk_map_node__south,
                    0
                    );
            munit_assert_ptr_not_equal(
                    current__chunk_map_node->chunk_map_node__west,
                    0
                    );
        }
    }
    return MUNIT_OK;
}

TEST_FUNCTION(get_chunk_index_at__xyz_from__chunk_manager) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    for (int32_t y=0;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            y++) {
        for (int32_t x=0;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                x++) {
            uint32_t index =
                get_chunk_index_at__xyz_from__chunk_manager(
                        &chunk_manager,
                        x, y, 0);
            munit_assert_uint32(
                    index,
                    ==,
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                    + x
                    );
        }
    }
    return MUNIT_OK;
}

TEST_FUNCTION(get_chunk_from__chunk_manager) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    for (int32_t y=0;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            y++) {
        for (int32_t x=0;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                x++) {
            Chunk *chunk_test =
                get_chunk_from__chunk_manager(
                        &chunk_manager,
                        x, y, 0);
            Chunk *chunk_actual =
                &chunk_manager.chunks[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x
                ];
            munit_assert_ptr_equal(
                    chunk_test,
                    chunk_actual);
        }
    }
    return MUNIT_OK;
}

static void inline assert_moved_chunk__row_or_column(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        Direction direction) {
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    int32_t old_x__start, old_y__start,
            old_x__end, old_y__end;

    move_chunk_manager(
            &chunk_manager,
            &world_params,
            direction,
            1);

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node;
    switch (direction) {
        default:
            munit_assert_false(true); // Bad invocation!
            break;
        case DIRECTION__NORTH:
            printf("seg flt %p\n", 
                    get_most_north_western__chunk_map_node(chunk_manager));
            printf("seg flt %p\n", 
                    get_most_north_western__chunk(chunk_manager)); 
            printf("seg flt\n");
            old_x__start = 
                get_most_north_western__chunk(chunk_manager)->x;
            old_y__start = 
                get_most_north_western__chunk(chunk_manager)->y;
            old_x__end = 
                get_most_north_eastern__chunk(chunk_manager)->x;
            old_y__end = 
                get_most_north_eastern__chunk(chunk_manager)->y;
            current__chunk_map_node = 
                get_most_north_western__chunk_map_node(chunk_manager);
            for (uint32_t index = 0;
                    index<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                    index++) {
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->x,
                        ==,
                        old_x__start + index
                        );
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->y,
                        ==,
                        old_y__start + 1
                        );
                current__chunk_map_node =
                    current__chunk_map_node
                    ->chunk_map_node__east;
            }
            break;
        case DIRECTION__EAST:
            old_x__start = 
                get_most_north_eastern__chunk(chunk_manager)->x;
            old_y__start = 
                get_most_north_eastern__chunk(chunk_manager)->y;
            old_x__end = 
                get_most_south_eastern__chunk(chunk_manager)->x;
            old_y__end = 
                get_most_south_eastern__chunk(chunk_manager)->y;
            current__chunk_map_node = 
                get_most_north_western__chunk_map_node(chunk_manager);
            for (uint32_t index = 0;
                    index<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                    index++) {
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->x,
                        ==,
                        old_x__start + 1
                        );
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->y,
                        ==,
                        old_y__start - index
                        );
                current__chunk_map_node =
                    current__chunk_map_node
                    ->chunk_map_node__south;
            }
            break;
        case DIRECTION__SOUTH:
            old_x__start = 
                get_most_south_western__chunk(chunk_manager)->x;
            old_y__start = 
                get_most_south_western__chunk(chunk_manager)->y;
            old_x__end = 
                get_most_south_eastern__chunk(chunk_manager)->x;
            old_y__end = 
                get_most_south_eastern__chunk(chunk_manager)->y;
            current__chunk_map_node = 
                get_most_north_western__chunk_map_node(chunk_manager);
            for (uint32_t index = 0;
                    index<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                    index++) {
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->x,
                        ==,
                        old_x__start + index
                        );
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->y,
                        ==,
                        old_y__start - 1 
                        );
                current__chunk_map_node =
                    current__chunk_map_node
                    ->chunk_map_node__east;
            }
            break;
        case DIRECTION__WEST:
            old_x__start = 
                get_most_north_western__chunk(chunk_manager)->x;
            old_y__start = 
                get_most_north_western__chunk(chunk_manager)->y;
            old_x__end = 
                get_most_south_western__chunk(chunk_manager)->x;
            old_y__end = 
                get_most_south_western__chunk(chunk_manager)->y;
            current__chunk_map_node = 
                get_most_north_western__chunk_map_node(chunk_manager);
            for (uint32_t index = 0;
                    index<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
                    index++) {
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->x,
                        ==,
                        old_x__start - 1
                        );
                munit_assert_int32(
                        current__chunk_map_node->chunk__here->y,
                        ==,
                        old_y__start - index
                        );
                current__chunk_map_node =
                    current__chunk_map_node
                    ->chunk_map_node__south;
            }
            break;
    }
}

TEST_FUNCTION(move_chunk_manager) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;

    assert_moved_chunk__row_or_column(
            &chunk_manager, 
            &world_params,
            DIRECTION__NORTH);
    assert_moved_chunk__row_or_column(
            &chunk_manager, 
            &world_params,
			DIRECTION__EAST);
    assert_moved_chunk__row_or_column(
            &chunk_manager, 
            &world_params,
			DIRECTION__SOUTH);
    assert_moved_chunk__row_or_column(
            &chunk_manager, 
            &world_params,
			DIRECTION__WEST);

    return MUNIT_OK;
}

DEFINE_SUITE(chunk_manager, 
        INCLUDE_TEST__STATELESS
            (get_chunk_index_during__initialization), 
        INCLUDE_TEST__STATELESS
            (get_chunk_index_at__xyz_from__chunk_manager),
        INCLUDE_TEST__STATELESS
            (init_chunk_manager),
        INCLUDE_TEST__STATELESS
            (get_chunk_from__chunk_manager),
        INCLUDE_TEST__STATELESS
            (move_chunk_manager),
        END_TESTS)
