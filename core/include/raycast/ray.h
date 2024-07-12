#ifndef RAY_H
#define RAY_H

#include "defines_weak.h"
#include "vectors.h"
#include <defines.h>

Ray__3i32F20 get_ray(
        Vector__3i32F4 starting_vector__3i32F4,
        Degree__u9 angle);

Ray__3i32F20 get_ray_as__extension(
        Ray__3i32F20 *p_ray,
        Degree__u9 angle);

void step_p_ray(Ray__3i32F20 *p_ray);
void step_p_ray_until__next_whole_integer(Ray__3i32F20 *p_ray);
void step_p_ray_until__next_tile(Ray__3i32F20 *p_ray);


static inline 
Vector__3i32F4 get_ray_endpoint_as__vector_3i32F4(
        Ray__3i32F20 *p_ray) {
    return vector_3i32F20_to__vector_3i32F4(
            p_ray->ray_current_vector__3i32F20);
}

static inline 
Vector__3i32 get_ray_endpoint_as__vector_3i32(
        Ray__3i32F20 *p_ray) {
    return vector_3i32F20_to__vector_3i32(
            p_ray->ray_current_vector__3i32F20);
}

static inline 
Vector__3i32F20 get_vector__3i32F20_wrt__p_ray_and_its_origin(
        Ray__3i32F20 *p_ray) {
    return subtract_vectors__3i32F20(
            p_ray->ray_current_vector__3i32F20,
            p_ray->ray_starting_vector__3i32F20);
}

static inline 
bool is_p_ray_within__squared_length_i32(
        Ray__3i32F20 *p_ray,
        i32 length) {
    return is_vector_3i32F20_within__squared_distance_i32(
            get_vector__3i32F20_wrt__p_ray_and_its_origin(p_ray),
            length);
}

static inline 
i32F4 get_squared_length_i32F4_of__ray(
        Ray__3i32F20 *p_ray) {
    Vector__3i32F4 delta_vector__3i32F4 =
        vector_3i32F20_to__vector_3i32F4(
                subtract_vectors__3i32F20(
                    p_ray->ray_current_vector__3i32F20,
                    p_ray->ray_starting_vector__3i32F20));

    return get_distance_squared_of__vector_3i32F4(
            delta_vector__3i32F4);
}

static inline 
i32F4 get_squared_length_i32F20_of__ray(
        Ray__3i32F20 *p_ray) {
    Vector__3i32F20 delta_vector__3i32F20 =
            subtract_vectors__3i32F20(
                p_ray->ray_current_vector__3i32F20,
                p_ray->ray_starting_vector__3i32F20);

    debug_info("%d, %d",
            i32F20_to__i32(delta_vector__3i32F20.x__i32F20),
            i32F20_to__i32(delta_vector__3i32F20.y__i32F20));
    return get_distance_squared_of__vector_3i32F20(
            delta_vector__3i32F20);
}

#endif
