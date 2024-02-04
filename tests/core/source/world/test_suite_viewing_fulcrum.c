#include <world/test_suite_viewing_fulcrum.h>

#include <world/viewing_fulcrum.c>

#include <entity/entity.h>

static void inline init_viewing_fulcrum_test__randomly__using_points(
        Viewing_Fulcrum *viewing_fulcrum,
        int32_t *x__chunk_start,
        int32_t *y__chunk_start) {
    init_viewing_fulcrum(viewing_fulcrum);
    
    *x__chunk_start =
        munit_rand_int_range(-128, 128);
    *y__chunk_start =
        munit_rand_int_range(-128, 128);

    set_hitbox__position(
            &viewing_fulcrum->fulcrum,
            *x__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE, 
            *y__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE,
            0);
}

static void inline init_viewing_fulcrum_test__randomly(
        Viewing_Fulcrum *viewing_fulcrum) {
    int32_t 
        x__chunk_start,
        y__chunk_start;
    init_viewing_fulcrum_test__randomly__using_points(
            viewing_fulcrum,
            &x__chunk_start,
            &y__chunk_start);
}

TEST_FUNCTION(is_chunk_position_within__viewing_fulcrum) {
    Viewing_Fulcrum viewing_fulcrum;
    init_viewing_fulcrum(&viewing_fulcrum);
    // testing on default 256x196
    // that means chunks in 4x4 about 0,0

    int32_t x__chunk_start, y__chunk_start;
    x__chunk_start =
        munit_rand_int_range(-128, 128);
    y__chunk_start =
        munit_rand_int_range(-128, 128);

    set_hitbox__position(
            &viewing_fulcrum.fulcrum,
            x__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE, 
            y__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE,
            0);

    // I am going to magic number the test since core doesn't
    // really care for these constants to be labeled. The meaning
    // of these constants is explained above (comment after
    // the init)
    for (int32_t y=-4;y<5;y++) {
        for (int32_t x=-4;x<5;x++) {
            if (x*x <= 4 && y*y <= 4) {
                munit_assert_true(
                        is_chunk_position_within__viewing_fulcrum(
                            &viewing_fulcrum,
                            x__chunk_start + x, 
                            y__chunk_start + y)
                        );
            } else {
                munit_assert_false(
                        is_chunk_position_within__viewing_fulcrum(
                            &viewing_fulcrum,
                            x__chunk_start + x, 
                            y__chunk_start + y)
                        );
            }
        }
    }
    return MUNIT_OK;
}

TEST_FUNCTION(
        init_hitbox_point_as__most_north_western_chunk_in__viewing_fulcrum) {
    Viewing_Fulcrum viewing_fulcrum;
    
    int32_t x__chunk_start, y__chunk_start;
    init_viewing_fulcrum_test__randomly__using_points(
            &viewing_fulcrum, 
            &x__chunk_start, 
            &y__chunk_start);

    Hitbox_Point chunk_position__most_north_western;
    init_hitbox_point_as__most_north_western_chunk_in__viewing_fulcrum(
            &chunk_position__most_north_western,
            &viewing_fulcrum);

    // TODO: replace 2 with appropriate const macro
    munit_assert_int32(
            chunk_position__most_north_western.x,
            ==,
            x__chunk_start - 2);
    munit_assert_int32(
            chunk_position__most_north_western.y,
            ==,
             y__chunk_start + 2);

    munit_assert_true(
            is_chunk_position_within__viewing_fulcrum(
                &viewing_fulcrum, 
                chunk_position__most_north_western.x, 
                chunk_position__most_north_western.y));

    return MUNIT_OK;
}

TEST_FUNCTION(
        init_hitbox_point_as__most_south_eastern_chunk_in__viewing_fulcrum) {
    Viewing_Fulcrum viewing_fulcrum;
    
    int32_t x__chunk_start, y__chunk_start;
    init_viewing_fulcrum_test__randomly__using_points(
            &viewing_fulcrum, 
            &x__chunk_start, 
            &y__chunk_start);

    Hitbox_Point chunk_position__most_south_eastern;
    init_hitbox_point_as__most_south_eastern_chunk_in__viewing_fulcrum(
            &chunk_position__most_south_eastern,
            &viewing_fulcrum);

    // TODO: replace 2 with appropriate const macro
    munit_assert_int32(
            chunk_position__most_south_eastern.x,
            ==,
            x__chunk_start + 2);
    munit_assert_int32(
            chunk_position__most_south_eastern.y,
            ==,
             y__chunk_start - 2);

    munit_assert_true(
            is_chunk_position_within__viewing_fulcrum(
                &viewing_fulcrum, 
                chunk_position__most_south_eastern.x, 
                chunk_position__most_south_eastern.y));

    return MUNIT_OK;
}

TEST_FUNCTION(gradually_get_extremum_positions_of__viewing_fulcrum) {
    Viewing_Fulcrum viewing_fulcrum;

    int32_t x__chunk_start, y__chunk_start;
    init_viewing_fulcrum_test__randomly__using_points(
            &viewing_fulcrum, 
            &x__chunk_start, 
            &y__chunk_start);

    return MUNIT_OK;
}

TEST_FUNCTION(get_next_chunk_position_in__viewing_fulcrum) {
    Viewing_Fulcrum viewing_fulcrum;

    int32_t x__chunk_start, y__chunk_start;
    init_viewing_fulcrum_test__randomly__using_points(
            &viewing_fulcrum, 
            &x__chunk_start, 
            &y__chunk_start);

    return MUNIT_OK;
}

TEST_FUNCTION(is_entity_within__viewing_fulcrum) {
    Viewing_Fulcrum viewing_fulcrum;

    int32_t x__chunk_start, y__chunk_start;
    init_viewing_fulcrum_test__randomly__using_points(
            &viewing_fulcrum, 
            &x__chunk_start, 
            &y__chunk_start);

    Entity entity;
    init_hitbox(&entity.hitbox,
            8,8, 
            (x__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE)
            + munit_rand_int_range(
                -VIEWING_FULCRUM__WIDTH/2,
                VIEWING_FULCRUM__WIDTH/2), 
            (y__chunk_start << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE)
            + munit_rand_int_range(
                -VIEWING_FULCRUM__LENGTH/2, 
                VIEWING_FULCRUM__LENGTH/2), 
            0);

    munit_assert_true(
            is_entity_within__viewing_fulcrum(
                &entity,
                &viewing_fulcrum));

    return MUNIT_OK;
}

// TEST_FUNCTION(MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM__at_origin) {
//     Viewing_Fulcrum viewing_fulcrum;
//     Chunk_Manager chunk_manager;
//     World_Parameters world_params;
//     init_viewing_fulcrum(&viewing_fulcrum);
// 
//     init_world_parameters(&world_params,
//             chunk_generator__test_f,
//             0);
//     init_chunk_manager(
//             &chunk_manager, &world_params);
// 
//     int32_t x__chunk__min =
//         get_aa__x__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
//     int32_t y__chunk__min =
//         get_aa__y__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
//     int32_t x__chunk__max =
//         get_bb__x__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
//     int32_t y__chunk__max =
//         get_bb__y__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
// 
//     int32_t x__range =
//         x__chunk__max - x__chunk__min + 1;
// 
//     int32_t index = 0;
// 
//     FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM(
//             (&viewing_fulcrum),
//             (&chunk_manager),
//             0,
//             current__chunk_map_node) {
//         int32_t x = index % x__range;
//         int32_t y = index / x__range;
// 
//         munit_assert_ptr_not_equal(
//                 current__chunk_map_node,
//                 0);
// 
//         Chunk_Manager__Chunk_Map_Node *expected_node =
//             get_chunk_map_node_from__chunk_manager(
//                     &chunk_manager, 
//                     x__chunk__min + x, 
//                     y__chunk__max - y, 
//                     0);
// 
//         munit_assert_ptr_equal(
//                 current__chunk_map_node,
//                 expected_node);
// 
//         index++;
//     }
// 
//     munit_assert_int32(
//             index,
//             ==,
//             x__range 
//             * (y__chunk__max - y__chunk__min + 1));
// 
//     return MUNIT_OK;
// }
// 
// TEST_FUNCTION(MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM) {
//     Viewing_Fulcrum viewing_fulcrum;
//     Chunk_Manager chunk_manager;
//     World_Parameters world_params;
// 
//     int32_t x__chunk_start, y__chunk_start;
//     init_viewing_fulcrum_test__randomly__using_points(
//             &viewing_fulcrum, 
//             &chunk_manager, 
//             &world_params, 
//             &x__chunk_start, 
//             &y__chunk_start);
// 
//     int32_t x__chunk__min =
//         get_aa__x__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
//     int32_t y__chunk__min =
//         get_aa__y__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
//     int32_t x__chunk__max =
//         get_bb__x__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
//     int32_t y__chunk__max =
//         get_bb__y__chunk_from__hitbox(&viewing_fulcrum.fulcrum);
// 
//     int32_t x__range =
//         x__chunk__max - x__chunk__min + 1;
// 
//     int32_t index = 0;
// 
//     FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM(
//             (&viewing_fulcrum),
//             (&chunk_manager),
//             0,
//             current__chunk_map_node) {
//         int32_t x = index % x__range;
//         int32_t y = index / x__range;
// 
//         munit_assert_ptr_not_equal(
//                 current__chunk_map_node,
//                 0);
// 
//         Chunk_Manager__Chunk_Map_Node *expected_node =
//             get_chunk_map_node_from__chunk_manager(
//                     &chunk_manager, 
//                     x__chunk__min + x, 
//                     y__chunk__max - y, 
//                     0);
// 
//         munit_assert_ptr_equal(
//                 current__chunk_map_node,
//                 expected_node);
// 
//         index++;
//     }
// 
//     munit_assert_int32(
//             index,
//             ==,
//             x__range 
//             * (y__chunk__max - y__chunk__min + 1));
// 
//     return MUNIT_OK;
// }

DEFINE_SUITE(viewing_fulcrum,
        INCLUDE_TEST__STATELESS
            (is_chunk_position_within__viewing_fulcrum),
        INCLUDE_TEST__STATELESS
            (init_hitbox_point_as__most_north_western_chunk_in__viewing_fulcrum),
        INCLUDE_TEST__STATELESS
            (init_hitbox_point_as__most_south_eastern_chunk_in__viewing_fulcrum),
        INCLUDE_TEST__STATELESS
            (gradually_get_extremum_positions_of__viewing_fulcrum),
        INCLUDE_TEST__STATELESS
            (get_next_chunk_position_in__viewing_fulcrum),
        INCLUDE_TEST__STATELESS
            (is_entity_within__viewing_fulcrum),
//         INCLUDE_TEST__STATELESS
//             (MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM__at_origin),
//         INCLUDE_TEST__STATELESS
//             (MACRO__FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM),
        END_TESTS)
