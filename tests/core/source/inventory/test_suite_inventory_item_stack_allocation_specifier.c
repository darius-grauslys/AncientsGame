#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_stack_allocation_specifier.h"
#include "test_util.h"
#include <inventory/test_suite_inventory_item_stack_allocation_specifier.h>

#include <inventory/item_stack_allocation_specifier.c>

MunitResult assert_item_stack_allocation_specifier_as__empty(
        Item_Stack_Allocation_Specifier *p_item_stack_allocation_specifier) {
    munit_assert(
            p_item_stack_allocation_specifier
                ->the_kind_of_item__this_specifier_is_for
            == Item_Kind__None);
    munit_assert_ptr(
            p_item_stack_allocation_specifier
                ->f_item_stack__create, 
            ==, 
            0);

    return MUNIT_OK;
}

TEST_FUNCTION(initialize_item_stack_allocation_specifier__empty) {
    Item_Stack_Allocation_Specifier isas;
    initialize_item_stack_allocation_specifier(
            &isas, 
            Item_Kind__None, 
            0);

    assert_item_stack_allocation_specifier_as__empty(
            &isas);

    return MUNIT_OK;
}

void f_item_stack__create__test(Item_Stack *p_item_stack) {
    p_item_stack->max_quantity_of__items = 0;
    return;
}

TEST_FUNCTION(initialize_item_stack_allocation_specifier) {
    Item_Stack_Allocation_Specifier isas;
    initialize_item_stack_allocation_specifier(
            &isas, 
            Item_Kind__Arrow__Iron, 
            f_item_stack__create__test);

    munit_assert(
            isas.the_kind_of_item__this_specifier_is_for
            == Item_Kind__Arrow__Iron);
    munit_assert_ptr(
            isas.f_item_stack__create, 
            ==, 
            f_item_stack__create__test);

    return MUNIT_OK;
}

DEFINE_SUITE(item_stack_allocation_specifier, 
        INCLUDE_TEST__STATELESS
            (initialize_item_stack_allocation_specifier__empty),
        INCLUDE_TEST__STATELESS
            (initialize_item_stack_allocation_specifier),
        END_TESTS)
