#include <collisions/test_suite_hitbox_aabb.h>

#include <collisions/hitbox_aabb.c>

#warning Please make tests for: /home/shalidor/Projects/AncientsGame/tests/core/source/collisions/test_suite_hitbox_aabb.c

// Before writing any tests, please see the README
// found in ./tests

TEST_FUNCTION(is_hitboxes__overlapping__small_box_in_big) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);

    init_hitbox(&hitbox__two, 
            6, 6,
            0, 0, 0);

    munit_assert_true(
            is_hitboxes__overlapping(
                &hitbox__one,
                &hitbox__two));

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitboxes__overlapping__perfect_overlap) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            0, 0, 0);

    munit_assert_true(
            is_hitboxes__overlapping(
                &hitbox__one,
                &hitbox__two));

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitboxes__overlapping__edge_inside) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    init_hitbox(&hitbox__one, 
            8, 8,
            0, 0, 0);

    init_hitbox(&hitbox__two, 
            8, 8,
            7, 0, 0);

    munit_assert_true(
            is_hitboxes__overlapping(
                &hitbox__one,
                &hitbox__two));

    return MUNIT_OK;
}

DEFINE_SUITE(hitbox_aabb, 
        INCLUDE_TEST__STATELESS
            (is_hitboxes__overlapping__small_box_in_big),
        INCLUDE_TEST__STATELESS
            (is_hitboxes__overlapping__perfect_overlap),
        INCLUDE_TEST__STATELESS
            (is_hitboxes__overlapping__edge_inside),
        END_TESTS)
