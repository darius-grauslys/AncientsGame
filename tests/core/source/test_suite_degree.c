#include "defines.h"
#include "defines_weak.h"
#include "degree.h"
#include "raycast/ray.h"
#include "vectors.h"
#include <test_suite_degree.h>

#include <math.h>

#include <degree.c>

i32 get_angle_with__clib(
        double x, 
        double y) {
    if (x == 0) {
        if (y < 0)
            return 180;
        if (y > 0)
            return 0;
        return 0;
    } else if (y == 0) {
        if (x < 0) 
            return 270;
        if (x > 0)
            return 90;
    }

    i32 angle = (int)floor(90.0 * (atan(fabs(y)/fabs(x)) / M_PI));

    if (y < 0) {
        if (x < 0) {
            angle += 180;
        } else {
            angle += 90;
        }
    } else {
        if (x < 0) {
            angle += 270;
        }
    }

    return angle;
}

TEST_FUNCTION(get_angle_between__vectors_3i32__cardinal_directions) {
    munit_assert_uint16(
            get_angle_between__vectors_3i32(
                get_vector__3i32(0, 0, 0), 
                get_vector__3i32(0, 1, 0)), 
            ==, 
            0);
    munit_assert_uint16(
            get_angle_between__vectors_3i32(
                get_vector__3i32(0, 0, 0), 
                get_vector__3i32(1, 0, 0)), 
            ==, 
            ANGLE__90);
    munit_assert_uint16(
            get_angle_between__vectors_3i32(
                get_vector__3i32(0, 0, 0), 
                get_vector__3i32(0, -1, 0)), 
            ==, 
            ANGLE__180);
    munit_assert_uint16(
            get_angle_between__vectors_3i32(
                get_vector__3i32(0, 0, 0), 
                get_vector__3i32(-1, 0, 0)), 
            ==, 
            ANGLE__270);

    return MUNIT_OK;
}

i32 convert_core_angle_to__integer_angle(
        Degree__u9 angle) {
    i32 actual = 
        (int)floor(
                (double)angle
                / (double)ANGLE__360 
                * 360.0);
    return actual;
}

MunitResult test_angle_to(
        i32 x, i32 y) {
    const i32 epsilon = 8;

    i32 correct = get_angle_with__clib(x, y);
    i32 from_core = 
        get_angle_between__vectors_3i32(
                get_vector__3i32(0, 0, 0), 
                get_vector__3i32(
                    x, 
                    y, 
                    0));
    i32 actual = 
        convert_core_angle_to__integer_angle(from_core);
    i32 error = 
            abs(actual - correct);

    munit_assert_int(error, <, epsilon);

    return MUNIT_OK;
}

MunitResult test_quadrant(
        i32 x__min,
        i32 x__max,
        i32 y__min,
        i32 y__max) {
    const Quantity__u32 quantity_of__trials = 64;

    for (u32 step = 0;
            step
            < quantity_of__trials;
            step++) {
        i32 x, y;
        x = munit_rand_int_range(x__min, x__max);
        y = munit_rand_int_range(y__min, y__max);

        test_angle_to(x, y);
    }

    return MUNIT_OK;
}

TEST_FUNCTION(get_angle_between__vectors_3i32__quadrant_one) {
    test_quadrant(
            0, 100,
            0, 100);

    return MUNIT_OK;
}

TEST_FUNCTION(get_angle_between__vectors_3i32__quadrant_two) {
    test_quadrant(
            0, 100,
            -100, 0);

    return MUNIT_OK;
}

TEST_FUNCTION(get_angle_between__vectors_3i32__quadrant_three) {
    test_quadrant(
            -100, 0,
            -100, 0);

    return MUNIT_OK;
}

TEST_FUNCTION(get_angle_between__vectors_3i32__quadrant_four) {
    test_quadrant(
            -100, 0,
            0, 100);

    return MUNIT_OK;
}

TEST_FUNCTION(get_angle_between__vectors_3i32_in__a_circle) {
    const double epsilon = 12.0;
    for (double angle=0.0;angle<360.0;angle+=0.25) {
        i32 x = munit_rand_int_range(10, 15) * sin(angle / 360.0 * M_PI);
        i32 y = munit_rand_int_range(10, 15) * cos(angle / 360.0 * M_PI);

        Degree__u9 from_core =
            get_angle_between__vectors_3i32(
                    get_vector__3i32(0, 0, 0), 
                    get_vector__3i32(x, y, 0)
                    );

        i32 actual = 
            convert_core_angle_to__integer_angle(from_core);
        double error = 
                fabs(actual - angle);

        munit_assert_int(error, <, epsilon);
    }
    return MUNIT_OK;
}

DEFINE_SUITE(degree,
        INCLUDE_TEST__STATELESS(get_angle_between__vectors_3i32__cardinal_directions),
        INCLUDE_TEST__STATELESS(get_angle_between__vectors_3i32__quadrant_one),
        INCLUDE_TEST__STATELESS(get_angle_between__vectors_3i32__quadrant_two),
        INCLUDE_TEST__STATELESS(get_angle_between__vectors_3i32__quadrant_three),
        INCLUDE_TEST__STATELESS(get_angle_between__vectors_3i32__quadrant_one),
        INCLUDE_TEST__STATELESS(get_angle_between__vectors_3i32_in__a_circle),
        END_TESTS)
