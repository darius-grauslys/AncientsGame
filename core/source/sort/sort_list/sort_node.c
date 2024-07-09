#include "defines.h"
#include <sort/sort_list/sort_node.h>

void initialize_sort_node_as__allocated(
        Sort_Node *p_sort_node,
        Signed_Quantity__i16 heuristic_value,
        Index__u16 index_for__next_node) {
    p_sort_node->heuristic_value =
        heuristic_value;
    p_sort_node->index_for__next_node =
        index_for__next_node;
    p_sort_node->is_allocated = true;
}

void initialize_sort_node_as__empty(
        Sort_Node *p_sort_node) {
    p_sort_node->heuristic_value = 0;
    p_sort_node->index_for__next_node =
        INDEX__UNKNOWN__SORT_NODE;
}
