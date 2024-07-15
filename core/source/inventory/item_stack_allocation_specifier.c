#include <inventory/item_stack_allocation_specifier.h>

void initialize_item_stack_allocation_specifier(
        Item_Stack_Allocation_Specifier
            *p_item_stack_allocation_specifier,
        enum Item_Kind the_kind_of_item,
        f_Item_Stack__Create f_item_stack__create) {
    p_item_stack_allocation_specifier
        ->the_kind_of_item__this_specifier_is_for =
        the_kind_of_item;
    p_item_stack_allocation_specifier
        ->f_item_stack__create =
        f_item_stack__create;
}
