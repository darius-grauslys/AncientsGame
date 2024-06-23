#include "defines_weak.h"
#include "numerics.h"
#include <inventory/item_stack.h>
#include <inventory/item.h>

void initialize_item_stack(
        Item_Stack *p_item_stack,
        Item item,
        i32F8 weight_of_each__item,
        Identifier__u16 identifier_for__item_stack,
        Quantity__u8 quantity_of__items,
        Quantity__u8 max_quantity_of__items) {
    p_item_stack->item = item;
    p_item_stack->weight_of_each__item =
        weight_of_each__item;
    p_item_stack->identifier_for__item_stack =
        identifier_for__item_stack;
    p_item_stack->quantity_of__items =
        quantity_of__items;
    p_item_stack->max_quantity_of__items =
        max_quantity_of__items;
}

void initialize_item_stack__as_empty(
        Item_Stack *p_item_stack) {
    initialize_item_stack(
            p_item_stack, 
            get_item__void(), 
            0, 
            IDENTIFIER__UNKNOWN__u16, 
            0, 
            0);
}

void merge_p_item_stacks(
        Item_Stack *p_item_stack__source,
        Item_Stack *p_item_stack__destination) {
    Quantity__u8 quantity_of_items__merged =
            p_item_stack__destination->max_quantity_of__items
            - p_item_stack__destination->quantity_of__items;

    p_item_stack__destination->quantity_of__items =
        add_u8__clamped(
                p_item_stack__destination->quantity_of__items, 
                p_item_stack__source->quantity_of__items, 
                p_item_stack__destination->max_quantity_of__items);

    p_item_stack__destination->quantity_of__items =
        subtract_u8__no_overflow(
                p_item_stack__destination->quantity_of__items, 
                quantity_of_items__merged);
}

void resolve_item_stack__merge_or_swap(
        Item_Stack *p_item_stack__source,
        Item_Stack *p_item_stack__destination) {
    if (is_p_item_stacks_the_same__item_kind(
                p_item_stack__source, 
                p_item_stack__destination)) {
        merge_p_item_stacks(
                p_item_stack__source, 
                p_item_stack__destination);
        return;
    }
    // different item_kinds, perform a swap.
    Item_Stack p_item_stack__tmp =
            *p_item_stack__source;
    *p_item_stack__source =
        *p_item_stack__destination;
    *p_item_stack__destination =
        p_item_stack__tmp;
}

void remove_quantity_of_items_from__item_stack(
        Item_Stack *p_item_stack,
        Quantity__u8 quantity_of__items_to__remove) {
    if (p_item_stack->quantity_of__items
            <= quantity_of__items_to__remove) {
        initialize_item_stack__as_empty(p_item_stack);
    } else {
        p_item_stack->quantity_of__items -=
            quantity_of__items_to__remove;
    }
}
