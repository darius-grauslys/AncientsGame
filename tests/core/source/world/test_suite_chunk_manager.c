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

TEST_FUNCTION(get_most_north_western__chunk_map_node) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    Chunk_Manager__Chunk_Map_Node *actual_node =
        get_most_north_western__chunk_map_node(&chunk_manager);
    Chunk_Manager__Chunk_Map_Node *expected_node =
        &chunk_manager.chunk_map[
        get_chunk_index_during__initialization(-4, 3)];

    munit_assert_ptr_equal(
            actual_node,
            expected_node);

    return MUNIT_OK;
}

TEST_FUNCTION(get_most_north_eastern__chunk_map_node) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    Chunk_Manager__Chunk_Map_Node *actual_node =
        get_most_north_eastern__chunk_map_node(&chunk_manager);
    Chunk_Manager__Chunk_Map_Node *expected_node =
        &chunk_manager.chunk_map[
        get_chunk_index_during__initialization(3, 3)];

    munit_assert_ptr_equal(
            actual_node,
            expected_node);

    return MUNIT_OK;
}

TEST_FUNCTION(get_most_south_western__chunk_map_node) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    Chunk_Manager__Chunk_Map_Node *actual_node =
        get_most_south_western__chunk_map_node(&chunk_manager);
    Chunk_Manager__Chunk_Map_Node *expected_node =
        &chunk_manager.chunk_map[
        get_chunk_index_during__initialization(-4, -4)];

    munit_assert_ptr_equal(
            actual_node,
            expected_node);

    return MUNIT_OK;
}

TEST_FUNCTION(get_most_south_eastern__chunk_map_node) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    Chunk_Manager__Chunk_Map_Node *actual_node =
        get_most_south_eastern__chunk_map_node(&chunk_manager);
    Chunk_Manager__Chunk_Map_Node *expected_node =
        &chunk_manager.chunk_map[
        get_chunk_index_during__initialization(3, -4)];

    munit_assert_ptr_equal(
            actual_node,
            expected_node);

    return MUNIT_OK;
}

static void inline assert_chunk_positions_with__offset(
        Chunk_Manager *chunk_manager,
        int32_t x__center_chunk,
        int32_t y__center_chunk,
        int32_t x__center_chunk_offset,
        int32_t y__center_chunk_offset) {

    // check extremum NW
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk__here->x,
            ==,
            chunk_manager->x__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2
            );
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk__here->y,
            ==,
            chunk_manager->y__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2 - 1
            );

    // check extremum NE
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk_map_node__west
            ->chunk__here->x,
            ==,
            chunk_manager->x__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2 - 1
            );
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk_map_node__west
            ->chunk__here->y,
            ==,
            chunk_manager->y__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2 - 1
            );

    // check extremum SW
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk_map_node__north
            ->chunk__here->x,
            ==,
            chunk_manager->x__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2
            );
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk_map_node__north
            ->chunk__here->y,
            ==,
            chunk_manager->y__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2
            );

    // check extremum SE
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk_map_node__north
            ->chunk_map_node__west
            ->chunk__here->x,
            ==,
            chunk_manager->x__center_chunk
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2 - 1
            );
    munit_assert_int32(
            chunk_manager->chunk_map_node__most_north_western
            ->chunk_map_node__north
            ->chunk_map_node__west
            ->chunk__here->y,
            ==,
            chunk_manager->y__center_chunk
            - CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2
            );

    Chunk *current__chunk;
    Chunk_Manager__Chunk_Map_Node *origin__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node;
    origin__chunk_map_node =
        get_most_south_western__chunk_map_node(chunk_manager);
    current__chunk_map_node =
        origin__chunk_map_node;
    for (int32_t y=-CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2;
            y++) {
        for (int32_t x=-CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x++) {
            current__chunk =
                current__chunk_map_node->chunk__here;

            munit_assert_int32(
                    current__chunk_map_node->chunk__here->x,
                    ==,
                    x__center_chunk + x);
            munit_assert_int32(
                    current__chunk_map_node->chunk__here->y,
                    ==,
                    y__center_chunk + y);

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
            current__chunk_map_node =
                current__chunk_map_node
                ->chunk_map_node__east;
        }
        origin__chunk_map_node =
            origin__chunk_map_node->chunk_map_node__north;
        current__chunk_map_node =
            origin__chunk_map_node;
    }
}

static void inline assert_chunk_positions(
        Chunk_Manager *chunk_manager,
        int32_t x__center_chunk,
        int32_t y__center_chunk){
    assert_chunk_positions_with__offset(
            chunk_manager, 
            x__center_chunk, 
            y__center_chunk, 
            0, 0);
}

TEST_FUNCTION(init_chunk_manager) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    assert_chunk_positions_with__offset(&chunk_manager,
            0, 0,
            4, 4);
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

    Chunk_Manager__Chunk_Map_Node 
        *current__chunk_map_node=
        chunk_manager.chunk_map[0]
        .chunk_map_node__west;

    for (uint32_t expected_index=0;
            expected_index <
            CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
            * CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            expected_index++) {
        if (expected_index % 8 == 0 && expected_index != 0) {
            current__chunk_map_node =
                current__chunk_map_node
                ->chunk_map_node__east
                ->chunk_map_node__south;
        } else {
            current__chunk_map_node =
                current__chunk_map_node
                ->chunk_map_node__east;
        }
        munit_assert_int32(
                get_chunk_index_at__xyz_from__chunk_manager(
                    &chunk_manager,
                    current__chunk_map_node->chunk__here->x,
                    current__chunk_map_node->chunk__here->y,
                    0),
                ==,
                expected_index);
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

    Chunk_Manager__Chunk_Map_Node *extremum__chunk_map_node;
    Chunk *testing_extremum__chunk;

    extremum__chunk_map_node =
        get_most_north_western__chunk_map_node(&chunk_manager);
    testing_extremum__chunk =
        get_chunk_from__chunk_manager(
                &chunk_manager,
                extremum__chunk_map_node
                ->chunk__here->x,
                extremum__chunk_map_node
                ->chunk__here->y,
                0);
    munit_assert_ptr_equal(
            extremum__chunk_map_node->chunk__here,
            testing_extremum__chunk);

    extremum__chunk_map_node =
        get_most_north_eastern__chunk_map_node(&chunk_manager);
    testing_extremum__chunk =
        get_chunk_from__chunk_manager(
                &chunk_manager,
                extremum__chunk_map_node
                ->chunk__here->x,
                extremum__chunk_map_node
                ->chunk__here->y,
                0);
    munit_assert_ptr_equal(
            extremum__chunk_map_node->chunk__here,
            testing_extremum__chunk);

    extremum__chunk_map_node =
        get_most_south_western__chunk_map_node(&chunk_manager);
    testing_extremum__chunk =
        get_chunk_from__chunk_manager(
                &chunk_manager,
                extremum__chunk_map_node
                ->chunk__here->x,
                extremum__chunk_map_node
                ->chunk__here->y,
                0);
    munit_assert_ptr_equal(
            extremum__chunk_map_node->chunk__here,
            testing_extremum__chunk);

    extremum__chunk_map_node =
        get_most_south_eastern__chunk_map_node(&chunk_manager);
    testing_extremum__chunk =
        get_chunk_from__chunk_manager(
                &chunk_manager,
                extremum__chunk_map_node
                ->chunk__here->x,
                extremum__chunk_map_node
                ->chunk__here->y,
                0);
    munit_assert_ptr_equal(
            extremum__chunk_map_node->chunk__here,
            testing_extremum__chunk);


    for (int32_t y=-CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2;
            y++) {
        for (int32_t x=-CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x++) {
            Chunk *chunk_test =
                get_chunk_from__chunk_manager(
                        &chunk_manager,
                        x, y, 0);

            munit_assert_int32(
                    chunk_test->x,
                    ==,
                    x);
            munit_assert_int32(
                    chunk_test->y,
                    ==,
                    y);
        }
    }
    return MUNIT_OK;
}

static void inline assert_moved_chunk__row_or_column(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        Direction direction) {
    init_world_parameters(world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            chunk_manager, world_params);

    int32_t old_x__center_chunk, old_y__center_chunk;
    int32_t x__center_chunk_offset, y__center_chunk_offset;
    old_x__center_chunk = 
        chunk_manager->x__center_chunk;
    old_y__center_chunk = 
        chunk_manager->y__center_chunk;
    int32_t old_x__start, old_y__start,
            old_x__end, old_y__end;

    move_chunk_manager(
            chunk_manager,
            world_params,
            direction,
            1);
    
    if (direction & DIRECTION__EAST) {
        x__center_chunk_offset = 1;
    } else if (direction & DIRECTION__WEST) {
        x__center_chunk_offset = -1;
    } else {
        x__center_chunk_offset = 0;
    }
    if (direction & DIRECTION__NORTH) {
        y__center_chunk_offset = 1;
    } else if (direction & DIRECTION__SOUTH) {
        y__center_chunk_offset = -1;
    } else {
        y__center_chunk_offset = 0;
    }
    assert_chunk_positions_with__offset(
            chunk_manager,
            old_x__center_chunk
            + x__center_chunk_offset,
            old_y__center_chunk
            + y__center_chunk_offset,
            x__center_chunk_offset,
            y__center_chunk_offset
            );
            

    return MUNIT_OK;
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node;
    switch (direction) {
        default:
            munit_assert_false(true); // Bad invocation!
            break;
        case DIRECTION__NORTH:
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

TEST_FUNCTION(set_chunk_manager_at__position) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;

    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    int32_t x__chunk_start, y__chunk_start;
    x__chunk_start =
        munit_rand_int_range(-128, 128);
    y__chunk_start =
        munit_rand_int_range(-128, 128);

    set_chunk_manager_at__position(
            &chunk_manager,
            &world_params,
            x__chunk_start, y__chunk_start);

    Chunk_Manager__Chunk_Map_Node *chunk_map_node__most_north_western =
        get_most_north_western__chunk_map_node(&chunk_manager);

    munit_assert_int32(
            chunk_map_node__most_north_western->chunk__here->x,
            ==,
            x__chunk_start
            - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2);
    munit_assert_int32(
            chunk_map_node__most_north_western->chunk__here->y,
            ==,
            y__chunk_start
            + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2 - 1);

    assert_chunk_positions(&chunk_manager,
            x__chunk_start, y__chunk_start);

    return MUNIT_OK;
}

TEST_FUNCTION(get_chunk_from__chunk_manager__after_setting_position) {
    Chunk_Manager chunk_manager;
    World_Parameters world_params;
    init_world_parameters(&world_params,
            chunk_generator__test_f,
            0);
    init_chunk_manager(
            &chunk_manager, &world_params);

    int32_t x__chunk_start, y__chunk_start;
    x__chunk_start =
        munit_rand_int_range(-128, 128);
    y__chunk_start =
        munit_rand_int_range(-128, 128);

    set_chunk_manager_at__position(
            &chunk_manager,
            &world_params,
            x__chunk_start,
            y__chunk_start);

    for (int32_t y=-CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2;
            y++) {
        for (int32_t x=-CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x++) {
            Chunk *chunk_test =
                get_chunk_from__chunk_manager(
                        &chunk_manager,
                        x + x__chunk_start, 
                        y + y__chunk_start, 
                        0);
            munit_assert_int32(
                    chunk_test->x,
                    ==,
                    x + x__chunk_start);
            munit_assert_int32(
                    chunk_test->y,
                    ==,
                    y + y__chunk_start);
        }
    }
    return MUNIT_OK;
}

DEFINE_SUITE(chunk_manager, 
        INCLUDE_TEST__STATELESS
            (get_chunk_index_during__initialization), 
        INCLUDE_TEST__STATELESS
            (get_most_north_western__chunk_map_node),
        INCLUDE_TEST__STATELESS
            (get_most_north_eastern__chunk_map_node),
        INCLUDE_TEST__STATELESS
            (get_most_south_western__chunk_map_node),
        INCLUDE_TEST__STATELESS
            (get_most_south_eastern__chunk_map_node),
        INCLUDE_TEST__STATELESS
            (get_chunk_index_at__xyz_from__chunk_manager),
        INCLUDE_TEST__STATELESS
            (init_chunk_manager),
        INCLUDE_TEST__STATELESS
            (get_chunk_from__chunk_manager),
        INCLUDE_TEST__STATELESS
            (move_chunk_manager),
        INCLUDE_TEST__STATELESS
            (set_chunk_manager_at__position),
        INCLUDE_TEST__STATELESS
            (get_chunk_from__chunk_manager__after_setting_position),
        END_TESTS)
