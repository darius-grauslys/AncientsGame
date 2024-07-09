#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <defines.h>

void initialize_sort_list_as__heap_sort(
        Sort_List *p_sort_list);

bool m_sort__heapify__sort_list(
        Sort_List *p_sort_list);

bool m_sort__heap_sort__sort_list(
        Sort_List *p_sort_list);

#endif
