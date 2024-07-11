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
        Degree__u8 starting_direction__degree_u8,
        bool is_rotating__left_or__right);

void initialize_path_as__unusued(
        Path *p_path);

void initialize_path_as__branching_path(
        Path *p_path,
        Path *p_path__branching_from,
        Vector__3i32 destination__3i32,
        Degree__u8 starting_direction__degree_u8);

static inline
void set_branching_path_of__this_path(
        Path *p_this_path,
        Path *p_path_to_be_made_as__branching,
        Vector__3i32 destination_of__branching_path_3i32,
        Degree__u8 starting_direction_of__branching_path) {
    p_this_path->p_path__branching =
        p_path_to_be_made_as__branching;
    initialize_path_as__branching_path(
            p_path_to_be_made_as__branching, 
            p_this_path, 
            destination_of__branching_path_3i32, 
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
enum Path_Stepping_State step_path(
        World *p_world,
        Path *p_path,
        Vector__3i32 destination);

static inline
bool is_path_stepping_result__progressing(
        enum Path_Stepping_State path_stepping_result) {
    return Path_Stepping_State__Progressing
        == path_stepping_result;
}

static inline
bool is_path_stepping_result__obstructed(
        enum Path_Stepping_State path_stepping_result) {
    return Path_Stepping_State__Obstructed
        == path_stepping_result;
}

static inline
bool is_path_stepping_result__deviating(
        enum Path_Stepping_State path_stepping_result) {
    return Path_Stepping_State__Deviating
        == path_stepping_result;
}

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

static inline
void commit_path_node_in__path_using__destination(
        Path *p_path,
        Vector__3i32 destination__3i32) {
    commit_path_node_in__path(
            p_path, 
            get_angle_between__vectors_3i32F4(
                vector_3i32F8_to__vector_3i32F4(
                    p_path->leading_ray_of__path
                        .ray_current_vector__3i32F8), 
                vector_3i32_to__vector_3i32F4(
                    destination__3i32)));
}

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

static inline
bool is_path_routed_to__this_position(
        Path *p_path,
        Vector__3i32 destination__3i32) {
    return is_vectors_3i32__equal(*p_path
            ->p_path_node__newest__3i32,
            destination__3i32);
}

static inline
bool is_path__unusued(
        Path *p_path) {
    return 
        p_path->p_path_node__newest__3i32 == 0;
}

static inline
void set_state_of__path(
        Path *p_path,
        enum Path_Stepping_State path_stepping_state) {
    p_path->state_of__path =
        path_stepping_state;
}

#endif
