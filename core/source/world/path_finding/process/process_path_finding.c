#include "defines.h"
#include "defines_weak.h"
#include "degree.h"
#include "game.h"
#include "process/process.h"
#include "sort/sort_list/heap_sort.h"
#include "sort/sort_list/sort_list.h"
#include "world/path_finding/path.h"
#include "world/path_finding/path_list.h"
#include <world/path_finding/process/process_path_finding.h>

static inline
void rotate_path_by__index_and_offset(
        Path_List *p_path_list,
        Path *p_path,
        Index__u8 index_offset) {
    Index__u8 index_of__path =
        get_index_of__p_path_in__path_list(
                p_path_list, 
                p_path) + index_offset;

    // if even index, rotate ray left, otherwise right.
    if (index_of__path & 0b1) {
        p_path
            ->leading_ray_of__path
            .angle_of__ray =
            subtract_angles(
                    p_path
                    ->leading_ray_of__path
                    .angle_of__ray, 
                    1);
    } else {
        p_path
            ->leading_ray_of__path
            .angle_of__ray =
            add_angles(
                    p_path
                    ->leading_ray_of__path
                    .angle_of__ray, 
                    1);
    }
}

void rotate_path_by__index(
        Path_List *p_path_list,
        Path *p_path) {
    rotate_path_by__index_and_offset(
            p_path_list, 
            p_path, 
            0);
}

void counter_rotate_path_by__index(
        Path_List *p_path_list,
        Path *p_path) {
    rotate_path_by__index_and_offset(
            p_path_list, 
            p_path, 
            1);
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

    if (is_path_routed_to__this_position(
                p_path__next, 
                p_path_list->destination__3i32F4)) {
        complete_process(p_this_process);
        return;
    }

    LOOP_PROCESS(p_this_process) {
        i32F4 old_squared_distance =
            p_path__next
            ->distance_squared__from_target__i32F4;

        bool is_obstructed =
            step_path(
                    get_p_world_from__game(p_game), 
                    p_path__next, 
                    p_path_list->destination__3i32F4);

        if (old_squared_distance
                < p_path__next
                ->distance_squared__from_target__i32F4) {
            counter_rotate_path_by__index(
                    p_path_list, 
                    p_path__next);
        }

        if (!is_obstructed)
            continue;

        bool is_branched =
            is_path__branched(p_path__next);

        if (!is_branched) {
            Path *p_path__branch =
                get_next_unused_path_in__path_list(
                        p_path_list);
            if (p_path__branch) {
                set_branching_path_of__this_path(
                        p_path__next, 
                        p_path__branch, 
                        p_path_list->destination__3i32F4, 
                        p_path__next
                            ->leading_ray_of__path
                            .angle_of__ray);
            }
        }

        rotate_path_by__index(
                p_path_list, 
                p_path__next);
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
}
