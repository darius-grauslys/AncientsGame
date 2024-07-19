#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_stack.h"
#include "test_util.h"
#include <inventory/test_suite_inventory_inventory_manager.h>

#include <inventory/inventory_manager.c>

TEST_FUNCTION(initialize_inventory_manager) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(allocate_p_inventory_in__inventory_manager) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(release_p_inventory_in__inventory_manager) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(resolve_s_inventory_ptr_to__inventory_manager) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(resolve_s_item_stack_ptr_to__inventory_manager) {
    return MUNIT_SKIP;
}

TEST_FUNCTION(resolve_s_item_stack_ptr_to__inventory_manager__post_merge) {
    Inventory_Manager inventory_manager;
    initialize_inventory_manager(
            &inventory_manager);
    Inventory *p_inventory =
        allocate_p_inventory_in__inventory_manager(
                &inventory_manager);

    Item item;
    initialize_item(
            &item, 
            0, 0, 0, 
            Item_Kind__Arrow__Iron, 
            0);
    Item_Stack *p_item_stack__one =
        add_item_stack_to__inventory(
                p_inventory, 
                item, 1, 2);
    Item_Stack *p_item_stack__two =
        add_item_stack_to__inventory(
                p_inventory, 
                item, 1, 2);

    Identifier__u32 uuid__one =
        p_item_stack__one->_serialization_header.uuid;
    Identifier__u32 uuid__two =
        p_item_stack__two->_serialization_header.uuid;

    resolve_item_stack__merge_or_swap(
            p_item_stack__one, 
            p_item_stack__two);

    Serialized_Field s_field__one;
    Serialized_Field s_field__two;

    initialize_serialized_field_as__unlinked(
            &s_field__one,
            uuid__one);
    initialize_serialized_field_as__unlinked(
            &s_field__two,
            uuid__two);

    munit_assert_true(
            resolve_s_item_stack_ptr_to__inventory_manager(
                &inventory_manager, 
                &s_field__one));
    munit_assert_true(
            is_p_item_stack__empty(
                s_field__one
                .p_serialized_field__item_stack)
            );
    munit_assert_true(
            resolve_s_item_stack_ptr_to__inventory_manager(
                &inventory_manager, 
                &s_field__two));
    munit_assert_false(
            is_p_item_stack__empty(
                s_field__two
                .p_serialized_field__item_stack)
            );

    return MUNIT_OK;
}

TEST_FUNCTION(resolve_s_item_stack_ptr_to__inventory_manager__post_swap) {
    Inventory_Manager inventory_manager;
    initialize_inventory_manager(
            &inventory_manager);
    Inventory *p_inventory =
        allocate_p_inventory_in__inventory_manager(
                &inventory_manager);

    Item item;
    initialize_item(
            &item, 
            0, 0, 0, 
            Item_Kind__Arrow__Iron, 
            0);
    Item_Stack *p_item_stack__one =
        add_item_stack_to__inventory(
                p_inventory, 
                item, 1, 2);

    initialize_item(
            &item, 
            0, 0, 0, 
            Item_Kind__Armor__Gold__Chaos, 
            0);
    Item_Stack *p_item_stack__two =
        add_item_stack_to__inventory(
                p_inventory, 
                item, 1, 2);

    Identifier__u32 uuid__one =
        p_item_stack__one->_serialization_header.uuid;
    Identifier__u32 uuid__two =
        p_item_stack__two->_serialization_header.uuid;

    resolve_item_stack__merge_or_swap(
            p_item_stack__one, 
            p_item_stack__two);

    Serialized_Field s_field__one;
    Serialized_Field s_field__two;

    initialize_serialized_field_as__unlinked(
            &s_field__one,
            uuid__one);
    initialize_serialized_field_as__unlinked(
            &s_field__two,
            uuid__two);

    munit_assert_true(
            resolve_s_item_stack_ptr_to__inventory_manager(
                &inventory_manager, 
                &s_field__one));
    munit_assert_false(
            is_p_item_stack__empty(
                s_field__one
                .p_serialized_field__item_stack)
            );
    munit_assert_true(
            resolve_s_item_stack_ptr_to__inventory_manager(
                &inventory_manager, 
                &s_field__two));
    munit_assert_false(
            is_p_item_stack__empty(
                s_field__two
                .p_serialized_field__item_stack)
            );

    return MUNIT_OK;
}



DEFINE_SUITE(inventory_manager, 
        INCLUDE_TEST__STATELESS
            (resolve_s_item_stack_ptr_to__inventory_manager__post_merge),
        INCLUDE_TEST__STATELESS
            (resolve_s_item_stack_ptr_to__inventory_manager__post_swap),
        END_TESTS)
