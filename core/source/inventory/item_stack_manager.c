#include "defines.h"
#include "defines_weak.h"
#include <inventory/item_stack_manager.h>
#include <inventory/item_stack_allocation_specifier.h>

void initialize_item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager) {
    p_item_stack_manager->quantity_of__item_stack_allocation_specifier = 0;
    for (Index__u32 index_of__item_stack_allocation_specification = 0;
            index_of__item_stack_allocation_specification
            < ITEM_STACK_RECORD_MAX_QUANTITY_OF;
            index_of__item_stack_allocation_specification++) {
        Item_Stack_Allocation_Specifier *p_item_stack_allocation_specifier =
            get_p_item_stack_alloc_spec_by__index_from__item_stack_manager(
                    p_item_stack_manager, 
                    index_of__item_stack_allocation_specification);
        initialize_item_stack_allocation_specifier_as__empty(
                p_item_stack_allocation_specifier);
    }
}

Item_Stack_Allocation_Specifier 
*allocate_item_stack_allocation_specification_in__item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager,
        enum Item_Kind the_kind_of__item) {
    Item_Stack_Allocation_Specifier *p_item_stack_allocation_specifier =
        get_p_item_stack_alloc_spec_by__index_from__item_stack_manager(
                p_item_stack_manager, 
                the_kind_of__item);
    if (is_item_stack_allocation_specifier__allocated(
                p_item_stack_allocation_specifier)) {
        debug_abort("allocate_item_stack_allocation_specification_in__item_stack_manager, specification for the_kind_of__item: %d already allocated.");
        return 0;
    }
    set_item_stack_allocation_specifier_as__allocated(
            p_item_stack_allocation_specifier);
    p_item_stack_manager
        ->quantity_of__item_stack_allocation_specifier++;
    return p_item_stack_allocation_specifier;
}

void release_item_stack_allocation_specification_in__item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager,
        Item_Stack_Allocation_Specifier *p_item_stack_allocation_specifier) {
#ifndef NDBEUG
    if (p_item_stack_allocation_specifier
            - p_item_stack_manager
            ->item_stack_allocation_specifiers
            >= ITEM_STACK_RECORD_MAX_QUANTITY_OF) {
        debug_abort("release_item_stack_allocation_specification_in__item_stack_manager, p_item_stack_allocation_specifier: %p is not allocated with p_item_stack_manager: %p",
                p_item_stack_allocation_specifier,
                p_item_stack_manager);
        return;
    }
#endif
    set_item_stack_allocation_specifier_as__deallocated(
            p_item_stack_allocation_specifier);
    p_item_stack_manager
        ->quantity_of__item_stack_allocation_specifier--;
}

void initalize_item_stack_with__item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager,
        enum Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items_in__item_stack,
        Item_Stack *p_item_stack) {
    p_item_stack_manager->item_stack_allocation_specifiers
        [the_kind_of__item].f_item_stack__create(
                p_item_stack);
    p_item_stack->quantity_of__items =
        quantity_of__items_in__item_stack;
}
