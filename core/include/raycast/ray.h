#ifndef RAY_H
#define RAY_H

#include "defines_weak.h"
#include "vectors.h"
#include <defines.h>

Ray__3i32F8 get_ray(
        Vector__3i32F4 starting_vector__3i32F4,
        Degree__u8 angle);

Ray__3i32F8 get_ray_as__extension(
        Ray__3i32F8 *p_ray,
        Degree__u8 angle);

void step_p_ray(Ray__3i32F8 *p_ray);
void step_p_ray_until__next_whole_integer(Ray__3i32F8 *p_ray);
void step_p_ray_until__next_tile(Ray__3i32F8 *p_ray);


static inline 
Vector__3i32F4 get_ray_endpoint_as__vector_3i32F4(
        Ray__3i32F8 *p_ray) {
    return vector_3i32F8_to__vector_3i32F4(
            p_ray->ray_current_vector__3i32F8);
}

static inline 
Vector__3i32 get_ray_endpoint_as__vector_3i32(
        Ray__3i32F8 *p_ray) {
    return vector_3i32F8_to__vector_3i32(
            p_ray->ray_current_vector__3i32F8);
}

static inline 
Vector__3i32F8 get_vector__3i32F8_wrt__p_ray_and_its_origin(
        Ray__3i32F8 *p_ray) {
    return subtract_vectors__3i32F8(
            p_ray->ray_current_vector__3i32F8,
            p_ray->ray_starting_vector__3i32F8);
}

static inline 
bool is_p_ray_within__length_i32F4(
        Ray__3i32F8 *p_ray,
        i32F4 length) {
    return is_vector_3i32F8_within__distance_i32F4(
            get_vector__3i32F8_wrt__p_ray_and_its_origin(p_ray),
            length);
}

static inline 
i32F4 get_squared_length_i32F4_of__ray(
        Ray__3i32F8 *p_ray) {
    Vector__3i32F4 delta_vector__3i32F4 =
        vector_3i32F8_to__vector_3i32F4(
                subtract_vectors__3i32F8(
                    p_ray->ray_current_vector__3i32F8,
                    p_ray->ray_starting_vector__3i32F8));

    return get_distance_squared_of__vector_3i32F4(
            delta_vector__3i32F4);
}

static inline 
i32F4 get_squared_length_i32F8_of__ray(
        Ray__3i32F8 *p_ray) {
    Vector__3i32F8 delta_vector__3i32F8 =
            subtract_vectors__3i32F8(
                p_ray->ray_current_vector__3i32F8,
                p_ray->ray_starting_vector__3i32F8);

    return get_distance_squared_of__vector_3i32F8(
            delta_vector__3i32F8);
}

#endif
