#include "defines_weak.h"
#include "numerics.h"
#include "serialization/serialization_header.h"
#include <inventory/item_stack.h>
#include <inventory/item.h>

void initialize_item_stack(
        Item_Stack *p_item_stack,
        Item item,
        Identifier__u16 identifier_for__item_stack,
        Quantity__u8 quantity_of__items,
        Quantity__u8 max_quantity_of__items) {
#ifndef NDEBUG
    if (!p_item_stack) {
        debug_abort("initialize_item_stack, p_item_stack is null.");
        return;
    }
#endif
    initialize_serialization_header(
            &p_item_stack->_serialization_header, 
            identifier_for__item_stack, 
            sizeof(Item_Stack));
    p_item_stack->item = item;
    p_item_stack->quantity_of__items =
        quantity_of__items;
    p_item_stack->max_quantity_of__items =
        max_quantity_of__items;
}

void initialize_item_stack_as__empty(
        Item_Stack *p_item_stack,
        Identifier__u32 identifier_for__item_stack__u32) {
#ifndef NDEBUG
    if (!p_item_stack) {
        debug_abort("initialize_item_stack__as_allocated, p_item_stack is null.");
        return;
    }
#endif
    initialize_serialization_header(
            &p_item_stack->_serialization_header, 
            identifier_for__item_stack__u32,
            sizeof(Item_Stack));
    p_item_stack->item = get_item__empty();
    p_item_stack->quantity_of__items = 0;
    p_item_stack->max_quantity_of__items = 0;
}

void set_item_stack(
        Item_Stack *p_item_stack,
        Item item,
        Quantity__u32 quantity_of__items,
        Quantity__u32 max_quantity_of__items) {
#ifndef NDEBUG
    if (!p_item_stack) {
        debug_abort("set_item_stack, p_item_stack is null.");
        return;
    }
#endif
    p_item_stack->item = item;
    p_item_stack->quantity_of__items =
        quantity_of__items;
    p_item_stack->max_quantity_of__items =
        max_quantity_of__items;
}

void merge_p_item_stacks(
        Item_Stack *p_item_stack__source,
        Item_Stack *p_item_stack__destination) {
#ifndef NDEBUG
    if (!p_item_stack__source) {
        debug_abort("merge_p_item_stacks, p_item_stack__source is null.");
        return;
    }
    if (!p_item_stack__destination) {
        debug_abort("merge_p_item_stacks, p_item_stack__destination is null.");
        return;
    }
#endif
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

    if (p_item_stack__source->quantity_of__items
            == 0) {
        initialize_item_stack_as__empty(
                p_item_stack__source,
                p_item_stack__source->_serialization_header.uuid);
    }
}

bool resolve_item_stack__merge_or_swap(
        Item_Stack *p_item_stack__source,
        Item_Stack *p_item_stack__destination) {
#ifndef NDEBUG
    if (!p_item_stack__source) {
        debug_abort("resolve_item_stack__merge_or_swap, p_item_stack__source is null.");
        return false;
    }
    if (!p_item_stack__destination) {
        debug_abort("resolve_item_stack__merge_or_swap, p_item_stack__destination is null.");
        return false;
    }
#endif
    if (is_p_item_stacks_the_same__item_kind(
                p_item_stack__source, 
                p_item_stack__destination)) {
        merge_p_item_stacks(
                p_item_stack__source, 
                p_item_stack__destination);
        return false;
    }
    // different item_kinds, perform a swap.
    Item_Stack p_item_stack__tmp =
            *p_item_stack__source;

    *p_item_stack__source =
        *p_item_stack__destination;
    p_item_stack__source
        ->_serialization_header.uuid =
        p_item_stack__tmp
        ._serialization_header.uuid;

    p_item_stack__tmp
        ._serialization_header.uuid =
        p_item_stack__destination
        ->_serialization_header.uuid;

    *p_item_stack__destination =
        p_item_stack__tmp;
    p_item_stack__destination
        ->_serialization_header.uuid =
        p_item_stack__destination
        ->_serialization_header.uuid;

    return true;
}

void remove_quantity_of_items_from__item_stack(
        Item_Stack *p_item_stack,
        Quantity__u8 quantity_of__items_to__remove) {
#ifndef NDEBUG
    if (!p_item_stack) {
        debug_abort("remove_quantity_of_items_from__item_stack, p_item_stack is null.");
        return;
    }
#endif
    p_item_stack->quantity_of__items =
        subtract_u8__no_overflow(
                p_item_stack->quantity_of__items, 
                quantity_of__items_to__remove);
}
