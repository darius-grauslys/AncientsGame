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

DEFINE_SUITE(hitbox_aabb, 
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__small_box_in_big),
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__perfect_overlap),
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__edge_inside),
        INCLUDE_TEST__STATELESS
            (is_hitbox__colliding__edge_entering),
        END_TESTS)
