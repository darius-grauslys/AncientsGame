#include "defines.h"
#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_stack.h"
#include <inventory/test_suite_inventory_item_stack.h>
#include <inventory/test_suite_inventory_item.h>

#include <inventory/item_stack.c>

MunitResult assert_item_stack_is__empty(
        Item_Stack *p_item_stack) {
    munit_assert_int(
            p_item_stack->quantity_of__items,
            ==,
            0);
    assert_item_as__empty(&p_item_stack->item);
    return MUNIT_OK;
}

TEST_FUNCTION(initialize_item_stack) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(resolve_item_stack__merge_or_swap__should_merge) {
    Item_Stack item_stack__one, item_stack__two;
    Item item;
    initialize_item(
            &item, 
            0, 0, 0, 
            Item_Kind__Arrow__Iron, 
            0);
    initialize_item_stack(
            &item_stack__one, 
            item, 
            IDENTIFIER__UNKNOWN__u16, 
            munit_rand_int_range(1, 16), 32);
    initialize_item_stack(
            &item_stack__two, 
            item, 
            IDENTIFIER__UNKNOWN__u16, 
            32 - item_stack__one.quantity_of__items, 32);

    resolve_item_stack__merge_or_swap(
            &item_stack__one,
            &item_stack__two);

    assert_item_stack_is__empty(&item_stack__one);
    munit_assert_int(
            item_stack__two.quantity_of__items,
            ==,
            item_stack__two.max_quantity_of__items);
    munit_assert_int(
            item_stack__two.item.the_kind_of_item__this_item_is,
            ==,
            item.the_kind_of_item__this_item_is);

    return MUNIT_OK;
}

bool is_p_item_stacks__equal(
        Item_Stack *p_item_stack__one,
        Item_Stack *p_item_stack__two)  {
    bool is_equal = false;

    is_equal =
        is_p_items__equal(
                &p_item_stack__one->item, 
                &p_item_stack__two->item);
        ;
    if (!is_equal)
        return false;

    is_equal =
        p_item_stack__one->max_quantity_of__items
        ==
        p_item_stack__two->max_quantity_of__items
        ;
    if (!is_equal)
        return false;

    is_equal =
        p_item_stack__one->quantity_of__items
        ==
        p_item_stack__two->quantity_of__items
        ;
    if (!is_equal)
        return false;

    is_equal =
        p_item_stack__one->identifier_for__item_stack
        ==
        p_item_stack__two->identifier_for__item_stack
        ;
    if (!is_equal)
        return false;

    return is_equal;
}

TEST_FUNCTION(resolve_item_stack__merge_or_swap__should_swap) {
    Item_Stack item_stack__one, item_stack__two;
    Item_Stack item_stack__one_swapped, item_stack__two_swapped;
    Item item__one, item__two;
    initialize_item(
            &item__one, 
            0, 0, 0, 
            Item_Kind__Arrow__Iron, 
            0);
    initialize_item(
            &item__two, 
            0, 0, 0, 
            Item_Kind__Battleaxe__Iron, 
            0);

    Quantity__u32 quantity_of__items_in__item_stack_one =
        (munit_rand_uint32() + 1) % 32;
    initialize_item_stack(
            &item_stack__one, 
            item__one, 
            IDENTIFIER__UNKNOWN__u16, 
            quantity_of__items_in__item_stack_one, 32);

    Quantity__u32 quantity_of__items_in__item_stack_two =
        (munit_rand_uint32() + 1) % 32;
    initialize_item_stack(
            &item_stack__two, 
            item__two, 
            IDENTIFIER__UNKNOWN__u16, 
            quantity_of__items_in__item_stack_two, 32);

    item_stack__one_swapped = item_stack__one;
    item_stack__two_swapped = item_stack__two;

    resolve_item_stack__merge_or_swap(
            &item_stack__one_swapped,
            &item_stack__two_swapped);

    munit_assert(
            is_p_item_stacks__equal(
                &item_stack__one,
                &item_stack__two_swapped));
    munit_assert(
            is_p_item_stacks__equal(
                &item_stack__two,
                &item_stack__one_swapped));

    return MUNIT_OK;
}

TEST_FUNCTION(remove_quantity_of_items_from__item_stack) {
    Item_Stack item_stack__one;
    Item item;
    initialize_item(
            &item, 
            0, 0, 0, 
            Item_Kind__Arrow__Iron, 
            0);
    Quantity__u32 quantity_of__items_in__item_stack =
        munit_rand_int_range(1, 16);
    initialize_item_stack(
            &item_stack__one, 
            item, 
            IDENTIFIER__UNKNOWN__u16, 
            quantity_of__items_in__item_stack, 32);

    remove_quantity_of_items_from__item_stack(
            &item_stack__one,
            1);

    munit_assert_int(
            item_stack__one.quantity_of__items,
            ==,
            quantity_of__items_in__item_stack - 1);

    remove_quantity_of_items_from__item_stack(
            &item_stack__one,
            item_stack__one.quantity_of__items + 1);

    munit_assert_int(
            item_stack__one.quantity_of__items,
            ==,
            0);

    return MUNIT_OK;
}

DEFINE_SUITE(item_stack, 
        INCLUDE_TEST__STATELESS(initialize_item_stack),
        INCLUDE_TEST__STATELESS(resolve_item_stack__merge_or_swap__should_merge),
        INCLUDE_TEST__STATELESS(resolve_item_stack__merge_or_swap__should_swap),
        INCLUDE_TEST__STATELESS(remove_quantity_of_items_from__item_stack),
        END_TESTS)
