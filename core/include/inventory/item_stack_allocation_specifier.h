#ifndef ITEM_STACK_ALLOCATION_SPECIFIER_H
#define ITEM_STACK_ALLOCATION_SPECIFIER_H

#include <defines.h>

void initialize_item_stack_allocation_specifier(
        Item_Stack_Allocation_Specifier
            *p_item_stack_allocation_specifier,
        enum Item_Kind the_kind_of_item,
        f_Item_Stack__Create f_item_stack__create);

static inline
void initialize_item_stack_allocation_specifier_as__empty(
        Item_Stack_Allocation_Specifier
            *p_item_stack_allocation_specifier) {
    initialize_item_stack_allocation_specifier(
            p_item_stack_allocation_specifier,
            Item_Kind__None,
            0);
    p_item_stack_allocation_specifier
        ->is_item_stack_allocation_specifier__allocated =
        false;
}

static inline
bool is_item_stack_allocation_specifier__allocated(
        Item_Stack_Allocation_Specifier
            *p_item_stack_allocation_specifier) {
    return p_item_stack_allocation_specifier
        ->is_item_stack_allocation_specifier__allocated;
}

static inline
void set_item_stack_allocation_specifier_as__allocated(
        Item_Stack_Allocation_Specifier
            *p_item_stack_allocation_specifier) {
    p_item_stack_allocation_specifier
        ->is_item_stack_allocation_specifier__allocated =
        true;
}

static inline
void set_item_stack_allocation_specifier_as__deallocated(
        Item_Stack_Allocation_Specifier
            *p_item_stack_allocation_specifier) {
    p_item_stack_allocation_specifier
        ->is_item_stack_allocation_specifier__allocated =
        false;
}

#endif
