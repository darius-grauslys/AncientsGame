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
        Sort_List *p_sort_list,
        Vector__3i32F4 starting_point__3i32F4,
        Vector__3i32F4 destination__3i32F4) {
    Degree__u8 starting_direction__degree_u8 =
        get_angle_between__vectors_3i32F4(
                &destination__3i32F4, 
                &starting_point__3i32F4);

    if (p_sort_list) {
        set_sort_list__sort_heuristic(
                p_sort_list, 
                f_sort_heuristic__path);
        point_sort_list__sort_nodes_to__this_range(
                p_sort_list, 
                p_path_list->paths, 
                sizeof(Path));
    }
    p_path_list->destination__3i32F4 =
        destination__3i32F4;
    p_path_list->p_sort_list_for__paths =
        p_sort_list;


    initialize_path(
            get_p_path_by__index_in__path_list(
                p_path_list, 
                0),
            starting_point__3i32F4,
            destination__3i32F4,
            starting_direction__degree_u8);

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

Path *get_next_unused_path_in__path_list(
        Path_List *p_path_list) {
    Path *p_path__unused = 0;

    for (Index__u8 index_of__path = 0;
            index_of__path
            < PATH_MAX_QUANTITY_OF;
            index_of__path++) {
        p_path__unused =
            get_p_path_by__index_in__path_list(
                    p_path_list, 
                    index_of__path);
        if (is_path__unusued(p_path__unused))
            return p_path__unused;
    }

    return p_path__unused;
}

Path *get_next_p_path_in__path_list(
        Path_List *p_path_list) {
    if (!is_heap_sort__sorted(
                p_path_list->p_sort_list_for__paths))
        return 0;

    return 
        (Path*)p_path_list
        ->p_sort_list_for__paths
        ->p_node_list[0]
        .p_node_data
        ;
}

