#include <world/test_suite_world.h>

#include <world/world.c>

#include <world/chunk_manager.h>
#include <world/viewing_fulcrum.h>
#include <collisions/collision_manager.h>

static void inline init_world__randomly__using_points(
        World *world,
        int32_t *x__chunk_start,
        int32_t *y__chunk_start) {
    init_world(world);
    
    *x__chunk_start =
        munit_rand_int_range(-128, 128);
    *y__chunk_start =
        munit_rand_int_range(-128, 128);

    set_hitbox__position(
            &world->viewing_fulcrum.fulcrum,
            *x__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE, 
            *y__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE,
            0);

    set_chunk_manager_at__position(
            &world->chunk_manager, 
            &world->world_params, 
            x__chunk_start, 
            y__chunk_start);

    set_collision_manager_at__position(
            &world->collision_manager,
            x__chunk_start,
            y__chunk_start);
}

static void inline init_world__randomly(
        World *world) {
    int32_t 
        x__chunk_start,
        y__chunk_start;
    init_world__randomly__using_points(
            world,
            &x__chunk_start,
            &y__chunk_start);
}

TEST_FUNCTION(get_entity_manager_from__world) {
    World world;
    init_world(&world);

    munit_assert_ptr_equal(
            get_entity_manager_from__world(&world),
            &world.entity_manager);

    return MUNIT_OK;
}

TEST_FUNCTION(get_chunk_manager_from__world) {
    World world;
    init_world(&world);

    munit_assert_ptr_equal(
            get_chunk_manager_from__world(&world),
            &world.chunk_manager);

    return MUNIT_OK;
}

TEST_FUNCTION(get_collision_manager_from__world) {
    World world;
    init_world(&world);

    munit_assert_ptr_equal(
            get_collision_manager_from__world(&world),
            &world.collision_manager);

    return MUNIT_OK;
}

TEST_FUNCTION(get_world_parameters_from__world) {
    World world;
    init_world(&world);

    munit_assert_ptr_equal(
            get_world_parameters_from__world(&world),
            &world.world_params);

    return MUNIT_OK;
}

TEST_FUNCTION(init_world) {
    //TODO: impl
    return MUNIT_OK;
}

TEST_FUNCTION(MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM__at_origin) {
    World world;
    init_world(&world);

    int32_t x__chunk__min =
        get_aa__x__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);
    int32_t y__chunk__min =
        get_aa__y__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);
    int32_t x__chunk__max =
        get_bb__x__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);
    int32_t y__chunk__max =
        get_bb__y__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);

    int32_t x__range =
        x__chunk__max - x__chunk__min + 1;

    int32_t index = 0;

    FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM(
            (&world),
            0,
            current__chunk_map_node) {
        int32_t x = index % x__range;
        int32_t y = index / x__range;

        munit_assert_ptr_not_equal(
                current__chunk_map_node,
                0);

        Chunk_Manager__Chunk_Map_Node *expected_node =
            get_chunk_map_node_from__chunk_manager(
                    &world.chunk_manager, 
                    x__chunk__min + x, 
                    y__chunk__max - y, 
                    0);

        munit_assert_ptr_equal(
                current__chunk_map_node,
                expected_node);

        index++;
    }

    munit_assert_int32(
            index,
            ==,
            x__range 
            * (y__chunk__max - y__chunk__min + 1));

    return MUNIT_OK;
}

TEST_FUNCTION(MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM) {
    World world;

    int32_t x__chunk_start, y__chunk_start;
    init_world__randomly__using_points(
            &world, 
            &x__chunk_start, 
            &y__chunk_start);

    int32_t x__chunk__min =
        get_aa__x__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);
    int32_t y__chunk__min =
        get_aa__y__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);
    int32_t x__chunk__max =
        get_bb__x__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);
    int32_t y__chunk__max =
        get_bb__y__chunk_from__hitbox(&world.viewing_fulcrum.fulcrum);

    int32_t x__range =
        x__chunk__max - x__chunk__min + 1;

    int32_t index = 0;

    FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM(
            (&world),
            0,
            current__chunk_map_node) {
        int32_t x = index % x__range;
        int32_t y = index / x__range;

        munit_assert_ptr_not_equal(
                current__chunk_map_node,
                0);

        Chunk_Manager__Chunk_Map_Node *expected_node =
            get_chunk_map_node_from__chunk_manager(
                    &world.chunk_manager, 
                    x__chunk__min + x, 
                    y__chunk__max - y, 
                    0);

        munit_assert_ptr_equal(
                current__chunk_map_node,
                expected_node);

        index++;
    }

    munit_assert_int32(
            index,
            ==,
            x__range 
            * (y__chunk__max - y__chunk__min + 1));

    return MUNIT_OK;
}

DEFINE_SUITE(world, 
        INCLUDE_TEST__STATELESS
            (get_entity_manager_from__world),
        INCLUDE_TEST__STATELESS
            (get_chunk_manager_from__world),
        INCLUDE_TEST__STATELESS
            (get_collision_manager_from__world),
        INCLUDE_TEST__STATELESS
            (get_world_parameters_from__world),
        INCLUDE_TEST__STATELESS
            (init_world),
        INCLUDE_TEST__STATELESS
            (MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM),
        INCLUDE_TEST__STATELESS
            (MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM__at_origin),
        END_TESTS)
