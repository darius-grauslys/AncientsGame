#include <alloca.h>
#include <sort/sort_list/test_suite_sort_sort_list_sort_list_manager.h>

#include <sort/sort_list/sort_list_manager.c>

TEST_FUNCTION(get_next_available__p_sort_list_in__sort_list_manager) {
    Sort_List_Manager sort_list_manager;
    initialize_sort_list_manager(
            &sort_list_manager);

    Sort_List *p_sort_list =
        get_next_available__p_sort_list_in__sort_list_manager(&sort_list_manager);

    munit_assert_ptr(
            p_sort_list,
            ==,
            &sort_list_manager.sort_lists[0]);
    return MUNIT_OK;
}

TEST_FUNCTION(allocate_sort_list_in__sort_list_manager) {
    Sort_List_Manager sort_list_manager;
    initialize_sort_list_manager(
            &sort_list_manager);
    Sort_List *p_sort_list =
        allocate_sort_list_in__sort_list_manager(
                &sort_list_manager,
                16);

    munit_assert_ptr(
            p_sort_list,
            !=,
            0);

    munit_assert_int32(
            p_sort_list->size_of__p_node_list,
            ==,
            16);

    for (Index__u16 index_of__sort_node = 0;
            index_of__sort_node < 16;
            index_of__sort_node++) {
        Sort_Node *p_sort_node =
            get_p_sort_node_by__index_from__sort_list(
                    p_sort_list,
                    index_of__sort_node);
        munit_assert_ptr(
                p_sort_node,
                !=,
                0);
    }
    return MUNIT_OK;
}

TEST_FUNCTION(get_quantity_of__available_sort_lists_in__sort_list_manager__after_initialization) {
    Sort_List_Manager sort_list_manager;
    initialize_sort_list_manager(
            &sort_list_manager);
    Quantity__u32 quantity_of__remaining_lists =
        get_quantity_of__available_sort_lists_in__sort_list_manager(
                    &sort_list_manager);
    
    munit_assert_int32(
            SORT_LIST__MAXIMUM_QUANTITY_OF,
            ==,
            quantity_of__remaining_lists);
    return MUNIT_OK;
}

TEST_FUNCTION(get_quantity_of__available_sort_nodes_in__sort_list_manager__after_initialization) {
    Sort_List_Manager sort_list_manager;
    initialize_sort_list_manager(
            &sort_list_manager);
    Quantity__u32 quantity_of__remaining_nodes =
        get_quantity_of__available_sort_nodes_in__sort_list_manager(
                    &sort_list_manager);
    
    munit_assert_int32(
            SORT_NODE__MAXIMUM_QUANTITY_OF,
            ==,
            quantity_of__remaining_nodes);
    return MUNIT_OK;
}

DEFINE_SUITE(sort_list_manager, 
        INCLUDE_TEST__STATELESS(get_next_available__p_sort_list_in__sort_list_manager),
        INCLUDE_TEST__STATELESS(allocate_sort_list_in__sort_list_manager),
        INCLUDE_TEST__STATELESS(get_quantity_of__available_sort_nodes_in__sort_list_manager__after_initialization),
        INCLUDE_TEST__STATELESS(get_quantity_of__available_sort_lists_in__sort_list_manager__after_initialization),
        END_TESTS)
