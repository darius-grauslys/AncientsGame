#ifndef SORT_LIST_H
#define SORT_LIST_H

#include "defines_weak.h"
#include "sort/sort_list/sort_node.h"
#include <defines.h>

void initialize_sort_list_as__allocated(
        Sort_List *p_sort_list,
        Sort_Node *p_node_list,
        f_Sort_Heuristic f_sort_heuristic,
        Quantity__u32 size_of__sort_list);

void initialize_sort_list_as__empty(
        Sort_List *p_sort_list);

///
/// Will have the entire sort list
/// point to the given range in
/// sequential order of nodes, regardless
/// of each node's index_for__next_node.
///
void point_sort_list__sort_nodes_to__this_range(
        Sort_List *p_sort_list,
        void *p_node_data__range,
        Quantity__u32 size_of__stride_in__bytes);

///
/// O(lgN) time complexity.
///
/// This will put the element at the back of the list.
/// If your heuristic doesn't want that, or can do a
/// better job, then be sure to create your own append 
/// function.
///
void append_into__sort_list(
        Sort_List *p_sort_list,
        void *p_data);

///
/// O(1) time complexity.
///
/// Inserts p_data into the list via the given index.
/// If your heuristic doesn't like this, then make your
/// own insert function.
///
void insert_into__sort_list(
        Sort_List *p_sort_list,
        void *p_data,
        Index__u16 index_of__sort_node);

///
/// O(N) time complexity.
///
/// This will linearly search for the corresponding p_data
/// pointer and remove the first found instance.
/// If your heuristic doesn't want that, or can do a better
/// job, be sure to create your own remove function.
///
void remove_from__sort_list(
        Sort_List *p_sort_list,
        void *p_data);

void run_sort(
        Sort_List *p_sort_list);

bool run_sort_with__this_many_steps(
        Sort_List *p_sort_list,
        Quantity__u32 quantity_of__steps);

bool run_sort_with__this_heurisitic_and__this_many_steps(
        Sort_List *p_sort_list,
        f_Sort_Heuristic f_this_sort_heuristic,
        Quantity__u32 quantity_of__steps);

Index__u16 get_index_of__sort_node_in__sort_list(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node);

Sort_Node *get_p_sort_node_by__index_from__sort_list(
        Sort_List *p_sort_list,
        Index__u16 index_of__sort_node);

///
/// Returns a pointer to a Sort_Node
/// that is determined by index_for__next_node.
///
/// Returns nullptr if there is no next node.
///
Sort_Node *get_next_p_sort_node_from__sort_list(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node);

static inline
Quantity__u32 get_length_of__sort_list(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("get_length_of__sort_list, p_sort_list is null.");
        return 0;
    }
#endif
    return p_sort_list->size_of__p_node_list;
}

static inline
bool run_sort__once(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("run_sort__once, p_sort_list is null.");
        return true;
    }
    if (!p_sort_list->m_sort) {
        debug_abort("run_sort__once, p_sort_list->m_sort is null.");
        return true;
    }
#endif
    p_sort_list->m_sort(p_sort_list);
}

static inline
void set_sort_list_as__allocated(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("set_sort_list_as__allocated, p_sort_list is null.");
        return;
    }
#endif
    p_sort_list->is_allocated = true;
}

static inline
void set_sort_list_as__deallocated(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("set_sort_list_as__deallocated, p_sort_list is null.");
        return;
    }
#endif
    p_sort_list->is_allocated = false;
}

static inline
Sort_Node *get_p_node_list_from__sort_list(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("get_p_node_list_from__sort_list, p_sort_list is null.");
        return 0;
    }
#endif
    return p_sort_list->p_node_list;
}

static inline
bool is_sort_list__allocated(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("is_sort_list__allocated, p_sort_list is null.");
        return 0;
    }
#endif
    return p_sort_list->is_allocated;
}

static inline
void set_sort_list__sort_heuristic(
        Sort_List *p_sort_list,
        f_Sort_Heuristic f_sort_heuristic) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("set_sort_list__sort_heuristic, p_sort_list is null.");
        return;
    }
#endif
    p_sort_list->f_sort_heuristic =
        f_sort_heuristic;
}

#endif
