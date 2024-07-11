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

Ray__3i32F8 get_ray_as__extension(
        Ray__3i32F8 *p_ray,
        Degree__u8 angle) {
    return (Ray__3i32F8) {
        p_ray->ray_current_vector__3i32F8,
        p_ray->ray_current_vector__3i32F8,
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

