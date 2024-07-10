#ifndef SORT_NODE_H
#define SORT_NODE_H

#include <defines.h>

void initialize_sort_node_as__allocated(
        Sort_Node *p_sort_node,
        Signed_Quantity__i16 heuristic_value,
        Index__u16 index_for__next_node);

void initialize_sort_node_as__empty(
        Sort_Node *p_sort_node);

static inline
void set_sort_node_as__allocated(
        Sort_Node *p_sort_node) {
    p_sort_node->is_allocated = true;
}

static inline
void set_sort_node_as__deallocated(
        Sort_Node *p_sort_node) {
    p_sort_node->is_allocated = false;
}

static inline
void set_sort_node__p_node_data(
        Sort_Node *p_sort_node,
        void *p_node_data) {
    p_sort_node->p_node_data =
        p_node_data;
}

static inline
bool is_sort_node__allocated(
        Sort_Node *p_sort_node) {
    return p_sort_node->is_allocated;
}

#endif
