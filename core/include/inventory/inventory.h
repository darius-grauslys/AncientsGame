#ifndef INVENTORY_H
#define INVENTORY_H

#include "defines_weak.h"
#include <defines.h>

void initialize_inventory(
        Inventory *p_inventory,
        Identifier__u32 identifier_for__inventory);

void initialize_inventory_as__empty(
        Inventory *p_inventory);

///
/// Calls initialize_item_stack to
/// an empty spot in inventory. Does nothing
/// if the inventory is already full.
///
Item_Stack *add_item_stack_to__inventory(
        Inventory *p_inventory,
        Item item,
        Quantity__u8 quantity_of__items,
        Quantity__u8 max_quantity_of__items);

void copy_p_item_stack_to__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__copy_origin);

void move_p_item_stack_to__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__move_origin);

void remove_p_item_stack_from__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack);

void remove_item_stack_from__inventory_using__identifier_for__item_stack(
        Inventory *p_inventory,
        Identifier__u16 identifier_for__item_stack);

void remove_this_many_item_kinds_from__inventory(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items_to__remove);

void remove_all_item_stacks_from__inventory(
        Inventory *p_inventory);

///
/// Attempt to find an item_stack with the
/// specified item_kind. Return nullptr on
/// failure.
///
Item_Stack *get_first_p_item_stack_of__this_item_kind_from__inventory(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item);

///
/// Attempt to find an item_stack with the
/// specified item_kind. Return nullptr on
/// failure.
///
Item_Stack *get_next_p_item_stack_of__this_item_kind_from__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__start_from,
        enum Item_Kind the_kind_of__item);

Item_Stack *get_p_item_stack_from__inventory_by__index(
        Inventory *p_inventory,
        Index__u8 index_of__item);

Item_Stack *get_p_item_stack_from__inventory(
        Inventory *p_inventory,
        Identifier__u32 identifier_for__item_stack);

i32F20 get_total_weight_of__inventory(
        Inventory *p_inventory);

static inline
bool does_inventory_have_this__item_kind(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item) {
    return (bool)get_first_p_item_stack_of__this_item_kind_from__inventory(
            p_inventory, the_kind_of__item);
}

bool does_inventory_have_this_many_of__item_kind(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items);

bool does_inventory_have__available_item_stacks(
        Inventory *p_inventory);

#endif
