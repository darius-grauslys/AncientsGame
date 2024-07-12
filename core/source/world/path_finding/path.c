#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "raycast/ray.h"
#include "vectors.h"
#include "world/tile.h"
#include "world/world.h"
#include <world/path_finding/path.h>

static inline
i32 get_distance_squared_of__path_ray_to__destination(
        Vector__3i32F4 ray_endpoint__3i32,
        Vector__3i32 destination) {
    return
        get_distance_squared_of__vector_3i32F4(
                subtract_vectors__3i32F4(
                    ray_endpoint__3i32,
                    vector_3i32_to__vector_3i32F4(
                        destination)));
}

static inline
void update_path__heuristic_values(
        Path *p_path,
        Vector__3i32F4 ray_endpoint__3i32F4,
        Vector__3i32 destination) {
    p_path->distance_squared__from_target__i32F4 =
        get_distance_squared_of__path_ray_to__destination(
                ray_endpoint__3i32F4, 
                destination);
    p_path->distance__hamming__i32 =
        get_distance_hamming_of__vectors_3i32(
                vector_3i32F4_to__vector_3i32(
                    ray_endpoint__3i32F4),
                destination);
}

void initialize_path(
        Path *p_path,
        Vector__3i32 starting_point__3i32,
        Vector__3i32 destination__3i32,
        Degree__u9 starting_direction__degree_u8,
        bool is_rotating__left_or__right) {
    p_path->distance__travelled__i32F20 = 0;
    p_path->leading_ray_of__path =
        get_ray(
                vector_3i32_to__vector_3i32F4(
                    starting_point__3i32),
                starting_direction__degree_u8);
    p_path->p_path_node__newest__3i32 =
        get_p_path_node_by__index_from__path(
                p_path, 
                0);
    *p_path->p_path_node__newest__3i32 =
        starting_point__3i32;
    p_path->p_path__branching = 0;

    for (Index__u8 index_of__path_node = 1;
            index_of__path_node
            < PATH_VECTORS_MAX_QUANTITY_OF;
            index_of__path_node++) {
        p_path->path_nodes__3i32
            [index_of__path_node] =
            VECTOR__3i32__OUT_OF_BOUNDS;
    }

    if (is_vectors_3i32__equal(
                destination__3i32, 
                VECTOR__3i32__OUT_OF_BOUNDS)) {
        p_path->distance_squared__from_target__i32F4 =
            BIT(31);
        p_path->distance__hamming__i32 =
            BIT(29);
        return;
    }

    Vector__3i32F4 ray_endpoint__3i32F4 =
        vector_3i32F20_to__vector_3i32F4(
            p_path->leading_ray_of__path
            .ray_current_vector__3i32F20);
    update_path__heuristic_values(
            p_path, 
            ray_endpoint__3i32F4,
            destination__3i32);
    p_path->
        is_rotating__left_or__right =
        is_rotating__left_or__right;
    p_path->state_of__path =
        Path_Stepping_State__Progressing;
}

void initialize_path_as__unusued(
        Path *p_path) {
    initialize_path(
            p_path, 
            VECTOR__3i32__OUT_OF_BOUNDS, 
            VECTOR__3i32__OUT_OF_BOUNDS, 
            0, 
            false);
    p_path->p_path_node__newest__3i32 = 0;
}

void initialize_path_as__branching_path(
        Path *p_path,
        Path *p_path__branching_from,
        Vector__3i32 destination__3i32,
        Degree__u9 starting_direction__degree_u8) {
    initialize_path(
            p_path,
            *p_path__branching_from
            ->p_path_node__newest__3i32,
            destination__3i32,
            starting_direction__degree_u8,
            !p_path->is_rotating__left_or__right);
    p_path->distance__travelled__i32F20 =
        p_path__branching_from
        ->distance__travelled__i32F20;
}

///
/// Returns true if path
/// is not obstructed.
///
enum Path_Stepping_State step_path(
        World *p_world,
        Path *p_path,
        Vector__3i32 destination) {
    Ray__3i32F20 ray__3i32F20 =
        p_path->leading_ray_of__path;

    step_p_ray(
            &ray__3i32F20);

    Tile *p_tile =
        get_p_tile_from__world_using__ray_3i32F20(
                p_world, 
                &ray__3i32F20);
    if (!p_tile || is_tile__unpassable(p_tile)) {
        return Path_Stepping_State__Obstructed;
    }

    Vector__3i32F4 ray_endpoint__3i32F4 =
        vector_3i32F20_to__vector_3i32F4(
                ray__3i32F20
                .ray_current_vector__3i32F20);
    i32F4 stepping_distance =
        get_distance_squared_of__path_ray_to__destination(
                ray_endpoint__3i32F4,
                destination);

    if (stepping_distance
            > p_path->distance_squared__from_target__i32F4) {
        return Path_Stepping_State__Deviating;
    }

    p_path->leading_ray_of__path =
        ray__3i32F20;

    update_path__heuristic_values(
            p_path, 
            ray_endpoint__3i32F4,
            destination);

    return Path_Stepping_State__Progressing;
}

void commit_path_node_in__path(
        Path *p_path,
        Degree__u9 new_direction__degree_u8) {
    Index__u8 index_of__path_node =
        (p_path->p_path_node__newest__3i32
        - p_path->path_nodes__3i32) 
        + 1
        ;

    if (PATH_VECTORS_MAX_QUANTITY_OF
            <= index_of__path_node)
        index_of__path_node = 0;

    p_path->p_path_node__newest__3i32 =
        get_p_path_node_by__index_from__path(
                p_path, 
                index_of__path_node);

    *p_path->p_path_node__newest__3i32 =
        vector_3i32F20_to__vector_3i32(
                p_path
                ->leading_ray_of__path
                .ray_current_vector__3i32F20);

    p_path->distance__travelled__i32F20 +=
        get_squared_length_i32F20_of__ray(
                &p_path->leading_ray_of__path);
    p_path->leading_ray_of__path
        .ray_starting_vector__3i32F20 =
        p_path->leading_ray_of__path
        .ray_current_vector__3i32F20;
}

static inline
Signed_Quantity__i32 get_path_heuristic_value_from__sort_node(
        Sort_Node *p_sort_node) {
    Path *p_path =
        (Path*)p_sort_node->p_node_data;
    Signed_Quantity__i32 quantity =
        p_path->distance__hamming__i32
        + i32F20_to__i32(
                p_path->distance__travelled__i32F20)
        ;

    return quantity;
}

Signed_Quantity__i32 f_sort_heuristic__path(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two) {
    Signed_Quantity__i32 difference =
        get_path_heuristic_value_from__sort_node(
                p_sort_node__one)
        - get_path_heuristic_value_from__sort_node(
                p_sort_node__two);
    return (difference < 0) - (difference > 0);
}

