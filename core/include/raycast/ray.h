#ifndef RAY_H
#define RAY_H

#include "defines_weak.h"
#include "vectors.h"
#include <defines.h>

Ray__3i32F8 get_ray(
        Vector__3i32F4 starting_vector__3i32F4,
        Degree__u8 angle);

void step_p_ray(Ray__3i32F8 *p_ray);
void step_p_ray_until__next_whole_integer(Ray__3i32F8 *p_ray);
void step_p_ray_until__next_tile(Ray__3i32F8 *p_ray);

///
/// Log(N) complexity get degree.
///
Degree__u8 get_degree(
        Vector__3i32F4 *p_source__3i32F4, 
        Vector__3i32F4 *p_target__3i32F4);

static Vector__3i32F4 inline get_endpoint_of__p_ray_as__vector_3i32F4(
        Ray__3i32F8 *p_ray) {
    return vector_3i32F8_to__vector_3i32F4(p_ray->ray_current_vector__3i32F8);
}

static Vector__3i32F8 inline get_vector__3i32F8_wrt__p_ray_and_its_origin(
        Ray__3i32F8 *p_ray) {
    return subtract_vectors__3i32F8(
            p_ray->ray_current_vector__3i32F8,
            p_ray->ray_starting_vector__3i32F8);
}

static bool inline is_p_ray_within__length_i32F4(
        Ray__3i32F8 *p_ray,
        i32F4 length) {
    return is_vector_3i32F8_within__distance_i32F4(
            get_vector__3i32F8_wrt__p_ray_and_its_origin(p_ray),
            length);
}

#endif
