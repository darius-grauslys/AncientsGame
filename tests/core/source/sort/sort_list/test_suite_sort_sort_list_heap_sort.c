#include "defines.h"
#include "defines_weak.h"
#include "munit.h"
#include "sort/sort_list/heap_sort.h"
#include "sort/sort_list/sort_list.h"
#include <sort/sort_list/test_suite_sort_sort_list_heap_sort.h>

#include <sort/sort_list/heap_sort.c>
#include <sort/sort_list/sort_list_manager.h>
#include <math.h>

TEST_FUNCTION(initialize_sort_list_as__heap_sort) {
    Sort_List_Manager sort_list_manager;
    initialize_sort_list_manager(
            &sort_list_manager);

    const Quantity__u8 quantity_of__nodes = 16;

    Sort_List *p_sort_list =
        allocate_sort_list_in__sort_list_manager(
                &sort_list_manager,
                quantity_of__nodes);

    munit_assert_ptr(
            p_sort_list,
            !=,
            0);

    initialize_sort_list_as__heap_sort(
            p_sort_list);

    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node < quantity_of__nodes;
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list,
                    index_of__sort_node);
        munit_assert_ptr(
                p_sort_node,
                !=,
                0);
        Index__u16 index_of__children =
            (index_of__sort_node << 1) + 1;
        if (quantity_of__nodes <=
                index_of__children)
            index_of__children =
                INDEX__UNKNOWN__SORT_NODE;
        munit_assert_int32(
                p_sort_node->index_for__next_node,
                ==,
                index_of__children);
    }

    return MUNIT_OK;
}

Signed_Index__i32 f_sort_heuristic__compare_p_data_addr(
        Sort_Node *p_sort_node__one,
        Sort_Node *p_sort_node__two) {
    munit_assert_ptr(
            p_sort_node__one,
            !=,
            0);
    munit_assert_ptr(
            p_sort_node__two,
            !=,
            0);
    int64_t value =
            (int64_t)p_sort_node__one->p_node_data
            - (int64_t)p_sort_node__two->p_node_data;
    return (value > 0) - (value < 0);
}

TEST_FUNCTION(m_sort__heapify__sort_list) {
    Sort_List_Manager sort_list_manager;
    initialize_sort_list_manager(
            &sort_list_manager);

    Quantity__u32 random_even_quantity_of__nodes =
        munit_rand_uint32()
        % (SORT_NODE__MAXIMUM_QUANTITY_OF - 8)
        + 8;

    if (random_even_quantity_of__nodes & 0b1)
        random_even_quantity_of__nodes--;

    Sort_List *p_sort_list =
        allocate_sort_list_in__sort_list_manager(
                &sort_list_manager, 
                random_even_quantity_of__nodes);

    munit_assert_ptr(
            p_sort_list,
            !=,
            0);

    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node
            < get_length_of__sort_list(p_sort_list);
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__sort_node);

        munit_assert_ptr(
                p_sort_node,
                !=,
                0);

        p_sort_node->p_node_data = (void*)(int64_t)munit_rand_uint32();
    }

    initialize_sort_list_as__heap_sort(
            p_sort_list);

    set_sort_list__sort_heuristic(
            p_sort_list, 
            f_sort_heuristic__compare_p_data_addr);

    while(!m_sort__heapify__sort_list(
            p_sort_list)) {}

    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node
            < get_length_of__sort_list(p_sort_list);
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__sort_node);

        munit_assert_ptr(
                p_sort_node,
                !=,
                0);

        if (does_heap_sort_node_have__left_child(
                    p_sort_node)) {
            Sort_Node *p_sort_node__left_child =
                get_p_sort_node_of__left_child(
                        p_sort_list,
                        p_sort_node);
            munit_assert_ptr(
                    p_sort_node__left_child,
                    !=,
                    0);
            munit_assert_ptr(
                    p_sort_node__left_child->p_node_data,
                    <=,
                    p_sort_node->p_node_data);
        }
        if (does_heap_sort_node_have__right_child(
                    p_sort_list,
                    p_sort_node)) {
            Sort_Node *p_sort_node__right_child =
                get_p_sort_node_of__right_child(
                        p_sort_list,
                        p_sort_node);
            munit_assert_ptr(
                    p_sort_node__right_child,
                    !=,
                    0);
            munit_assert_ptr(
                    p_sort_node__right_child->p_node_data,
                    <=,
                    p_sort_node->p_node_data);
        }
    }
    return MUNIT_OK;
}

TEST_FUNCTION(m_sort__heap_sort__sort_list) {
    Sort_List_Manager sort_list_manager;
    initialize_sort_list_manager(
            &sort_list_manager);

    Quantity__u32 random_even_quantity_of__nodes =
        munit_rand_uint32()
        % (SORT_NODE__MAXIMUM_QUANTITY_OF - 8)
        + 8;

    if (random_even_quantity_of__nodes & 0b1)
        random_even_quantity_of__nodes--;

    Sort_List *p_sort_list =
        allocate_sort_list_in__sort_list_manager(
                &sort_list_manager, 
                random_even_quantity_of__nodes);

    munit_assert_ptr(
            p_sort_list,
            !=,
            0);

    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node
            < get_length_of__sort_list(p_sort_list);
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__sort_node);

        munit_assert_ptr(
                p_sort_node,
                !=,
                0);

        p_sort_node->p_node_data = (void*)(int64_t)munit_rand_uint32();
    }

    initialize_sort_list_as__heap_sort(
            p_sort_list);

    set_sort_list__sort_heuristic(
            p_sort_list, 
            f_sort_heuristic__compare_p_data_addr);

    while(!m_sort__heapify__sort_list(
            p_sort_list)) {}

    while(!m_sort__heap_sort__sort_list(
            p_sort_list)) {}

    Sort_Node *p_sort_node__previous =
        get_p_sort_node_by__index_from__sort_list(
                p_sort_list, 
                0);
    for (Index__u16 index_of__sort_node = 1;
            index_of__sort_node
            < get_length_of__sort_list(p_sort_list);
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list, 
                    index_of__sort_node);

        munit_assert_ptr(
                p_sort_node->p_node_data, 
                >=, 
                p_sort_node__previous->p_node_data);
    }

    return MUNIT_OK;
}


DEFINE_SUITE(heap_sort,
        INCLUDE_TEST__STATELESS
            (initialize_sort_list_as__heap_sort),
        INCLUDE_TEST__STATELESS
            (m_sort__heapify__sort_list),
        INCLUDE_TEST__STATELESS
            (m_sort__heap_sort__sort_list),
        END_TESTS)
