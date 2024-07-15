#include "defines_weak.h"
#include "numerics.h"
#include <inventory/item_stack.h>
#include <inventory/item.h>

void initialize_item_stack(
        Item_Stack *p_item_stack,
        Item item,
        Identifier__u16 identifier_for__item_stack,
        Quantity__u8 quantity_of__items,
        Quantity__u8 max_quantity_of__items) {
    p_item_stack->item = item;
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
            get_item__empty(), 
            IDENTIFIER__UNKNOWN__u16, 
            0, 
            0);
}

static inline
void poll_item_stack_for__vaildation(
        Item_Stack *p_item_stack) {
    if (p_item_stack->quantity_of__items == 0
            || is_p_item__empty(&p_item_stack->item)) {
        initialize_item_stack__as_empty(
                p_item_stack);
    }
}

void merge_p_item_stacks(
        Item_Stack *p_item_stack__source,
        Item_Stack *p_item_stack__destination) {
    Quantity__u16 quantity_of__total_items =
        p_item_stack__destination->quantity_of__items
        + p_item_stack__source->quantity_of__items
        ;
    Quantity__u8 quantity_of__items_overflowed =
        (quantity_of__total_items
         > p_item_stack__destination->max_quantity_of__items)
        ? quantity_of__total_items 
            - p_item_stack__destination->max_quantity_of__items
        : 0
        ;

    p_item_stack__destination->quantity_of__items =
        add_u8__clamped(
                p_item_stack__destination->quantity_of__items, 
                p_item_stack__source->quantity_of__items, 
                p_item_stack__destination->max_quantity_of__items);

    p_item_stack__source->quantity_of__items =
        subtract_u8__no_overflow(
                p_item_stack__source->quantity_of__items, 
                p_item_stack__source->quantity_of__items
                - quantity_of__items_overflowed);
    poll_item_stack_for__vaildation(
            p_item_stack__source);
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
    p_item_stack->quantity_of__items =
        subtract_u8__no_overflow(
                p_item_stack->quantity_of__items, 
                quantity_of__items_to__remove);
    poll_item_stack_for__vaildation(
            p_item_stack);
}
