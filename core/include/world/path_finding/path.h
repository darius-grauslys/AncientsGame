#ifndef PATH_H
#define PATH_H

#include "defines_weak.h"
#include "degree.h"
#include "vectors.h"
#include <defines.h>

void initialize_path(
        Path *p_path,
        Vector__3i32 starting_point__3i32,
        Vector__3i32 destination__3i32,
        Degree__u9 starting_direction__degree_u8,
        bool is_rotating__left_or__right);

static inline
void initialize_path_as__unusued(
        Path *p_path) {
    initialize_path(
            p_path, 
            VECTOR__3i32__OUT_OF_BOUNDS, 
            VECTOR__3i32__OUT_OF_BOUNDS, 
            0, 
            false);
}

void initialize_path_as__branching_path(
        Path *p_path,
        Path *p_path__branching_from,
        Vector__3i32 destination__3i32,
        Degree__u9 starting_direction__degree_u8);

///
/// Returns true if obstruction_indicent_stack is empty
/// AFTER popping.
///
bool pop_obstruction_incident_from__path(
        Path *p_path);

///
/// Returns true if the obstruction_indicent_stack is full
/// BEFORE pushing.
///
bool push_obstruction_incident_onto__path(
        Path *p_path,
        Degree__u9 angle_of__obstruction_incident);

/// Returns true if path
/// is not obstructed.
///
enum Path_Stepping_Result step_path(
        World *p_world,
        Path *p_path,
        Vector__3i32 destination);

static inline
bool is_path_stepping_result_of__this_kind(
        enum Path_Stepping_Result result,
        enum Path_Stepping_Result is_this_kind) {
    return result == is_this_kind;
}

static inline
bool is_progression_state_of__path_of__this_kind(
        Path *p_path,
        enum Path_Progression_State is_this_kind) {
    return p_path->state_of__path_progression == is_this_kind;
}

static inline
Vector__3i32 get_latest_path_node_in__path(
        Path *p_path) {
    return p_path->path_nodes__3i32[
        p_path->index_of__path_node];
}

static inline
Degree__u9 get_latest_obstruction_incident_in__path(
        Path *p_path) {
    return p_path->obstruction_indicent_stack[
        p_path->index_of__incident];
}

///
/// This makes the ray_current_vector__3i32F20
/// of the path the new path_node
/// (overwritting oldest if needed.)
///
/// It will then reset the path's ray
/// to this newest node with the given direction.
///
/// Returns true if fails to commit node to path.
///
bool commit_path_node_in__path(
        Path *p_path,
        Degree__u9 new_direction__degree_u8);

static inline
void commit_path_node_in__path_using__destination(
        Path *p_path,
        Vector__3i32 destination__3i32) {
    commit_path_node_in__path(
            p_path, 
            get_angle_between__vectors_3i32(
                vector_3i32F20_to__vector_3i32(
                    p_path->leading_ray_of__path
                        .ray_current_vector__3i32F20), 
                destination__3i32));
}

Signed_Quantity__i32 f_sort_heuristic__min_path(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two);

Signed_Quantity__i32 f_sort_heuristic__max_path(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two);

Signed_Quantity__i32 f_evaluation_heuristic__path(
        Sort_Node *p_sort_node);

static inline
void change_direction_of__path(
        Path *p_path,
        Degree__u9 new_direction__degree_u8) {
    p_path->leading_ray_of__path.angle_of__ray =
        new_direction__degree_u8;
}

static inline
void change_rotation_parity_of__path(
        Path *p_path,
        bool parity) {
    p_path->is_rotating__left_or__right = parity;
}

static inline
void toggle_rotation_parity_of__path(
        Path *p_path) {
    p_path->is_rotating__left_or__right =
        !p_path->is_rotating__left_or__right;
}

static inline
Vector__3i32 get_path_node_by__index_from__path(
        Path *p_path,
        Index__u8 index_of__path_node) {
#ifndef NDEBUG
    if (PATH_VECTORS_MAX_QUANTITY_OF
            <= index_of__path_node) {
        debug_abort("get_path_node_by__index_from__path, out of bounds: %d > %d",
                index_of__path_node,
                PATH_VECTORS_MAX_QUANTITY_OF);
        return VECTOR__3i32__OUT_OF_BOUNDS;
    }
#endif
    return p_path
        ->path_nodes__3i32[index_of__path_node];
}

static inline
Vector__3i32 *get_p_path_node_by__index_from__path(
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
        ->path_nodes__3i32[index_of__path_node];
}

bool is_path_routed_to__this_position(
        Path *p_path,
        Vector__3i32 destination__3i32);

static inline
bool is_path__unusued(
        Path *p_path) {
    return
        is_vectors_3i32__out_of_bounds(
                p_path->path_nodes__3i32[0]);
}

static inline
void set_progression_state_of__path(
        Path *p_path,
        enum Path_Progression_State path_progression_state) {
    p_path->state_of__path_progression =
        path_progression_state;
}

static inline
enum Path_Progression_State get_path_progression_state_of__path(
        Path *p_path) {
    return p_path->state_of__path_progression;
}

#endif
