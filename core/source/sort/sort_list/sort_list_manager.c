#include "defines.h"
#include "defines_weak.h"
#include "sort/sort_list/sort_list.h"
#include "sort/sort_list/sort_node.h"
#include <sort/sort_list/sort_list_manager.h>

void initialize_sort_list_manager(
        Sort_List_Manager *p_sort_list_manager) {
    p_sort_list_manager
        ->quantity_of__allocated_sort_lists = 0;
    p_sort_list_manager
        ->quantity_of__allocated_sort_nodes = 0;
    for (Index__u8 index_of__sort_list = 0;
            index_of__sort_list < SORT_LIST__MAXIMUM_QUANTITY_OF;
            index_of__sort_list++) {
        Sort_List *p_sort_list =
                &p_sort_list_manager->sort_lists[index_of__sort_list];
        initialize_sort_list_as__empty(p_sort_list);
        set_sort_list_as__deallocated(p_sort_list);
    }
    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node < SORT_NODE__MAXIMUM_QUANTITY_OF;
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            &p_sort_list_manager->sort_nodes[index_of__sort_node];
        initialize_sort_node_as__empty(p_sort_node);
        set_sort_node_as__deallocated(p_sort_node);
    }
}

Sort_List *get_next_available__p_sort_list_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager) {
    for (Index__u8 index_of__sort_list = 0;
            index_of__sort_list < SORT_LIST__MAXIMUM_QUANTITY_OF;
            index_of__sort_list++) {
        Sort_List *p_sort_list =
            get_p_sort_list_by__index_in__sort_list_manager(
                    p_sort_list_manager, 
                    index_of__sort_list);
        if (is_sort_list__allocated(p_sort_list))
            continue;
        return p_sort_list;
    }
    return 0;
}

Sort_Node *allocate_sort_nodes_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager,
        Quantity__u32 quantity_of__nodes) {
    Index__u16 index_of__sort_node =
        p_sort_list_manager->quantity_of__allocated_sort_nodes;
    Index__u16 lookahead_index_of__sort_node = 
        p_sort_list_manager->quantity_of__allocated_sort_nodes;
    while (true) {
        Sort_Node *p_sort_node = 0;
find_available_node:
        for(;
                index_of__sort_node
                < SORT_NODE__MAXIMUM_QUANTITY_OF;
                index_of__sort_node++) {
            p_sort_node =
                get_p_sort_node_by__index_in__sort_list_manager(
                        p_sort_list_manager, 
                        index_of__sort_node);
            if (!is_sort_node__allocated(p_sort_node))
                break;
        }
        if (SORT_NODE__MAXIMUM_QUANTITY_OF
                <= index_of__sort_node)
            return 0;

        for (lookahead_index_of__sort_node =
                index_of__sort_node;
                lookahead_index_of__sort_node
                < SORT_NODE__MAXIMUM_QUANTITY_OF
                && lookahead_index_of__sort_node
                < (quantity_of__nodes + index_of__sort_node);
                lookahead_index_of__sort_node++) {
            Sort_Node *p_sort_node__lookahead =
                get_p_sort_node_by__index_in__sort_list_manager(
                        p_sort_list_manager, 
                        lookahead_index_of__sort_node);
            if (is_sort_node__allocated(p_sort_node__lookahead)) {
                index_of__sort_node = 
                    lookahead_index_of__sort_node;
                goto find_available_node;
            }
        }
        if (SORT_NODE__MAXIMUM_QUANTITY_OF
                <= lookahead_index_of__sort_node)
            return 0;

        for (Index__u16 allocation_index_of__sort_node = 0;
                allocation_index_of__sort_node
                < SORT_NODE__MAXIMUM_QUANTITY_OF
                && allocation_index_of__sort_node
                < quantity_of__nodes;
                allocation_index_of__sort_node++) {
            p_sort_node =
                get_p_sort_node_by__index_in__sort_list_manager(
                        p_sort_list_manager, 
                        index_of__sort_node
                        + allocation_index_of__sort_node);
            set_sort_node_as__allocated(p_sort_node);
        }
        break;
    }
    return get_p_sort_node_by__index_in__sort_list_manager(
            p_sort_list_manager, index_of__sort_node);
}

///
/// Returns nullptr if fails to allocate a
/// CONTIGUOUS list of nodes equal in size
/// to quantity_of__nodes.
///
Sort_List *allocate_sort_list_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager,
        Quantity__u32 quantity_of__nodes) {
    Quantity__u32 quantity_of__remaining_nodes =
        get_quantity_of__available_sort_nodes_in__sort_list_manager(
                p_sort_list_manager);
    if (!get_quantity_of__available_sort_lists_in__sort_list_manager(
                p_sort_list_manager)) {
        debug_error("allocate_sort_list_in__sort_list_manager, no available sort list entries.");
        return 0;
    }
    if (quantity_of__remaining_nodes
            < quantity_of__nodes) {
        debug_error("allocate_sort_list_in__sort_list_manager, node size exceeds available: %d > %d",
                quantity_of__nodes,
                quantity_of__remaining_nodes);
        return 0;
    }

    Sort_List *p_sort_list =
        get_next_available__p_sort_list_in__sort_list_manager(
                p_sort_list_manager);

#ifndef NDEBUG
    if (!p_sort_list) {
        debug_abort("allocate_sort_list_in__sort_list_manager, failed to get next available sort_list.");
        return 0;
    }
#endif

    p_sort_list->p_node_list =
        allocate_sort_nodes_in__sort_list_manager(
                p_sort_list_manager,
                quantity_of__nodes);

#ifndef NDEBUG
    if (!p_sort_list->p_node_list) {
        set_sort_list_as__deallocated(p_sort_list);
        debug_abort("allocate_sort_list_in__sort_list_manager, failed to get next contiguous sort_nodes list of size: %d.",
                quantity_of__nodes);
        return 0;
    }
#endif

    p_sort_list->size_of__p_node_list =
        quantity_of__nodes;
    p_sort_list_manager
        ->quantity_of__allocated_sort_lists++;
    p_sort_list_manager
        ->quantity_of__allocated_sort_nodes +=
        quantity_of__nodes;
    set_sort_list_as__allocated(p_sort_list);
    
    return p_sort_list;
}

void release_sort_nodes_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager,
        Sort_Node *p_sort_nodes,
        Quantity__u32 quantity_of__nodes) {
    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node < SORT_LIST__MAXIMUM_QUANTITY_OF
            && index_of__sort_node < quantity_of__nodes;
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_in__sort_list_manager(
                    p_sort_list_manager, index_of__sort_node);
        initialize_sort_node_as__empty(p_sort_node);
        set_sort_node_as__allocated(p_sort_node);
    }
}

void release_sort_list_in__sort_list_manager(
        Sort_List_Manager *p_sort_list_manager,
        Sort_List *p_sort_list) {
    release_sort_nodes_in__sort_list_manager(
            p_sort_list_manager, 
            p_sort_list->p_node_list, 
            p_sort_list->size_of__p_node_list);
    
    p_sort_list_manager
        ->quantity_of__allocated_sort_lists--;
    p_sort_list_manager
        ->quantity_of__allocated_sort_nodes +=
        p_sort_list->size_of__p_node_list;

    initialize_sort_list_as__empty(
            p_sort_list);
    set_sort_list_as__deallocated(p_sort_list);
}
