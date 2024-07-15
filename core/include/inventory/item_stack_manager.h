#ifndef ITEM_STACK_MANAGER_H
#define ITEM_STACK_MANAGER_H

#include "defines.h"
#include "defines_weak.h"
void initialize_item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager);

Item_Stack_Allocation_Specifier 
*allocate_item_stack_allocation_specification_in__item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager,
        enum Item_Kind the_kind_of__item);

void release_item_stack_allocation_specification_in__item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager,
        Item_Stack_Allocation_Specifier *p_item_stack_allocation_specifier);

void initalize_item_stack_with__item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager,
        enum Item_Kind the_kind_of_item,
        Quantity__u32 quantity_of__items_in__item_stack,
        Item_Stack *p_item_stack);

Item_Stack_Allocation_Specifier 
*get_p_item_stack_alloc_spec_by__index_from__item_stack_manager(
        Item_Stack_Manager *p_item_stack_manager,
        Index__u32 index_of__item_stack_allocation_specification) {
#ifndef NDEBUG
    if (index_of__item_stack_allocation_specification
            >= ITEM_STACK_RECORD_MAX_QUANTITY_OF) {
        debug_abort("get_p_item_stack_alloc_spec_by__index_from__item_stack_manager, index out of bounds: %d", index_of__item_stack_allocation_specification);
        return 0;
    }
#endif
    return &p_item_stack_manager
        ->item_stack_allocation_specifiers
        [index_of__item_stack_allocation_specification];
}

#endif
