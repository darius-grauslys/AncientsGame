#include "defines.h"
#include "defines_weak.h"
#include "sort/sort_list/sort_list.h"
#include <sort/sort_list/heap_sort.h>

static inline
Index__u16 get_heap_sort_index_of__parent_sort_node(
        Index__u16 index_of__node) {
    return (index_of__node-1) >> 1;
}

static inline
Index__u16 get_heap_sort_index_of__left_child_node(
        Sort_Node *p_sort_note) {
    return p_sort_note->index_for__next_node;
}

static inline
Index__u16 get_heap_sort_index_of__right_child_node(
        Sort_Node *p_sort_note) {
    return p_sort_note->index_for__next_node + 1;
}

static inline
bool does_heap_sort_node_have__left_child(
        Sort_Node *p_sort_node) {
    return p_sort_node->index_for__next_node
        != INDEX__UNKNOWN__SORT_NODE;
}

static inline
Sort_Node *get_p_sort_node_of__left_child(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
    return
        get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                get_heap_sort_index_of__left_child_node(
                    p_sort_node));
}

static inline
Sort_Node *get_p_sort_node_of__right_child(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
    return
        get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                get_heap_sort_index_of__right_child_node(
                    p_sort_node));
}

static inline
bool does_heap_sort_node_have__right_child(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
    return p_sort_node->index_for__next_node
        != INDEX__UNKNOWN__SORT_NODE
        && p_sort_node->index_for__next_node + 1
        < get_length_of__sort_list(p_sort_list);
}

static inline
void update_heap_sort_node__index_for__next_node(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
    Index__u16 index_of__sort_node =
        p_sort_node
        - p_sort_list->p_node_list
        ;
    p_sort_node->index_for__next_node =
        (index_of__sort_node << 1) + 1;
    if (get_length_of__sort_list(p_sort_list)
            <= p_sort_node->index_for__next_node)
        p_sort_node->index_for__next_node =
            INDEX__UNKNOWN__SORT_NODE;
}

void request_resorting_of__heap(
        Sort_List *p_sort_list) {
    p_sort_list
        ->sort_data.index_of__heapification = 
        get_heap_sort_index_of__parent_sort_node(
            get_length_of__sort_list(p_sort_list) - 1);
}

void request_resorting_of__heap_sort(
        Sort_List *p_sort_list) {
    p_sort_list
        ->sort_data.index_of__heap_sort =
        get_length_of__sort_list(p_sort_list);
}

void initialize_sort_list_as__heap(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("initialize_sort_list_as__heap_sort, p_sort_list is null.");
        return;
    }
    if (get_length_of__sort_list(p_sort_list) & 0b1) {
        debug_abort("initialize_sort_list_as__heap_sort, p_sort_list has odd length.");
        return;
    }
#endif
    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node
            < get_length_of__sort_list(p_sort_list);
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__sort_node);
        update_heap_sort_node__index_for__next_node(
                p_sort_list,
                p_sort_node);
    }

    p_sort_list->m_sort =
        m_sort__heapify__sort_list;

    request_resorting_of__heap(p_sort_list);
    request_resorting_of__heap_sort(p_sort_list);
}

void initialize_sort_list_as__heap_sort(
        Sort_List *p_sort_list) {
#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("initialize_sort_list_as__heap_sort, p_sort_list is null.");
        return;
    }
    if (get_length_of__sort_list(p_sort_list) & 0b1) {
        debug_abort("initialize_sort_list_as__heap_sort, p_sort_list has odd length.");
        return;
    }
#endif
    initialize_sort_list_as__heap(p_sort_list);
    p_sort_list->m_sort = m_sort__heap_sort__sort_list;
}

void swap_sort_nodes_in__heap(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two) {
    Sort_Node tmp_node =
        *p_sort_node__one;

    *p_sort_node__one =
        *p_sort_node__two;
    *p_sort_node__two =
        tmp_node;

    update_heap_sort_node__index_for__next_node(
            p_sort_list,
            p_sort_node__one);
    update_heap_sort_node__index_for__next_node(
            p_sort_list,
            p_sort_node__two);
}

void rotate_heap(
        Sort_List *p_sort_list) {
    swap_sort_nodes_in__heap(
            p_sort_list, 
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                0), 
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                get_length_of__sort_list(
                    p_sort_list) - 1));
}

static inline
Index__u16 get_index_of__heapification_from__sort_list(
        Sort_List *p_sort_list) {
    return p_sort_list->sort_data.index_of__heapification;
}

void sift_down_in__heap(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
    while (true) {
        Index__u16 index_of__children =
            get_heap_sort_index_of__left_child_node(
                    p_sort_node);
        
        if (get_index_of__heap_sort_from__sort_list(p_sort_list)
                <= index_of__children)
            return; //we are at a leaf node.

        Signed_Quantity__i32 comparison = 0;
        Sort_Node *p_right_child =
            get_p_sort_node_of__right_child(
                    p_sort_list,
                    p_sort_node);
        Sort_Node *p_left_child =
            get_p_sort_node_of__left_child(
                    p_sort_list, 
                    p_sort_node);
        Sort_Node *p_child =
            p_left_child;
        if (p_right_child 
                && index_of__children + 1 
                < get_index_of__heap_sort_from__sort_list(p_sort_list)) {
            comparison =
                p_sort_list->f_sort_heuristic(
                    p_left_child,
                    p_right_child);
            p_child = 
                (comparison < 0)
                ? p_right_child
                : p_left_child
                ;
        }
        comparison =
            p_sort_list->f_sort_heuristic(
                p_sort_node,
                p_child);
        
        if (comparison < 0) {
            swap_sort_nodes_in__heap(
                    p_sort_list,
                    p_sort_node,
                    p_child);
            p_sort_node = p_child;
        } else {
            return;
        }
    }
}

bool m_sort__heapify__sort_list(
        Sort_List *p_sort_list) {
    Index__u16 index_of__heapification =
        get_index_of__heapification_from__sort_list(
                p_sort_list);
    if (INDEX__UNKNOWN__SORT_NODE
            == index_of__heapification) {
        debug_warning("m_sort__heapify__sort_list, extraneous call.");
        return true;
    }

    sift_down_in__heap(
            p_sort_list, 
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                index_of__heapification));

    if (index_of__heapification == 0) {
        p_sort_list->sort_data
            .index_of__heapification = INDEX__UNKNOWN__SORT_NODE;

        sift_down_in__heap(
                p_sort_list, 
                get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__heapification));

        p_sort_list->sort_data.index_of__heap_sort =
            get_length_of__sort_list(p_sort_list);
        return true;
    }
    p_sort_list->sort_data
        .index_of__heapification--;
    return false;
}

static inline
void decrement_index_of__heap_sort_from__sort_data(
        Sort_Data *p_sort_data) {
    p_sort_data->index_of__heap_sort--;
}

static inline
void decrement_index_of__heap_sort_from__sort_list(
        Sort_List *p_sort_list) {
    decrement_index_of__heap_sort_from__sort_data(
            &p_sort_list->sort_data);
}

bool m_sort__heap_sort__sort_list(
        Sort_List *p_sort_list) {
    if (!is_heap__heapifed(p_sort_list)) {
        m_sort__heap_sort__sort_list(p_sort_list);
        return false;
    }

    if (is_heap_sort__sorted(p_sort_list)) {
        return true;
    }
    decrement_index_of__heap_sort_from__sort_list(
            p_sort_list);

    Sort_Node *p_sort_node__root =
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                0);
    swap_sort_nodes_in__heap(
            p_sort_list,
            p_sort_node__root,
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                get_index_of__heap_sort_from__sort_list(
                    p_sort_list)));
    sift_down_in__heap(
            p_sort_list, 
            p_sort_node__root
            );

    return false;
}
