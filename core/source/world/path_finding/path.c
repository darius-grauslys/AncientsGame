#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "raycast/ray.h"
#include "vectors.h"
#include "world/tile.h"
#include "world/world.h"
#include <world/path_finding/path.h>

static inline
void update_path__heuristic_values(
        Path *p_path,
        Vector__3i32F4 destination) {
    Vector__3i32F4 ray_endpoint__3i32F4 =
        vector_3i32F8_to__vector_3i32F4(
            p_path->leading_ray_of__path
            .ray_current_vector__3i32F8);

    p_path->distance_squared__from_target__i32F4 =
        get_distance_squared_of__vector_3i32F4(
                subtract_vectors__3i32F4(
                    ray_endpoint__3i32F4,
                    destination));
    p_path->distance__hamming__i32F4 =
        get_distance_hamming_of__vectors_3i32F4(
                ray_endpoint__3i32F4,
                destination);
}

void initialize_path(
        Path *p_path,
        Vector__3i32F4 starting_point__3i32F4,
        Vector__3i32F4 destination__3i32F4,
        Degree__u8 starting_direction__degree_u8) {
    p_path->distance__travelled__i32F8 = 0;
    p_path->leading_ray_of__path =
        get_ray(
                starting_point__3i32F4,
                starting_direction__degree_u8);
    p_path->p_path_node__newest__3i32F4 =
        get_p_path_node_by__index_from__path(
                p_path, 
                0);
    p_path->p_path__branching = 0;

    for (Index__u8 index_of__path_node = 1;
            index_of__path_node
            < PATH_VECTORS_MAX_QUANTITY_OF;
            index_of__path_node++) {
        p_path->path_nodes__3i32F4
            [index_of__path_node] =
            VECTOR__3i32F4__OUT_OF_BOUNDS;
    }

    if (is_vectors_3i32F4__equal(
                destination__3i32F4, 
                VECTOR__3i32F4__OUT_OF_BOUNDS)) {
        p_path->distance_squared__from_target__i32F4 =
            BIT(31);
        p_path->distance__hamming__i32F4 =
            BIT(31);
        return;
    }
    update_path__heuristic_values(
            p_path, 
            destination__3i32F4);
}

///
/// Returns true if path
/// is not obstructed.
///
bool step_path(
        World *p_world,
        Path *p_path,
        Vector__3i32F4 destination) {
    Ray__3i32F8 ray__3i32F8 =
        p_path->leading_ray_of__path;
    step_p_ray_until__next_tile(
            &ray__3i32F8);
    Tile *p_tile =
        get_p_tile_from__world_using__ray_3i32F8(
                p_world, 
                &ray__3i32F8);
    if (is_tile__unpassable(p_tile)) {
        p_path->leading_ray_of__path =
            ray__3i32F8;
        return true;
    }

    Entity *p_entity =
        get_p_entity_from__world_using__ray_3i32F8(
                p_world, 
                &ray__3i32F8);

    if (p_entity) {
        bool is_p_entity__on_top_of__destination =
            is_vector_3i32F4_inside__hitbox(
                    destination, 
                    &p_entity->hitbox);
        if (!is_p_entity__on_top_of__destination)
            return true;
    }

    p_path->leading_ray_of__path =
        ray__3i32F8;

    update_path__heuristic_values(
            p_path, 
            destination);

    return false;
}

void commit_path_node_in__path(
        Path *p_path,
        Degree__u8 new_direction__degree_u8) {
    Index__u8 index_of__path_node =
        p_path->p_path_node__newest__3i32F4
        - p_path->path_nodes__3i32F4
        ;

    if (PATH_VECTORS_MAX_QUANTITY_OF
            <= index_of__path_node)
        index_of__path_node = 0;

    p_path->p_path_node__newest__3i32F4 =
        get_p_path_node_by__index_from__path(
                p_path, 
                index_of__path_node);

    *p_path->p_path_node__newest__3i32F4 =
        vector_3i32F8_to__vector_3i32F4(
                p_path
                ->leading_ray_of__path
                .ray_current_vector__3i32F8);

    p_path->distance__travelled__i32F8 +=
        get_squared_length_i32F4_of__ray(
                &p_path->leading_ray_of__path);
    p_path->leading_ray_of__path =
        get_ray(
                *p_path->p_path_node__newest__3i32F4,
                new_direction__degree_u8);
}

static inline
Signed_Quantity__i32 get_path_heuristic_value_from__sort_node(
        Sort_Node *p_sort_node) {
    Path *p_path =
        (Path*)p_sort_node->p_node_data;
    Signed_Quantity__i32 quantity =
        p_path->distance__hamming__i32F4
        + i32F8_to__i32F4(
                p_path->distance__travelled__i32F8)
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

