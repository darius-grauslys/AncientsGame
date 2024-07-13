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
    p_path->
        is_rotating__left_or__right =
        is_rotating__left_or__right;
    p_path->state_of__path_progression =
        Path_Progression_State__Progressing;
    p_path->index_of__path_node = 0;
    p_path->index_of__incident = 0;

    p_path->path_nodes__3i32[0] =
        starting_point__3i32;

    for (Index__u8 index_of__path_node = 1;
            index_of__path_node
            < PATH_VECTORS_MAX_QUANTITY_OF;
            index_of__path_node++) {
        p_path->path_nodes__3i32
            [index_of__path_node] =
            VECTOR__3i32__OUT_OF_BOUNDS;
        p_path->obstruction_indicent_stack
            [index_of__path_node] =
            ANGLE__OUT_OF_BOUNDS;
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
}

void initialize_path_as__branching_path(
        Path *p_path,
        Path *p_path__branching_from,
        Vector__3i32 destination__3i32,
        Degree__u9 starting_direction__degree_u8) {
    for (Index__u8 index_of__path_node = 1;
            index_of__path_node
            < p_path__branching_from->index_of__path_node;
            index_of__path_node++) {
        p_path->path_nodes__3i32
            [index_of__path_node] =
            p_path__branching_from
                ->path_nodes__3i32[index_of__path_node];
        p_path->obstruction_indicent_stack
            [index_of__path_node] =
            p_path__branching_from
                ->obstruction_indicent_stack[index_of__path_node];
    }

    p_path->distance__travelled__i32F20 =
        p_path__branching_from
        ->distance__travelled__i32F20;
    p_path->leading_ray_of__path =
        p_path__branching_from->leading_ray_of__path;
    p_path->
        is_rotating__left_or__right =
        !p_path__branching_from
        ->is_rotating__left_or__right;
    p_path->state_of__path_progression =
        p_path__branching_from
        ->state_of__path_progression;
    p_path->index_of__path_node = 
        p_path__branching_from
        ->index_of__path_node;
    p_path->index_of__incident =
        p_path__branching_from
        ->index_of__incident;
}

bool pop_obstruction_incident_from__path(
        Path *p_path) {
    p_path->obstruction_indicent_stack
        [p_path->index_of__incident] =
        ANGLE__OUT_OF_BOUNDS;
    if (p_path->index_of__path_node == 0) {
        return true;
    }
    p_path->index_of__incident--;

    return false;
}

bool push_obstruction_incident_onto__path(
        Path *p_path,
        Degree__u9 angle_of__obstruction_incident) {
    if (p_path->index_of__incident + 1
            >= PATH_VECTORS_MAX_QUANTITY_OF) {
        return true;
    }

    p_path->obstruction_indicent_stack
        [p_path->index_of__incident] =
        angle_of__obstruction_incident;

    return false;
}

///
/// Returns true if path
/// is not obstructed.
///
enum Path_Stepping_Result step_path(
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
        return Path_Stepping_Result__Obstructed;
    }

    Vector__3i32F4 ray_endpoint__3i32F4 =
        vector_3i32F20_to__vector_3i32F4(
                ray__3i32F20
                .ray_current_vector__3i32F20);

    p_path->leading_ray_of__path =
        ray__3i32F20;

    update_path__heuristic_values(
            p_path, 
            ray_endpoint__3i32F4,
            destination);

    return Path_Stepping_Result__Unobstructed;
}

bool commit_path_node_in__path(
        Path *p_path,
        Degree__u9 new_direction__degree_u8) {
    if (p_path->index_of__path_node + 1
            >= PATH_VECTORS_MAX_QUANTITY_OF) {
        return true;
    }

    p_path->path_nodes__3i32
        [p_path->index_of__path_node] =
        vector_3i32F20_to__vector_3i32(
                p_path
                ->leading_ray_of__path
                .ray_current_vector__3i32F20);

    p_path->index_of__path_node++;

    p_path->distance__travelled__i32F20 +=
        get_squared_length_i32F20_of__ray(
                &p_path->leading_ray_of__path);
    p_path->leading_ray_of__path
        .ray_starting_vector__3i32F20 =
        p_path->leading_ray_of__path
        .ray_current_vector__3i32F20;

    return false;
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

Signed_Quantity__i32 f_sort_heuristic__min_path(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two) {
    Signed_Quantity__i32 difference =
        get_path_heuristic_value_from__sort_node(
                p_sort_node__one)
        - get_path_heuristic_value_from__sort_node(
                p_sort_node__two);
    return (difference < 0) - (difference > 0);
}

Signed_Quantity__i32 f_sort_heuristic__max_path(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two) {
    Signed_Quantity__i32 difference =
        get_path_heuristic_value_from__sort_node(
                p_sort_node__one)
        - get_path_heuristic_value_from__sort_node(
                p_sort_node__two);
    return (difference > 0) - (difference < 0);
}

