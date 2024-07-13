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
#include "world/world.h"
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
void set_progression_state_of__path_and__commit_path_node(
        Path *p_path,
        enum Path_Progression_State path_progression_state) {
    if (commit_path_node_in__path(
            p_path, 
            p_path->leading_ray_of__path.angle_of__ray)) {
        set_progression_state_of__path(
                p_path, 
                Path_Progression_State__List_Exhausted);
        return;
    }
    set_progression_state_of__path(
            p_path, path_progression_state);
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
                    vector_3i32F20_to__vector_3i32F4(
                        p_path
                        ->leading_ray_of__path
                        .ray_current_vector__3i32F20)))
        ;
    return distance_squared__i32F4 
        < destination_squared_radius__i32F4;
}

static inline
bool is_lookahead_ray__colliding(
        Ray__3i32F20 *p_ray,
        World *p_world) {
    step_p_ray(p_ray);
    step_p_ray(p_ray);

    Tile *p_tile =
        get_p_tile_from__world_using__ray_3i32F20(
                p_world,
                p_ray);

    return !p_tile 
        || is_tile__unpassable(p_tile);
}

bool poll_path_for__completion(
        Path *p_path,
        Path_List *p_path_list) {
    if (is_path_ray__within_destination_radius(
                p_path, 
                p_path_list->destination__3i32, 
                p_path_list->destination_squared_radius__i32F4)) {
        set_progression_state_of__path(
                p_path, 
                Path_Progression_State__Routed);
        return true;
    }
    return false;
}

static inline
void resolve_path__obstruction(
        Path *p_path,
        Path_List *p_path_list,
        Game *p_game) {
    rotate_path(p_path);
    enum Path_Stepping_Result result_of__path_step =
        step_path(
                get_p_world_from__game(p_game), 
                p_path, 
                p_path_list->destination__3i32);

    switch (result_of__path_step) {
        case Path_Stepping_Result__Obstructed:
            return;
        case Path_Stepping_Result__Unobstructed:
            set_progression_state_of__path(
                    p_path, 
                    Path_Progression_State__Unobstructed);
            return;
    }
}

static inline
void resolve_path__unobstruction(
        Path *p_path,
        Path_List *p_path_list,
        Game *p_game) {
    Degree__u9 angle_to__destination =
        get_angle_between__vectors_3i32(
            get_latest_path_node_in__path(p_path), 
            p_path_list->destination__3i32);

    if (angle_to__destination
            == p_path->leading_ray_of__path.angle_of__ray) {
        set_progression_state_of__path_and__commit_path_node(
                p_path, 
                Path_Progression_State__Progressing);
        return;
    }

    set_progression_state_of__path_and__commit_path_node(
            p_path, 
            Path_Progression_State__Deviating);
    return;
}

static inline
void resolve_path__deviation(
        Path *p_path,
        Path_List *p_path_list,
        Game *p_game) {
    Ray__3i32F20 obstruction_ray =
        get_ray_as__extension(
                &p_path->leading_ray_of__path, 
                get_latest_obstruction_incident_in__path(p_path));

    if (is_lookahead_ray__colliding(
                &obstruction_ray, 
                get_p_world_from__game(p_game))) {
        enum Path_Stepping_Result result_of__path_step =
            step_path(
                    get_p_world_from__game(p_game), 
                    p_path, 
                    p_path_list->destination__3i32);

        switch (result_of__path_step) {
            case Path_Stepping_Result__Unobstructed:
                return;
            case Path_Stepping_Result__Obstructed:
                set_progression_state_of__path_and__commit_path_node(
                        p_path, 
                        Path_Progression_State__Obstructed);
                return;
        }
    }

    if (pop_obstruction_incident_from__path(
                p_path)) {
        set_progression_state_of__path_and__commit_path_node(
                p_path, 
                Path_Progression_State__Progressing);
        return;
    }
}

static inline
bool resolve_path__progression(
        Path *p_path,
        Path_List *p_path_list,
        Game *p_game) {
    if (poll_path_for__completion(
            p_path, 
            p_path_list)) {
        return false;
    }

    enum Path_Stepping_Result result_of__path_step =
        step_path(
                get_p_world_from__game(p_game), 
                p_path, 
                p_path_list->destination__3i32);

    switch (result_of__path_step) {
        case Path_Stepping_Result__Unobstructed:
            return false;
        case Path_Stepping_Result__Obstructed:
            set_progression_state_of__path_and__commit_path_node(
                    p_path, 
                    Path_Progression_State__Obstructed);
            if (is_progression_state_of__path_of__this_kind(
                        p_path, 
                        Path_Progression_State__List_Exhausted)) {
                return false;
            }
            
            Path *p_path__branching = 
                get_next_unused_path_in__path_list(
                        p_path_list);
            if (!p_path__branching) {
                p_path__branching = 
                    get_worst_p_path_in__path_list(
                            p_path_list);
#ifndef NDEBUG
                if (!p_path__branching) {
                    debug_abort("resolve_path__progression, get_worst_p_path_in__path_list returned null");
                }
#endif
            }

            initialize_path_as__branching_path(
                    p_path__branching, 
                    p_path, 
                    p_path_list->destination__3i32, 
                    p_path->leading_ray_of__path.angle_of__ray);

            return true;
    }
    return false;
}

void m_process__path_find(
        Process *p_this_process,
        Game *p_game) {
    Path_List *p_path_list =
        get_p_path_list_from__process(p_this_process);

    if (is_path_list_heaps__not_heapified(p_path_list)) {
        heapify_path_lists(
                p_path_list, 
                p_this_process->quantity_of__steps_per_cycle);
        return;
    }

    Path *p_path__next =
        get_next_p_path_in__path_list(p_path_list);

    LOOP_PROCESS(p_this_process) {
        enum Path_Progression_State path_progesssion_state__previous =
            get_path_progression_state_of__path(p_path__next);

        switch (path_progesssion_state__previous) {
            case Path_Progression_State__Obstructed:
                resolve_path__obstruction(
                        p_path__next, 
                        p_path_list,
                        p_game);
                break;
            case Path_Progression_State__Unobstructed:
                resolve_path__unobstruction(
                        p_path__next, 
                        p_path_list,
                        p_game);
                break;
            case Path_Progression_State__Deviating:
                resolve_path__deviation(
                        p_path__next, 
                        p_path_list,
                        p_game);
                break;
            case Path_Progression_State__Progressing:
                // if resolution effected p_max_heap
                if (resolve_path__progression(
                            p_path__next, 
                            p_path_list,
                            p_game)) {
                    // TODO: can we use the last process loops
                    // to sort instead of returning?
                    request_heapification_of__path_list(
                            p_path_list);
                    return;
                }
                break;
            case Path_Progression_State__Routed:
                complete_process(p_this_process);
                return;
            case Path_Progression_State__List_Exhausted:
                fail_process(p_this_process);
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
            p_path_list->p_min_heap_for__paths);
    set_sort_list__sort_heuristic(
            p_path_list->p_min_heap_for__paths, 
            f_sort_heuristic__min_path);

    initialize_sort_list_as__heap(
            p_path_list->p_max_heap_for__paths);
    set_sort_list__sort_heuristic(
            p_path_list->p_max_heap_for__paths, 
            f_sort_heuristic__max_path);
}
