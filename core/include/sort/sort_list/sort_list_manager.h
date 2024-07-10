#ifndef SORT_LIST_MANAGER_H
#define SORT_LIST_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_sort_list_manager(
        Sort_List_Manager *p_sort_list_manager);

///
/// Returns nullptr if fails to allocate a
/// CONTIGUOUS list of nodes equal in size
/// to quantity_of__nodes.
///
Sort_List *allocate_sort_list_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager,
        Quantity__u32 quantity_of__nodes);

void release_sort_list_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager,
        Sort_List *p_sort_list);

static inline
Quantity__u32 get_quantity_of__allocated_sort_lists_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager) {
    return p_sort_list_manager->quantity_of__allocated_sort_lists;
}

static inline
Quantity__u32 get_quantity_of__allocated_sort_nodes_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager) {
    return p_sort_list_manager->quantity_of__allocated_sort_nodes;
}

static inline
Quantity__u32 get_quantity_of__available_sort_lists_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager) {
    return
        SORT_LIST__MAXIMUM_QUANTITY_OF
        - get_quantity_of__allocated_sort_nodes_in__sort_list_manager(
                p_sort_list_manager);
}

static inline
Quantity__u32 get_quantity_of__available_sort_nodes_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager) {
    return
        SORT_NODE__MAXIMUM_QUANTITY_OF
        - get_quantity_of__allocated_sort_lists_in__sort_list_manager(
                p_sort_list_manager);
}

static inline
Sort_List *get_p_sort_list_by__index_in__sort_list_manager(
        Sort_List_Manager  *p_sort_list_manager,
        Index__u8 index_of__sort_list) {
    return &p_sort_list_manager->sort_lists[index_of__sort_list];
}

static inline
Sort_Node *get_p_sort_node_by__index_in__sort_list_manager(
        Sort_List_Manager  *p_sort_list_manager,
        Index__u16 index_of__sort_node) {
    return &p_sort_list_manager->sort_nodes[index_of__sort_node];
}

#endif
