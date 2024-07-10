#include "defines.h"
#include "defines_weak.h"
#include "sort/sort_list/sort_list_manager.h"
#include "world/path_finding/path_list.h"
#include <world/path_finding/path_list_manager.h>

void initialize_path_list_manager(
        Path_List_Manager *p_path_list_manager) {
    p_path_list_manager->quantity_of__path_lists = 0;

    for (Index__u16 index_of__path_list = 0;
            index_of__path_list
            < PATH_LIST_MAX_QUANTITY_OF;
            index_of__path_list++) {
        Path_List *p_path_list =
            get_p_path_list_by__index_from__path_list_manager(
                    p_path_list_manager, 
                    index_of__path_list);

        initialize_path_list_as__deallocated(
                p_path_list);
    }
}

Path_List *allocate_and_initialize_path_list_with__managers(
        Path_List_Manager *p_path_list_manager,
        Sort_List_Manager *p_sort_list_manager,
        Vector__3i32F4 starting_point__3i32F4, 
        Vector__3i32F4 destination__3i32F4) {
    Path_List *p_path_list =
        allocate_path_list_in__path_list_manager(
                p_path_list_manager);

    Sort_List *p_sort_list =
        allocate_sort_list_in__sort_list_manager(
                p_sort_list_manager, 
                PATH_MAX_QUANTITY_OF);

    if (!p_sort_list) {
        debug_error("allocate_path_list_in__path_list_manager, failed to allocate p_sort_list.");
        release_path_list_in__path_list_manager(
                p_path_list_manager, 
                p_sort_list_manager,
                p_path_list);
        return 0;
    }

    initialize_path_list(
            p_path_list, 
            p_sort_list, 
            starting_point__3i32F4, 
            destination__3i32F4);

    return p_path_list;
}

Path_List *allocate_path_list_in__path_list_manager(
        Path_List_Manager *p_path_list_manager) {
    if (PATH_LIST_MAX_QUANTITY_OF <=
            p_path_list_manager->quantity_of__path_lists) {
        debug_error("allocate_path_list_in__path_list_manager, no space available.");
        return 0;
    }

    Path_List *p_path_list = 0;
    for (Index__u16 index_of__path_list = 0;
            index_of__path_list
            < PATH_LIST_MAX_QUANTITY_OF;
            index_of__path_list++) {
        Path_List *p_path_list__candidate =
            get_p_path_list_by__index_from__path_list_manager(
                    p_path_list_manager, 
                    index_of__path_list);
        
        if (!is_path_list__allocated(p_path_list__candidate)) {
            p_path_list =
                p_path_list__candidate;
            break;
        }
    }

#ifndef NDEBUG
    if (!p_path_list) {
        debug_error("allocate_path_list_in__path_list_manager, failed to allocate p_path_list.");
    }
#endif

    p_path_list_manager->quantity_of__path_lists++;
    return p_path_list;
}

void release_path_list_in__path_list_manager(
        Path_List_Manager *p_path_list_manager,
        Sort_List_Manager *p_sort_list_manager,
        Path_List *p_path_list) {
    if (p_path_list->p_sort_list_for__paths) {
        release_sort_list_in__sort_list_manager(
                p_sort_list_manager, 
                p_path_list
                ->p_sort_list_for__paths);
    }

    initialize_path_list_as__deallocated(
            p_path_list);
    p_path_list_manager->quantity_of__path_lists--;
}
