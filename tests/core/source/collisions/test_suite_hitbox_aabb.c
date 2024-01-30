#include <collisions/test_suite_hitbox_aabb.h>

#include <collisions/hitbox_aabb.c>

#warning Please make tests for: /home/shalidor/Projects/AncientsGame/tests/core/source/collisions/test_suite_hitbox_aabb.c

// Before writing any tests, please see the README
// found in ./tests

TEST_FUNCTION(is_hitbox__colliding__small_box_in_big) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);

    init_hitbox(&hitbox__two, 
            6, 6,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            1, 0, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__EAST);

    init_hitbox(&hitbox__two, 
            6, 6,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            -1, 0, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__WEST);

    init_hitbox(&hitbox__two, 
            6, 6,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            0, 1, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__NORTH);

    init_hitbox(&hitbox__two, 
            6, 6,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            0, -1, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__SOUTH);

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitbox__colliding__perfect_overlap) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    init_hitbox(&hitbox__one, 
            8, 8,
            -1, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            1, 0, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            0, 0, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__EAST);

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitbox__colliding__edge_inside) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            1, 0, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            7, 1, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__EAST);

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            -1, 0, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            -7, 1, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__WEST);

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            0, 1, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            1, 7, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__NORTH);

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            0, -1, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            1, -7, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__SOUTH);

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitbox__colliding__edge_entering) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            ENTITY_VELOCITY__PLAYER * 2, 0, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            8, 1, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__EAST);

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            -ENTITY_VELOCITY__PLAYER * 2, 0, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            -8, -1, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__WEST);

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            0, ENTITY_VELOCITY__PLAYER * 2, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            1, 8, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__NORTH);

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            0, -ENTITY_VELOCITY__PLAYER * 2, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            1, -8, 0);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__SOUTH);

    return MUNIT_OK;
}

TEST_FUNCTION(get_tile_transition_direction_of__hitbox) {
    Hitbox_AABB hitbox;
    Hitbox_Point aa, bb;
    Direction direction_of_transition;

    init_hitbox(&hitbox, 
            8, 8,
            3, 3, 0);
    apply_velocity_to__hitbox(&hitbox, 
            ENTITY_VELOCITY__PLAYER * 2, 0, 0);

    direction_of_transition =
        get_tile_transition_direction_of__hitbox(
                &hitbox,
                &aa, &bb);

    munit_assert_int32(
            direction_of_transition,
            ==,
            DIRECTION__EAST);
    munit_assert_int32(
            bb.x,
            ==,
            1);

    init_hitbox(&hitbox, 
            8, 8,
            3, 3, 0);
    apply_velocity_to__hitbox(&hitbox, 
            -ENTITY_VELOCITY__PLAYER * 2, 0, 0);

    direction_of_transition =
        get_tile_transition_direction_of__hitbox(
                &hitbox,
                &aa, &bb);

    munit_assert_int32(
            direction_of_transition,
            ==,
            DIRECTION__WEST);
    munit_assert_int32(
            aa.x,
            ==,
            -1);
    
    init_hitbox(&hitbox, 
            8, 8,
            3, 3, 0);
    apply_velocity_to__hitbox(&hitbox, 
            0, ENTITY_VELOCITY__PLAYER * 2, 0);

    direction_of_transition =
        get_tile_transition_direction_of__hitbox(
                &hitbox,
                &aa, &bb);

    munit_assert_int32(
            direction_of_transition,
            ==,
            DIRECTION__NORTH);
    munit_assert_int32(
            bb.y,
            ==,
            1);

    init_hitbox(&hitbox, 
            8, 8,
            3, 3, 0);
    apply_velocity_to__hitbox(&hitbox, 
            0, -ENTITY_VELOCITY__PLAYER * 2, 0);

    direction_of_transition =
        get_tile_transition_direction_of__hitbox(
                &hitbox,
                &aa, &bb);

    munit_assert_int32(
            direction_of_transition,
            ==,
            DIRECTION__SOUTH);
    munit_assert_int32(
            aa.y,
            ==,
            -1);

    return MUNIT_OK;
}

DEFINE_SUITE(hitbox_aabb, 
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__small_box_in_big),
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__perfect_overlap),
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__edge_inside),
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__edge_entering),
        INCLUDE_TEST__STATELESS
            (get_tile_transition_direction_of__hitbox),
        END_TESTS)
