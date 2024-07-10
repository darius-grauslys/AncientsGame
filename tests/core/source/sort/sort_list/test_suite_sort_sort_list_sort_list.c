#include <sort/sort_list/test_suite_sort_sort_list_sort_list.h>

#include <sort/sort_list/sort_list.c>
#include <sort/sort_list/sort_list_manager.h>

TEST_FUNCTION(get_length_of__sort_list) {
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
    munit_assert_ptr(
            p_sort_list,
            ==,
            &sort_list_manager.sort_lists[0]);

    munit_assert_int32(
            get_length_of__sort_list(
                p_sort_list),
            ==,
            16);
    return MUNIT_OK;
}


DEFINE_SUITE(sort_list, 
        INCLUDE_TEST__STATELESS(get_length_of__sort_list),
        END_TESTS)
