#ifndef PATH_LIST_H
#define PATH_LIST_H

#include "defines_weak.h"
#include "sort/sort_list/heap_sort.h"
#include "sort/sort_list/sort_list.h"
#include "vectors.h"
#include <defines.h>

void initialize_path_list(
        Path_List *p_path_list,
        Sort_List *p_min_heap,
        Sort_List *p_max_heap,
        Vector__3i32 starting_point__3i32,
        Vector__3i32 destination__3i32,
        i32F4 destination_squared_radius__i32F4);

static inline
void initialize_path_list_as__deallocated(
        Path_List *p_path_list) {
    initialize_path_list(
            p_path_list, 
            0, 
            0,
            VECTOR__3i32__OUT_OF_BOUNDS, 
            VECTOR__3i32__OUT_OF_BOUNDS,
            0);
}

static inline
bool is_path_list__allocated(
        Path_List *p_path_list) {
    return (bool)p_path_list->p_min_heap_for__paths;
}

///
/// Primarily used for the path finding
/// algorithm. Will return null if
/// all paths are being utilized.
///
Path *get_next_unused_path_in__path_list(
        Path_List *p_path_list);

static inline
Index__u8 get_index_of__p_path_in__path_list(
        Path_List *p_path_list,
        Path *p_path) {
    return p_path - p_path_list->paths;
}

static inline
Path *get_p_path_by__index_in__path_list(
        Path_List *p_path_list,
        Index__u8 index_of__path) {
    return &p_path_list->paths[index_of__path];
}

///
/// WARNING: If this sort is apart of a
/// task-scheduled process, it may frequently
/// return null on this function! This is 
/// because the sort is not yet finished.
///
/// WARNING: Calling this function will NOT
/// make a resort request for the path_list.
/// 
/// If this function returns null, hold off on whatever
/// you're doing until the next game tick.
///
/// -DVERBOSE to see message logs of when this
/// invocation returns null as a result of
/// the path list not yet being sorted.
///
Path *get_next_p_path_in__path_list(
        Path_List *p_path_list);

Path *get_worst_p_path_in__path_list(
        Path_List *p_path_list);

bool is_path_list_heaps__not_heapified(
        Path_List *p_path_list);

void heapify_path_lists(
        Path_List *p_path_list,
        Quantity__u32 quantity_of__steps_per_cycle);

///
/// Invoke this if the path_list
/// is sorted via task-scheduling.
///
static inline
void request_heapification_of__path_list(
        Path_List *p_path_list) {
    request_resorting_of__heap(
            p_path_list
            ->p_min_heap_for__paths);
}

///
/// WARNING: If the path_list is long
/// this might take a bit on some platforms
/// and thereby cause lag. Consider leveraging
/// the task-scheduling system.
///
static inline
void resort_path_list(
        Path_List *p_path_list) {
    run_sort(p_path_list
            ->p_min_heap_for__paths);
}

#endif
