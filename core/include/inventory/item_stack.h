#ifndef ITEM_STACK_H
#define ITEM_STACK_H

#include "defines_weak.h"
#include <defines.h>
#include <inventory/item.h>

void initialize_item_stack(
        Item_Stack *p_item_stack,
        Item item,
        Identifier__u16 identifier_for__item_stack,
        Quantity__u8 quantity_of__items,
        Quantity__u8 max_quantity_of__items);

void initialize_item_stack_as__empty(
        Item_Stack *p_item_stack,
        Identifier__u32 identifier_for__item_stack__u32);

void m_serialize__item_stack(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);

void m_deserialize__item_stack(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_item_stack__serializer);

void set_item_stack(
        Item_Stack *p_item_stack,
        Item item,
        Quantity__u32 quantity_of__items,
        Quantity__u32 max_quantity_of__items);

static inline
void copy_item_stack(
        Item_Stack *p_item_stack__source,
        Item_Stack *p_item_stack__destination) {
    set_item_stack(
            p_item_stack__destination, 
            p_item_stack__source->item, 
            p_item_stack__source->quantity_of__items, 
            p_item_stack__source->max_quantity_of__items);
}

///
/// If the Item_Stacks are for the same Item_Kind
/// then merge. Otherwise swap.
///
/// Returns true only if a swap occured.
///
bool resolve_item_stack__merge_or_swap(
        Item_Stack *p_item_stack__source,
        Item_Stack *p_item_stack__destination);

///
/// Returns the amount of items not removed.
///
Quantity__u32 remove_quantity_of_items_from__item_stack(
        Item_Stack *p_item_stack,
        Quantity__u8 quantity_of__items_to__remove);

static inline
bool is_p_item_stack__empty(
        Item_Stack *p_item_stack) {
    return 
        p_item_stack->quantity_of__items == 0
        || is_p_item__empty(&p_item_stack->item);
}

static inline
bool is_p_item_stack___full(
        Item_Stack *p_item_stack) {
    return 
        !is_p_item__empty(&p_item_stack->item)
        && p_item_stack->quantity_of__items
        < p_item_stack->max_quantity_of__items;
}

static inline
bool is_p_item_stack_of__this_item_kind(
        Item_Stack *p_item_stack,
        enum Item_Kind this_item_kind) {
    return p_item_stack->item.the_kind_of_item__this_item_is
        == this_item_kind;
}

static inline
bool is_p_item_stack__full(
        Item_Stack *p_item_stack) {
    return p_item_stack->quantity_of__items
        == p_item_stack->max_quantity_of__items;
}

static inline
bool is_p_item_stacks_the_same__item_kind(
        Item_Stack *p_item_stack__one,
        Item_Stack *p_item_stack__two) {
    return p_item_stack__one->item.the_kind_of_item__this_item_is
        == p_item_stack__two->item.the_kind_of_item__this_item_is;
}

static inline
Quantity__u32 get_quantity_of__items_in__item_stack(
        Item_Stack *p_item_stack) {
    return p_item_stack
        ->quantity_of__items;
}

static inline
Item_Kind get_item_kind_of__item_stack(
        Item_Stack *p_item_stack) {
    return get_item_kind_of__item(
            &p_item_stack->item);
}

#endif
