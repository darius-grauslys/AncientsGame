#include "defines.h"
#include "defines_weak.h"
#include "sort/sort_list/sort_node.h"
#include <sort/sort_list/sort_list.h>

void initialize_sort_list_as__allocated(
        Sort_List *p_sort_list,
        Sort_Node *p_node_list,
        f_Sort_Heuristic f_sort_heuristic,
        f_Evaluation_Heuristic f_evaluation_heuristic,
        Quantity__u32 size_of__sort_list) {
#ifndef NDEBUG
    if (size_of__sort_list >=
            SORT_NODE__MAXIMUM_QUANTITY_OF) {
        debug_abort("initialize_sort_list_as__allocated, size too large: %d > %d",
                size_of__sort_list,
                SORT_NODE__MAXIMUM_QUANTITY_OF);
        return;
    }
#endif

    p_sort_list->p_node_list =
        p_node_list;
    p_sort_list->f_sort_heuristic =
        f_sort_heuristic;
    p_sort_list->f_evaluation_heuristic =
        f_evaluation_heuristic;
    p_sort_list->size_of__p_node_list =
        size_of__sort_list;
    p_sort_list->is_allocated = true;

    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node
            < size_of__sort_list;
            index_of__sort_node++) {
        initialize_sort_node_as__empty(
                get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__sort_node));
    }
}

void initialize_sort_list_as__empty(
        Sort_List *p_sort_list) {
    p_sort_list->p_node_list = 0;
    p_sort_list->f_sort_heuristic = 0;
    p_sort_list->f_evaluation_heuristic = 0;
    p_sort_list->size_of__p_node_list = 0;
    p_sort_list->is_allocated = false;
}

Signed_Quantity__i32 f_heuristic__ptr_address_comparison(
        Sort_Node *p_node__one,
        Sort_Node *p_node__two) {
    return 
        (Signed_Quantity__i32)p_node__one->p_node_data
        - (Signed_Quantity__i32)p_node__two->p_node_data
        ;
}

///
/// O(lgN) time complexity.
///
void append_into__sort_list(
        Sort_List *p_sort_list,
        void *p_data) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("append_into__sort_list, p_sort_list is null.");
        return;
    }
#endif
    Quantity__u32 quantity_of__nodes =
        get_length_of__sort_list(p_sort_list);
    Index__u16 index = (Index__u16)quantity_of__nodes >> 1;
    Index__u16 previous = index;

    Sort_Node *p_current = 
        get_p_sort_node_by__index_from__sort_list(
                p_sort_list,
                index);

    Index__u16 pivot_left = 0;
    Index__u16 pivot_right = quantity_of__nodes;
    Sort_Node *p_next = p_current;
    do {
        previous = index;
        p_current = p_next;
        if (p_next->p_node_data) {
            pivot_left = index;
            index = (index + pivot_right) >> 1;
        } else {
            pivot_right = index;
            index = (index + pivot_left) >> 1;
        }
        p_next = 
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list,
                index
                );
    } while (p_current->p_node_data && !p_next->p_node_data);

    insert_into__sort_list(
            p_sort_list, 
            p_data, 
            previous);
}

///
/// O(1) time complexity.
///
void insert_into__sort_list(
        Sort_List *p_sort_list,
        void *p_data,
        Index__u16 index_of__sort_node) {
#ifndef NDEBUG
    if (index_of__sort_node >=
            get_length_of__sort_list(p_sort_list)) {
        debug_abort("insert_into__sort_list, out of bounds: %d",
                index_of__sort_node);
        return;
    }
#endif
    p_sort_list
        ->p_node_list[index_of__sort_node]
        .p_node_data = p_data;
}

///
/// O(N) time complexity.
///
void remove_from__sort_list(
        Sort_List *p_sort_list,
        void *p_data) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("remove_from__sort_list, p_sort_list is null.");
        return;
    }
#endif
    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node
            < get_length_of__sort_list(p_sort_list);
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, index_of__sort_node);
        if (p_sort_node->p_node_data
                == p_data) {
            p_sort_node->p_node_data = 0;
            return;
        }
    }
}

void run_sort(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("run_sort, p_sort_list is null.");
        return;
    }
    if (!p_sort_list->m_sort) {
        debug_abort("run_sort, p_sort_list->m_sort is null.");
        return;
    }
#endif
    while (!p_sort_list->m_sort(p_sort_list)) {}
}

bool run_sort_with__this_many_steps(
        Sort_List *p_sort_list,
        Quantity__u32 quantity_of__steps) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("run_sort_with__this_many_steps, p_sort_list is null.");
        return true;
    }
    if (!p_sort_list->m_sort) {
        debug_abort("run_sort_with__this_many_steps, p_sort_list->m_sort is null.");
        return true;
    }
#endif
    bool is_sorted = false;
    for (Quantity__u32 current_step = 0;
            current_step < quantity_of__steps;
            current_step++) {
        is_sorted =
            p_sort_list->m_sort(p_sort_list);    
        if (is_sorted)
            break;
    }
    return is_sorted;
}

///
/// Returns the index sort finished on.
/// Be sure to keep track of it!
///
bool run_sort_with__this_heurisitic_and__this_many_steps(
        Sort_List *p_sort_list,
        f_Sort_Heuristic f_this_sort_heuristic,
        Quantity__u32 quantity_of__steps) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("run_sort, p_sort_list is null.");
        return true;
    }
    if (!p_sort_list->m_sort) {
        debug_abort("run_sort, p_sort_list->m_sort is null.");
        return true;
    }
#endif
    f_Sort_Heuristic f_previous_heuristic =
        p_sort_list->f_sort_heuristic;
    p_sort_list->f_sort_heuristic =
        f_this_sort_heuristic;
    bool is_sorted =
        run_sort_with__this_many_steps(
                p_sort_list, 
                quantity_of__steps);
    p_sort_list->f_sort_heuristic =
        f_previous_heuristic;
    return is_sorted;
}

Index__u16 get_index_of__sort_node_in__sort_list(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("get_index_of__sort_node_in__sort_list, p_sort_list is null.");
        return true;
    }
    if (!p_sort_node) {
        debug_abort("get_index_of__sort_node_in__sort_list, p_sort_node is null.");
        return true;
    }
#endif
    Index__u16 index_of__node =
        p_sort_node
        - p_sort_list->p_node_list;
    return
        (index_of__node
            >= get_length_of__sort_list(p_sort_list))
        ? INDEX__UNKNOWN__SORT_NODE
        : index_of__node
        ;
}

Sort_Node *get_p_sort_node_by__index_from__sort_list(
        Sort_List *p_sort_list,
        Index__u16 index_of__sort_node) {
    if (index_of__sort_node >=
            get_length_of__sort_list(p_sort_list)) {
        return 0;
    }
    Sort_Node *p_sort_node =
        &p_sort_list->p_node_list[index_of__sort_node];
    return
        (is_sort_node__allocated(p_sort_node))
        ? p_sort_node
        : 0
        ;
}

///
/// Returns a pointer to a Sort_Node
/// that is determined by index_for__next_node.
///
/// Returns nullptr if there is no next node.
///
Sort_Node *get_next_p_sort_node_from__sort_list(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("get_next_p_sort_node_from__sort_list, p_sort_list is null.");
        return 0;
    }
    if (!p_sort_node) {
        debug_abort("get_next_p_sort_node_from__sort_list, p_sort_node is null.");
        return 0;
    }
#endif
    return get_p_sort_node_by__index_from__sort_list(
            p_sort_list,
            p_sort_node->index_for__next_node);
}
