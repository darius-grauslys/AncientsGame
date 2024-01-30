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
    return MUNIT_OK;
}

DEFINE_SUITE(chunk_manager, 
        INCLUDE_TEST__STATELESS
            (get_chunk_index_during__initialization), 
        INCLUDE_TEST__STATELESS
            (get_chunk_index_at__xyz_from__chunk_manager),
        INCLUDE_TEST__STATELESS
            (get_chunk_from__chunk_manager),
        END_TESTS)
