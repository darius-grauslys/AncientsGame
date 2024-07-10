#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <defines.h>

void initialize_sort_list_as__heap_sort(
        Sort_List *p_sort_list);

///
/// Swaps the root with the last leaf.
/// Be sure to invoke request_resorting_of__heap!
///
void rotate_heap(
        Sort_List *p_sort_list);

void request_resorting_of__heap(
        Sort_List *p_sort_list);

void request_resorting_of__heap_sort(
        Sort_List *p_sort_list);

bool m_sort__heapify__sort_list(
        Sort_List *p_sort_list);

bool m_sort__heap_sort__sort_list(
        Sort_List *p_sort_list);

static inline
bool is_sort_data__heapifed(
        Sort_Data *p_sort_data) {
    return p_sort_data->index_of__heapification ==
        INDEX__UNKNOWN__SORT_NODE;
}

static inline
bool is_heap__heapifed(
        Sort_List *p_sort_list) {
    return is_sort_data__heapifed(
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
bool is_heap_sort__sorted(
        Sort_List *p_sort_list) {
    return get_index_of__heap_sort_from__sort_data(
            &p_sort_list->sort_data) <= 1;
}

#endif
