#ifndef PATH_LIST_MANAGER_H
#define PATH_LIST_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_path_list_manager(
        Path_List_Manager *p_path_list_manager);

///
/// NOTE: This will allocate both a path_list
/// and a sort_list for that path_list.
///
/// If you already have a sort_list, instead
/// used allocate_path_list_in__path_list_manager
/// 
/// Returns nullptr if it failed to allocate
/// the sort_list or the path_list.
///
Path_List *allocate_and_initialize_path_list_with__managers(
        Path_List_Manager *p_path_list_manager,
        Sort_List_Manager *p_sort_list_manager,
        Vector__3i32 starting_point__3i32, 
        Vector__3i32 destination__3i32,
        i32F4 destination_squared_radius__i32F4);

///
/// NOTE: This will allocate ONLY a path_list.
/// Use this function if you already have a
/// sort_list for the allocating path_list.
///
/// Otherwise use allocate_path_list_with__managers.
///
/// Returns nullptr if it failed to allocate
/// a path_list.
///
Path_List *allocate_path_list_in__path_list_manager(
        Path_List_Manager *p_path_list_manager);

void release_path_list_in__path_list_manager(
        Path_List_Manager *p_path_list_manager,
        Sort_List_Manager *p_sort_list_manager,
        Path_List *p_path_list);

static inline
Path_List *get_p_path_list_by__index_from__path_list_manager(
        Path_List_Manager *p_path_list_manager,
        Index__u16 index_of__path_list) {
    return &p_path_list_manager
        ->path_lists[index_of__path_list];
}

#endif
