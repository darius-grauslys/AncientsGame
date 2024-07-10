#ifndef PATH_H
#define PATH_H

#include "defines_weak.h"
#include "vectors.h"
#include <defines.h>

void initialize_path(
        Path *p_path,
        Vector__3i32F4 starting_point__3i32F4,
        Vector__3i32F4 destination__3i32F4,
        Degree__u8 starting_direction__degree_u8);

static inline
void initialize_path_as__unusued(
        Path *p_path) {
    initialize_path(
            p_path, 
            VECTOR__3i32F4__OUT_OF_BOUNDS, 
            VECTOR__3i32F4__OUT_OF_BOUNDS, 
            0);
}

static inline
void initialize_path_as__branching_path(
        Path *p_path,
        Path *p_path__branching_from,
        Vector__3i32F4 destination__3i32F4,
        Degree__u8 starting_direction__degree_u8) {
    initialize_path(
            p_path,
            *p_path__branching_from
            ->p_path_node__newest__3i32F4,
            destination__3i32F4,
            starting_direction__degree_u8);
}

static inline
void set_branching_path_of__this_path(
        Path *p_path,
        Path *p_path__branching,
        Vector__3i32F4 destination_of__branching_path_3i32F4,
        Degree__u8 starting_direction_of__branching_path) {
    p_path->p_path__branching =
        p_path__branching;
    initialize_path_as__branching_path(
            p_path__branching, p_path, 
            destination_of__branching_path_3i32F4, 
            starting_direction_of__branching_path);
}

static inline
bool is_path__branched(
        Path *p_path) {
    return p_path->p_path__branching;
}

///
/// Returns true if path
/// is not obstructed.
///
bool step_path(
        World *p_world,
        Path *p_path,
        Vector__3i32F4 destination);

///
/// This makes the ray_current_vector__3i32F8
/// of the path the new path_node
/// (overwritting oldest if needed.)
///
/// It will then reset the path's ray
/// to this newest node with the given direction.
///
void commit_path_node_in__path(
        Path *p_path,
        Degree__u8 new_direction__degree_u8);

Signed_Quantity__i32 f_sort_heuristic__path(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two);

Signed_Quantity__i32 f_evaluation_heuristic__path(
        Sort_Node *p_sort_node);

static inline
void change_direction_of__path(
        Path *p_path,
        Degree__u8 new_direction__degree_u8) {
    p_path->leading_ray_of__path.angle_of__ray =
        new_direction__degree_u8;
}

static inline
Vector__3i32F4 get_path_node_by__index_from__path(
        Path *p_path,
        Index__u8 index_of__path_node) {
#ifndef NDEBUG
    if (PATH_VECTORS_MAX_QUANTITY_OF
            <= index_of__path_node) {
        debug_abort("get_path_node_by__index_from__path, out of bounds: %d > %d",
                index_of__path_node,
                PATH_VECTORS_MAX_QUANTITY_OF);
        return VECTOR__3i32F4__OUT_OF_BOUNDS;
    }
#endif
    return p_path
        ->path_nodes__3i32F4[index_of__path_node];
}

static inline
Vector__3i32F4 *get_p_path_node_by__index_from__path(
        Path *p_path,
        Index__u8 index_of__path_node) {
#ifndef NDEBUG
    if (PATH_VECTORS_MAX_QUANTITY_OF
            <= index_of__path_node) {
        debug_abort("get_path_node_by__index_from__path, out of bounds: %d > %d",
                index_of__path_node,
                PATH_VECTORS_MAX_QUANTITY_OF);
        return 0;
    }
#endif
    return &p_path
        ->path_nodes__3i32F4[index_of__path_node];
}

static inline
bool is_path_routed_to__this_position(
        Path *p_path,
        Vector__3i32F4 destination__3i32F4) {
    return is_vectors_3i32F4__equal(*p_path
            ->p_path_node__newest__3i32F4,
            destination__3i32F4);
}

static inline
bool is_path__unusued(
        Path *p_path) {
    return 
        p_path->p_path_node__newest__3i32F4 == 0;
}

#endif
