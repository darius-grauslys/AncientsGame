#include "defines.h"
#include "defines_weak.h"
#include "sort/sort_list/sort_list.h"
#include <sort/sort_list/heap_sort.h>

void initialize_sort_list_as__heap_sort(
        Sort_List *p_sort_list) {
    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node
            < get_length_of__sort_list(p_sort_list);
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__sort_node);
        p_sort_node->index_for__next_node =
            1 << index_of__sort_node;
        if (get_length_of__sort_list(p_sort_list)
                <= p_sort_node->index_for__next_node)
            p_sort_node->index_for__next_node =
                INDEX__UNKNOWN__SORT_NODE;
    }

    p_sort_list
        ->sort_data.index_of__heapification = 
        get_length_of__sort_list(p_sort_list)
        - 1;
}

static inline
Index__u16 get_heap_childern_index_of__sort_node(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
    ///
    /// heap heuristic sets
    /// p_sort_node->index_for__next_node
    /// to be the children of this node.
    ///
    return
        get_index_of__sort_node_in__sort_list(
                p_sort_list, 
                p_sort_node);
}

void swap_sort_nodes_in__heap(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two) {
    Sort_Node tmp_node =
        *p_sort_node__one;
    *p_sort_node__one =
        *p_sort_node__two;
    *p_sort_node__two =
        tmp_node;
}

void sift_down_in__heap(
        Sort_List *p_sort_list,
        Sort_Node *p_sort_node) {
    while (true) {
        Index__u16 index_of__children =
            get_heap_childern_index_of__sort_node(
                    p_sort_list, 
                    p_sort_node);
        
        if (INDEX__UNKNOWN__SORT_NODE
                == index_of__children)
            return;

        // if has right child
        Sort_Node *p_right_child =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__children + 1);
        Sort_Node *p_child =
            (p_right_child)
            ? p_right_child
            : get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__children);
        
        Signed_Quantity__i32
            comparison =
            p_sort_list->f_sort_heuristic(
                    p_sort_node,
                    p_child);
        if (comparison < 0) {
            swap_sort_nodes_in__heap(
                    p_sort_node,
                    p_child);
        } else {
            return;
        }
    }
}

static inline
Index__u16 get_index_of__heapification_from__sort_list(
        Sort_List *p_sort_list) {
    return p_sort_list->sort_data.index_of__heapification;
}

bool m_sort__heapify__sort_list(
        Sort_List *p_sort_list) {
    Index__u16 index_of__heapification =
        get_index_of__heapification_from__sort_list(
                p_sort_list);

    sift_down_in__heap(
            p_sort_list, 
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                index_of__heapification));

    if (index_of__heapification == 0) {
        p_sort_list->sort_data
            .index_of__heapification = INDEX__UNKNOWN__SORT_NODE;
        return true;
    }
    index_of__heapification >>= 1;
    p_sort_list->sort_data
        .index_of__heapification = index_of__heapification;
    return false;
}

static inline
bool is_sort_data__heapifying(
        Sort_Data *p_sort_data) {
    return p_sort_data->index_of__heapification !=
        INDEX__UNKNOWN__SORT_NODE;
}

static inline
bool is_sort_list__heapifying(
        Sort_List *p_sort_list) {
    return is_sort_data__heapifying(
            &p_sort_list->sort_data);
}

static inline
Index__u16 get_index_of__heap_sort_from__sort_data(
        Sort_Data *p_sort_data) {
    return p_sort_data->index_of__heap_sort;
}

static inline
Index__u16 get_index_of__heap_sort_from__sort_list(
        Sort_List *p_sort_list) {
    return get_index_of__heap_sort_from__sort_data(
            &p_sort_list->sort_data);
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
    if (is_sort_list__heapifying(p_sort_list)) {
        m_sort__heap_sort__sort_list(p_sort_list);
        return false;
    }

    Index__u16 index_of__heap_sort =
        get_index_of__heap_sort_from__sort_list(
                p_sort_list);
    if (index_of__heap_sort <= 1) {
        return true;
    }

    decrement_index_of__heap_sort_from__sort_list(
            p_sort_list);
    index_of__heap_sort--;
    Sort_Node *p_sort_node__root =
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                0);
    swap_sort_nodes_in__heap(
            p_sort_node__root,
            get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                index_of__heap_sort));
    sift_down_in__heap(
            p_sort_list, 
            p_sort_node__root
            );

    return false;
}
