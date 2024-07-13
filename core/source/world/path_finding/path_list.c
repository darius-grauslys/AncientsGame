#include "defines.h"
#include "defines_weak.h"
#include "degree.h"
#include "numerics.h"
#include "sort/sort_list/heap_sort.h"
#include "vectors.h"
#include <world/path_finding/path_list.h>
#include <sort/sort_list/sort_list.h>
#include <sort/sort_list/sort_node.h>
#include <world/path_finding/path.h>

void initialize_path_list(
        Path_List *p_path_list,
        Sort_List *p_min_heap,
        Sort_List *p_max_heap,
        Vector__3i32 starting_point__3i32,
        Vector__3i32 destination__3i32,
        i32F4 destination_squared_radius__i32F4) {
    Degree__u9 starting_direction__degree_u8 =
        get_angle_between__vectors_3i32(
                starting_point__3i32,
                destination__3i32);

    if (p_min_heap) {
        set_sort_list__sort_heuristic(
                p_min_heap, 
                f_sort_heuristic__min_path);
        point_sort_list__sort_nodes_to__this_range(
                p_min_heap, 
                p_path_list->paths, 
                sizeof(Path));
    }
    if (p_max_heap) {
        set_sort_list__sort_heuristic(
                p_max_heap, 
                f_sort_heuristic__max_path);
        point_sort_list__sort_nodes_to__this_range(
                p_max_heap, 
                p_path_list->paths, 
                sizeof(Path));
    }
    p_path_list->destination__3i32 =
        destination__3i32;
    p_path_list->p_min_heap_for__paths =
        p_min_heap;
    p_path_list->p_max_heap_for__paths =
        p_max_heap;
    p_path_list
        ->destination_squared_radius__i32F4 =
        destination_squared_radius__i32F4;

    initialize_path(
            get_p_path_by__index_in__path_list(
                p_path_list, 
                0),
            starting_point__3i32,
            destination__3i32,
            starting_direction__degree_u8,
            true);

    for (Index__u16 index_of__path = 1;
            index_of__path
            < PATH_MAX_QUANTITY_OF;
            index_of__path++) {
        Path *p_path =
            get_p_path_by__index_in__path_list(
                    p_path_list, 
                    index_of__path);
        initialize_path_as__unusued(
                p_path);
    }
}

bool is_path_list_heaps__not_heapified(
        Path_List *p_path_list) {
    return !is_heap__heapifed(
                p_path_list->p_min_heap_for__paths)
        || !is_heap__heapifed(
                    p_path_list->p_max_heap_for__paths);
}

void heapify_path_lists(
        Path_List *p_path_list,
        Quantity__u32 quantity_of__steps_per_cycle) {
    if (!is_heap__heapifed(p_path_list->p_min_heap_for__paths)) {
        run_sort_with__this_many_steps(
                p_path_list->p_min_heap_for__paths, 
                quantity_of__steps_per_cycle >> 1);
    }
    if (!is_heap__heapifed(p_path_list->p_max_heap_for__paths)) {
        run_sort_with__this_many_steps(
                p_path_list->p_max_heap_for__paths, 
                quantity_of__steps_per_cycle >> 1);
    }
}

Path *get_next_unused_path_in__path_list(
        Path_List *p_path_list) {
    for (Index__u8 index_of__path = 0;
            index_of__path
            < PATH_MAX_QUANTITY_OF;
            index_of__path++) {
        Path *p_path__candidate =
            get_p_path_by__index_in__path_list(
                    p_path_list, 
                    index_of__path);
        if (is_path__unusued(p_path__candidate))
            return p_path__candidate;
    }

    return 0;
}

Path *get_next_p_path_in__path_list(
        Path_List *p_path_list) {
    return 
        (Path*)p_path_list
        ->p_min_heap_for__paths
        ->p_node_list[0]
        .p_node_data
        ;
}

Path *get_worst_p_path_in__path_list(
        Path_List *p_path_list) {
    return 
        (Path*)p_path_list
        ->p_max_heap_for__paths
        ->p_node_list[0]
        .p_node_data
        ;
}

