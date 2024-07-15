#include "defines.h"
#include "defines_weak.h"
#include "inventory/item_stack.h"
#include <inventory/inventory.h>

void remove_all_unequiped_item_stacks_from__inventory(
        Inventory *p_inventory) {
    for (Index__u8 index_of__item=0;
            index_of__item < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item++) {
        initialize_item_stack__as_empty(
                &p_inventory->items[index_of__item]);
    }
}

void remove_all_equiped_item_stacks_from__inventory(
        Inventory *p_inventory) {
    initialize_item_stack__as_empty(
            &p_inventory->slot__armor);
    initialize_item_stack__as_empty(
            &p_inventory->slot__main_hand);
    initialize_item_stack__as_empty(
            &p_inventory->slot__off_hand);
    for (Index__u8 consumable_index=0;
            consumable_index < INVENTORY_CONSUMABLES_QUANTITY_OF;
            consumable_index++) {
        initialize_item_stack__as_empty(
                &p_inventory->slot__consumable[consumable_index]);
    }
}

void initialize_inventory(
        Inventory *p_inventory) {
    remove_all_equiped_item_stacks_from__inventory(
            p_inventory);
    remove_all_unequiped_item_stacks_from__inventory(
            p_inventory);
}

Item_Stack *get_p_item_stack_from__inventory_by__index(
        Inventory *p_inventory,
        Index__u8 index_of__item) {
    return &p_inventory->items[index_of__item];
}

Item_Stack *get_next_available_p_item_stack_from__inventory(
        Inventory *p_inventory) {
    for (Index__u8 index_of__item=0;
            index_of__item < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item++) {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, 
                    index_of__item);
        if (is_p_item_stack__empty(p_item_stack))
            return p_item_stack;
    }
    return 0;
}

///
/// Calls initialize_item_stack to
/// an empty spot in inventory. Does nothing
/// if the inventory is already full.
///
void add_item_stack_to__inventory(
        Inventory *p_inventory,
        Item item,
        Identifier__u16 identifier_for__item_stack,
        Quantity__u8 quantity_of__items,
        Quantity__u8 max_quantity_of__items) {
    Item_Stack *p_item_stack =
        get_next_available_p_item_stack_from__inventory(
                p_inventory);

    if (!p_item_stack) {
        debug_warning("add_item_stack_to__inventory, p_item_stack==0");
        debug_warning("is the inventory full?");
        return;
    }

    initialize_item_stack(
            p_item_stack,
            item,
            identifier_for__item_stack,
            quantity_of__items,
            max_quantity_of__items);
}

void copy_p_item_stack_to__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__copy_origin) {
    Item_Stack *p_item_stack =
        get_next_available_p_item_stack_from__inventory(
                p_inventory);

    if (!p_item_stack) {
        debug_warning("copy_p_item_stack_to__inventory, p_item_stack==0");
        debug_warning("is the inventory full?");
        return;
    }

    *p_item_stack =
        *p_item_stack__copy_origin;
}

void move_p_item_stack_to__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__move_origin) {
    copy_p_item_stack_to__inventory(
            p_inventory, 
            p_item_stack__move_origin);
    initialize_item_stack__as_empty(
            p_item_stack__move_origin);
}

void remove_p_item_stack_from__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack) {
    remove_this_many_item_kinds_from__inventory(
            p_inventory, 
            p_item_stack->item.the_kind_of_item__this_item_is, 
            p_item_stack->quantity_of__items);
}

void remove_item_stack_from__inventory_using__identifier_for__item_stack(
        Inventory *p_inventory,
        Identifier__u16 identifier_for__item_stack) {
    Item_Stack *p_item_stack =
        get_p_item_stack_from__inventory(
                p_inventory, 
                identifier_for__item_stack);
    initialize_item_stack__as_empty(p_item_stack);
}

void remove_this_many_item_kinds_from__inventory(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items_to__remove) {
    Item_Stack *p_item_stack =
        get_first_p_item_stack_of__this_item_kind_from__inventory(
                p_inventory, the_kind_of__item);
    if (!p_item_stack)
        return;
    do {
        Quantity__u8 quantity_of__items_in__item_stack =
            p_item_stack->quantity_of__items;
        remove_quantity_of_items_from__item_stack(
                p_item_stack, 
                quantity_of__items_to__remove);
        if (quantity_of__items_to__remove
                < quantity_of__items_in__item_stack) {
            return;
        }
        quantity_of__items_to__remove -=
            p_item_stack->quantity_of__items;
    } while ((p_item_stack =
                get_next_p_item_stack_of__this_item_kind_from__inventory(
                    p_inventory, 
                    p_item_stack, 
                    the_kind_of__item)));
}

///
/// Attempt to find an item_stack with the
/// specified item_kind. Return nullptr on
/// failure.
///
Item_Stack *get_first_p_item_stack_of__this_item_kind_from__inventory(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item) {
    Item_Stack *p_item_stack =
        get_p_item_stack_from__inventory_by__index(
                p_inventory, 
                0);
    if (p_item_stack->item.the_kind_of_item__this_item_is
            == the_kind_of__item)
        return p_item_stack;
    return get_next_p_item_stack_of__this_item_kind_from__inventory(
            p_inventory, 
            p_item_stack, 
            the_kind_of__item);
}

///
/// Attempt to find an item_stack with the
/// specified item_kind. Return nullptr on
/// failure.
///
Item_Stack *get_next_p_item_stack_of__this_item_kind_from__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__start_from,
        enum Item_Kind the_kind_of__item) {
    Index__u8 starting_index_of__items = 0;
    for (;
            starting_index_of__items < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            starting_index_of__items++) {
        if (get_p_item_stack_from__inventory_by__index(
                    p_inventory, 
                    starting_index_of__items)
                == p_item_stack__start_from)
            break;
    }
    if (starting_index_of__items >= INVENTORY_ITEM_MAXIMUM_QUANTITY_OF) {
        debug_error("get_next_available_p_item_stack_from__inventory, p_item_stack__start_from is not in present p_inventory.");
        return 0;
    }
    for (Index__u8 index_of__item=starting_index_of__items+1;
            index_of__item < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item++) {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, 
                    index_of__item);
        if (is_p_item_stack_of__this_item_kind(
                    p_item_stack,
                    the_kind_of__item))
            return p_item_stack;
    }
    return 0;
}

Item_Stack *get_p_item_stack_from__inventory(
        Inventory *p_inventory,
        Identifier__u16 identifier_for__item_stack) {
    for (Index__u8 index_of__item=0;
            index_of__item < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item++) {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, 
                    index_of__item);
        if (p_item_stack->identifier_for__item_stack
                == identifier_for__item_stack)
            return p_item_stack;
    }
    return 0;
}

i32F20 get_total_weight_of__inventory(
        Inventory *p_inventory) {
    i32F20 total_weight = 0;
    for (Index__u8 index_of__item=0;
            index_of__item < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item++) {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, 
                    index_of__item);

        total_weight += 
            p_item_stack->item.weight_per__item
            * p_item_stack->quantity_of__items;
    }

    return total_weight;
}

bool does_inventory_have_this_many_of__item_kind(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items) {
    Item_Stack *p_item_stack =
        get_first_p_item_stack_of__this_item_kind_from__inventory(
                p_inventory, the_kind_of__item);
    if (!p_item_stack)
        return quantity_of__items == 0;
    Quantity__u32 total_quantity = 0;
    do {
        total_quantity +=
            p_item_stack->quantity_of__items;
        if (total_quantity >= quantity_of__items)
            return true;
    } while ((p_item_stack =
                get_next_p_item_stack_of__this_item_kind_from__inventory(
                    p_inventory, 
                    p_item_stack, 
                    the_kind_of__item)));
    return false;
}

bool does_inventory_have__available_item_stacks(
        Inventory *p_inventory) {
    return !get_next_available_p_item_stack_from__inventory(p_inventory);
}
