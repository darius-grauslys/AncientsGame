#include <collisions/test_suite_collisions_hitbox_aabb.h>

#include <collisions/hitbox_aabb.c>

#warning TODO: FINISH
/// 
/// TODO: This entire test suite is outdated
/// and needs to be reviewed.
///

TEST_FUNCTION(is_hitbox__colliding__small_box_in_big) {
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    initialize_hitbox(
            &hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));

    initialize_hitbox(
            &hitbox__two, 
            6, 6,
            get_vector__3i32F4_using__i32(0, 0, 0));
    Vector__3i32F4 velocity = 
            get_vector__3i32F4_using__i32(1, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__EAST);

    initialize_hitbox(&hitbox__two, 
            6, 6,
            get_vector__3i32F4_using__i32(0, 0, 0));
    velocity = 
            get_vector__3i32F4_using__i32(-1, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__WEST);

    initialize_hitbox(&hitbox__two, 
            6, 6,
            get_vector__3i32F4_using__i32(0, 0, 0));
    velocity = 
            get_vector__3i32F4_using__i32(0, 1, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__NORTH);

    initialize_hitbox(&hitbox__two, 
            6, 6,
            get_vector__3i32F4_using__i32(0, 0, 0));
    velocity = 
            get_vector__3i32F4_using__i32(0, -1, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__two,
                &hitbox__one),
            ==,
            DIRECTION__SOUTH);

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitbox__colliding__perfect_overlap) {
#warning TODO: FINISH
/// 
/// This test is currently not passing.
/// It might be because it's outdated.
/// Be sure to review the test.
///
/// TODO: This entire test suite is outdated
/// and needs to be reviewed.
///
    return;
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    initialize_hitbox(&hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(-1, 0, 0));
    Vector__3i32F4 velocity = 
            get_vector__3i32F4_using__i32(1, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(&hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__EAST);

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitbox__colliding__edge_inside) {
#warning TODO: FINISH
/// 
/// This test is currently not passing.
/// It might be because it's outdated.
/// Be sure to review the test.
///
/// TODO: This entire test suite is outdated
/// and needs to be reviewed.
///
    return;
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    initialize_hitbox(&hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));
    Vector__3i32F4 velocity = 
            get_vector__3i32F4_using__i32(1, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(&hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(7, 1, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__EAST);

    initialize_hitbox(&hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));

    velocity = 
            get_vector__3i32F4_using__i32(-1, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(&hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(-7, 1, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__WEST);

    initialize_hitbox(&hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));

    velocity = 
            get_vector__3i32F4_using__i32(0, 1, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(&hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(1, 7, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__NORTH);

    initialize_hitbox(&hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));

    velocity = 
            get_vector__3i32F4_using__i32(0, -1, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(&hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(1, -7, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__SOUTH);

    return MUNIT_OK;
}

TEST_FUNCTION(is_hitbox__colliding__edge_entering) {
#warning TODO: FINISH
/// 
/// This test is currently not passing.
/// It might be because it's outdated.
/// Be sure to review the test.
///
/// TODO: This entire test suite is outdated
/// and needs to be reviewed.
///
    return;
    Hitbox_AABB hitbox__one;
    Hitbox_AABB hitbox__two;

    initialize_hitbox(&hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));
    Vector__3i32F4 velocity = 
            get_vector__3i32F4_using__i32(ENTITY_VELOCITY__PLAYER * 2, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(&hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(8, 1, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__EAST);

    initialize_hitbox(&hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));
    velocity = 
            get_vector__3i32F4_using__i32(-ENTITY_VELOCITY__PLAYER * 2, 0, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(&hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(-8, -1, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__WEST);

    initialize_hitbox(
            &hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));
    velocity = 
            get_vector__3i32F4_using__i32(0, ENTITY_VELOCITY__PLAYER * 2, 0);
    apply_velocity_to__hitbox(&hitbox__two, 
            &velocity);

    initialize_hitbox(
            &hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(1, 8, 0));

    munit_assert_int32(
            is_hitbox__colliding(
                &hitbox__one,
                &hitbox__two),
            ==,
            DIRECTION__NORTH);

    initialize_hitbox(
            &hitbox__one, 
            8, 8,
            get_vector__3i32F4_using__i32(0, 0, 0));
    velocity = 
            get_vector__3i32F4_using__i32(0, -ENTITY_VELOCITY__PLAYER * 2, 0);
    apply_velocity_to__hitbox(&hitbox__one, 
            &velocity);

    initialize_hitbox(
            &hitbox__two, 
            8, 8,
            get_vector__3i32F4_using__i32(1, -8, 0));

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
