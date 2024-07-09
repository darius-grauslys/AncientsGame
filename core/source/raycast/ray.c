#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "vectors.h"
#include <raycast/ray.h>

extern Vector__3i32F8 __DEGREE_TO_2i32F10__LOOKUP_TABLE[255];

Ray__3i32F8 get_ray(
        Vector__3i32F4 starting_vector__3i32F4,
        Degree__u8 angle) {
    return (Ray__3i32F8) {
        vector_3i32F4_to__vector_3i32F8(starting_vector__3i32F4),
        vector_3i32F4_to__vector_3i32F8(starting_vector__3i32F4),
        angle
    };
}

void step_p_ray(Ray__3i32F8 *p_ray) {
    add_p_vectors__3i32F8(
            &p_ray->ray_current_vector__3i32F8, 
            &__DEGREE_TO_2i32F10__LOOKUP_TABLE[p_ray->angle_of__ray]);
}

void step_p_ray_until__next_whole_integer(Ray__3i32F8 *p_ray) {
    Signed_Quantity__i32 x, y;    
    //TODO: magic numbers
    x = p_ray->ray_current_vector__3i32F8.x__i32F8 >> 8;
    y = p_ray->ray_current_vector__3i32F8.y__i32F8 >> 8;

    do {
        step_p_ray(p_ray);
    } while (
            p_ray->ray_current_vector__3i32F8.x__i32F8 >> 8
            == x
            && p_ray->ray_current_vector__3i32F8.y__i32F8 >> 8
            == y);
}

void step_p_ray_until__next_tile(Ray__3i32F8 *p_ray) {
    Signed_Quantity__i32 x, y;    
    //TODO: magic numbers
    x = p_ray->ray_current_vector__3i32F8.x__i32F8 >> 11;
    y = p_ray->ray_current_vector__3i32F8.y__i32F8 >> 11;

    do {
        step_p_ray(p_ray);
    } while (
            p_ray->ray_current_vector__3i32F8.x__i32F8 >> 11
            == x
            && p_ray->ray_current_vector__3i32F8.y__i32F8 >> 11
            == y);
}

i32F8 get_middle_degree(
        i32F8 degree__one,
        i32F8 degree__two) {
    if (degree__one < degree__two)
        return (degree__one + degree__two) >> 1;
    return ((degree__one + degree__two + 256) >> 1);
}

Degree__u8 get_degree(
        Vector__3i32F4 *p_source__3i32F4, 
        Vector__3i32F4 *p_target__3i32F4) {
    i32F8 pivots[2];
    i32F8 *p_pivot__d_x, *p_pivot__d_y;

    // step 1) find cartesian quadrant

    i32 d_x = 
        p_target__3i32F4->x__i32F4
        - p_source__3i32F4->x__i32F4
        ;
    i32 d_y = 
        p_target__3i32F4->y__i32F4
        - p_source__3i32F4->y__i32F4
        ;

    // trivial cases
    if (!d_x && !d_y)
        return 0;
    if (!d_x)
        return 
            (d_y < 0)
            ? 128
            : 0
            ;
    if (!d_y)
        return
            (d_x < 0)
            ? 192
            : 64
            ;

    if (d_x > 0 && d_y > 0) {
        // quad 1 (x+, y+) 
        pivots[0] = i32_to__i32F8(0);
        pivots[1] = i32_to__i32F8(64);

        p_pivot__d_x = &pivots[1];
        p_pivot__d_y = &pivots[0];
    } else if (d_x > 0 && d_y < 0) {
        // quad 2 (x+, y-)
        pivots[0] = i32_to__i32F8(64);
        pivots[1] = i32_to__i32F8(128);

        p_pivot__d_x = &pivots[0];
        p_pivot__d_y = &pivots[1];
    } else if (d_x < 0 && d_y < 0) {
        // quad 3 (x-, y-)
        pivots[0] = i32_to__i32F8(128);
        pivots[1] = i32_to__i32F8(192);

        p_pivot__d_x = &pivots[1];
        p_pivot__d_y = &pivots[0];
    } else {
        // quad 4 (x+, y-)
        pivots[0] = i32_to__i32F8(192);
        pivots[1] = i32_to__i32F8(256);

        p_pivot__d_x = &pivots[0];
        p_pivot__d_y = &pivots[1];
    }

    d_x = abs(d_x);
    d_y = abs(d_y);

    i32F8 degree__between_pivots =
        get_middle_degree(
                pivots[0], 
                pivots[1]);

    if (d_x == d_y)
        return degree__between_pivots;

    i32F8 distance = 0;
    do {
        if (d_x < d_y) {
            d_y -= d_x;

            *p_pivot__d_x =
                degree__between_pivots;
        } else {
            d_x -= d_y;

            *p_pivot__d_y =
                degree__between_pivots;
        }
        degree__between_pivots =
            get_middle_degree(
                    pivots[0], 
                    pivots[1]);
        distance =
            pivots[0] - pivots[1];
    } while (
            !(distance < i32_to__i32F8(1) 
                && distance > i32_to__i32F8(-1))
            && d_x != d_y);

    Degree__u8 fractional =
        degree__between_pivots
        & MASK(8);

    Degree__u8 integer =
        (degree__between_pivots 
         >> FRACTIONAL_PERCISION_8__BIT_SIZE)
        & MASK(8);

    return integer
        + (bool)(fractional & BIT(7));
}
