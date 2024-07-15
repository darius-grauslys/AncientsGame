#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_stack_manager.h"
#include <inventory/test_suite_inventory_item_stack_manager.h>
#include <inventory/test_suite_inventory_item_stack_allocation_specifier.h>
#include <inventory/test_suite_inventory_item.h>

#include <inventory/item_stack_manager.c>

TEST_FUNCTION(initialize_item_stack_manager) {
    Item_Stack_Manager item_stack_manager;
    initialize_item_stack_manager(&item_stack_manager);

    munit_assert_int(
            item_stack_manager.quantity_of__item_stack_allocation_specifier,
            ==,
            0);

    for (Index__u32 index_of__item_stack_allocation_specification = 0;
            index_of__item_stack_allocation_specification
            < ITEM_STACK_RECORD_MAX_QUANTITY_OF;
            index_of__item_stack_allocation_specification++) {
        Item_Stack_Allocation_Specifier *p_isas =
            get_p_item_stack_alloc_spec_by__index_from__item_stack_manager(
                    &item_stack_manager,
                    index_of__item_stack_allocation_specification);
        assert_item_stack_allocation_specifier_as__empty(
                p_isas);
    }

    return MUNIT_OK;
}

TEST_FUNCTION
(allocate_item_stack_allocation_specification_in__item_stack_manager) {
    Item_Stack_Manager item_stack_manager;
    initialize_item_stack_manager(&item_stack_manager);

    Item_Stack_Allocation_Specifier *p_isas =
        allocate_item_stack_allocation_specification_in__item_stack_manager(
                &item_stack_manager,
                Item_Kind__Arrow__Iron);

    munit_assert_int(
            item_stack_manager
            .quantity_of__item_stack_allocation_specifier,
            ==,
            1);
    munit_assert_ptr(
            p_isas,
            !=,
            0);
    munit_assert_int(
            p_isas
            - item_stack_manager
                .item_stack_allocation_specifiers,
            <,
            ITEM_STACK_RECORD_MAX_QUANTITY_OF);

    return MUNIT_OK;
}

TEST_FUNCTION
(release_item_stack_allocation_specification_in__item_stack_manager){
    Item_Stack_Manager item_stack_manager;
    initialize_item_stack_manager(&item_stack_manager);

    Item_Stack_Allocation_Specifier *p_isas =
        allocate_item_stack_allocation_specification_in__item_stack_manager(
                &item_stack_manager,
                Item_Kind__Arrow__Iron);
    release_item_stack_allocation_specification_in__item_stack_manager(
            &item_stack_manager, 
            p_isas);

    munit_assert_int(
            item_stack_manager
            .quantity_of__item_stack_allocation_specifier,
            ==,
            0);

    return MUNIT_OK;
}

TEST_FUNCTION(initalize_item_stack_with__item_stack_manager) {
    return MUNIT_SKIP;
}

DEFINE_SUITE(item_stack_manager,
        INCLUDE_TEST__STATELESS(initialize_item_stack_manager),
        INCLUDE_TEST__STATELESS(allocate_item_stack_allocation_specification_in__item_stack_manager),
        INCLUDE_TEST__STATELESS(release_item_stack_allocation_specification_in__item_stack_manager),
        INCLUDE_TEST__STATELESS(initalize_item_stack_with__item_stack_manager),
        END_TESTS)
