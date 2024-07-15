#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include <inventory/test_suite_inventory_inventory.h>

#include <inventory/inventory.c>

TEST_FUNCTION(initialize_inventory) {
    Inventory inventory;
    initialize_inventory(&inventory);

    for (Index__u32 index_of__item_stack = 0;
            index_of__item_stack
            < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item_stack++) {
        Item_Stack *p_item_stack =
            &inventory.items[index_of__item_stack];
        munit_assert_int(
                p_item_stack->identifier_for__item_stack,
                ==,
                IDENTIFIER__UNKNOWN__u16);
        munit_assert_int(
                p_item_stack->max_quantity_of__items, 
                ==, 
                0);
        munit_assert_int(
                p_item_stack->quantity_of__items, 
                ==, 
                0);
        munit_assert_int(
                p_item_stack->quantity_of__items, 
                ==, 
                0);
    }

    return MUNIT_OK;
}

TEST_FUNCTION(add_item_stack_to__inventory) {
    Inventory inventory;
    initialize_inventory(&inventory);
    return MUNIT_OK;
}

TEST_FUNCTION(copy_p_item_stack_to__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(move_p_item_stack_to__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(remove_p_item_stack_from__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(remove_item_stack_from__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(remove_this_many_item_kinds_from__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(remove_all_item_stacks_from__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(get_first_p_item_stack_of__this_item_kind_from__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(get_next_p_item_stack_of__this_item_kind_from__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(get_p_item_stack_from__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(get_total_weight_of__inventory) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(does_inventory_have_this_many_of__item_kind) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(does_inventory_have__available_item_stacks) {
    return MUNIT_SKIP;
}

DEFINE_SUITE(inventory, END_TESTS)
