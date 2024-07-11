#include "defines.h"
#include "defines_weak.h"
#include "degree.h"
#include "game.h"
#include "process/process.h"
#include "raycast/ray.h"
#include "sort/sort_list/heap_sort.h"
#include "sort/sort_list/sort_list.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "world/path_finding/path.h"
#include "world/path_finding/path_list.h"
#include "world/tile.h"
#include <world/path_finding/process/process_path_finding.h>

static inline
void rotate_path__left(
        Path *p_path) {
    p_path
        ->leading_ray_of__path
        .angle_of__ray =
        subtract_angles(
                p_path
                ->leading_ray_of__path
                .angle_of__ray, 
                1);
}

static inline
void rotate_path__right(
        Path *p_path) {
    p_path
        ->leading_ray_of__path
        .angle_of__ray =
        add_angles(
                p_path
                ->leading_ray_of__path
                .angle_of__ray, 
                1);
}

static inline
void rotate_path(
        Path *p_path) {
    if (p_path->is_rotating__left_or__right) {
        rotate_path__left(p_path);
    } else {
        rotate_path__right(p_path);
    }
}

static inline
bool is_path_ray__within_destination_radius(
        Path *p_path,
        Vector__3i32 destination__3i32,
        i32F4 destination_squared_radius__i32F4) {
    i32F4 distance_squared__i32F4 =
        get_distance_squared_of__vector_3i32F4(
                subtract_vectors__3i32F4(
                    vector_3i32_to__vector_3i32F4(
                        destination__3i32), 
                    vector_3i32F8_to__vector_3i32F4(
                        p_path
                        ->leading_ray_of__path
                        .ray_current_vector__3i32F8)))
        ;
    return distance_squared__i32F4 
        < destination_squared_radius__i32F4;
}

static inline
bool is_path_ray__blockage_commited(
        Path *p_path) {
    return
        is_vectors_3i32F8__equal(
                p_path
                    ->leading_ray_of__path
                    .ray_starting_vector__3i32F8,
                p_path
                    ->leading_ray_of__path
                    .ray_current_vector__3i32F8);
}

void m_process__path_find(
        Process *p_this_process,
        Game *p_game) {
    Path_List *p_path_list =
        get_p_path_list_from__process(p_this_process);
    Path *p_path__next =
        get_next_p_path_in__path_list(p_path_list);

    if (!p_path__next) {
        run_sort_with__this_many_steps(
                p_path_list->p_sort_list_for__paths, 
                p_this_process->quantity_of__steps_per_cycle);
        return;
    }

    LOOP_PROCESS(p_this_process) {
        if (is_path_ray__within_destination_radius(
                    p_path__next, 
                    p_path_list->destination__3i32, 
                    p_path_list->destination_squared_radius__i32F4)) {
            commit_path_node_in__path(
                    p_path__next, 
                    p_path__next
                    ->leading_ray_of__path
                    .angle_of__ray);
            complete_process(p_this_process);
            return;
        }

    }

    request_heapification_of__path_list(
            p_path_list);
}

void initialize_process_for__path_finding(
        Process *p_process,
        Path_List *p_path_list,
        Quantity__u32 quantity_of__steps_per_cycle) {
    initialize_process(
            p_process, 
            m_process__path_find, 
            0,
            p_path_list,
            quantity_of__steps_per_cycle);
    initialize_sort_list_as__heap(
            p_path_list->p_sort_list_for__paths);
    set_sort_list__sort_heuristic(
            p_path_list->p_sort_list_for__paths, 
            f_sort_heuristic__path);
}
