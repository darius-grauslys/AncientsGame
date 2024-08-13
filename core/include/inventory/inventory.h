#ifndef INVENTORY_H
#define INVENTORY_H

#include "defines_weak.h"
#include <defines.h>

void initialize_inventory(
        Inventory *p_inventory,
        Identifier__u32 identifier_for__inventory);

void initialize_inventory_as__empty(
        Inventory *p_inventory);

void m_serialize__inventory(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);

void m_deserialize__inventory(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_inventory__serializer);

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

static inline
bool is_inventory_uuid_for__entity_or__container(
        Identifier__u32 uuid) {
    return uuid & UUID_BIT__INVENTORY_IS__ENTITY_OR__CONTAINER;
}

static inline
u16 get_inventory_container__z_from__uuid(
        Identifier__u32 uuid) {
    return (uuid & UUID_MASK__INVENTORY__CONTAINER__Z_AXIS)
        >> UUID_BIT_SHIFT__INVENTORY__CONTAINER__Z_AXIS
        ;
}

static inline
u16 get_inventory_container__x_from__uuid(
        Identifier__u32 uuid) {
    return (uuid & UUID_MASK__INVENTORY__CONTAINER__X_AXIS)
        >> UUID_BIT_SHIFT__INVENTORY__CONTAINER__X_AXIS
        ;
}

static inline
u16 get_inventory_container__y_from__uuid(
        Identifier__u32 uuid) {
    return (uuid & UUID_MASK__INVENTORY__CONTAINER__Y_AXIS);
}

static inline
void set_inventory_uuid_flag_for__entity(
        Identifier__u32 *p_uuid) {
    *p_uuid |= UUID_BIT__INVENTORY_IS__ENTITY_OR__CONTAINER;
}

static inline
void set_inventory_uuid_flag_for__container(
        Identifier__u32 *p_uuid) {
    *p_uuid &= ~UUID_BIT__INVENTORY_IS__ENTITY_OR__CONTAINER;
}

static inline
void set_inventory_container__z_in__uuid(
        Identifier__u32 *p_uuid,
        u16 z) {
    *p_uuid &= ~UUID_MASK__INVENTORY__CONTAINER__Z_AXIS;
    *p_uuid |= (UUID_MASK__INVENTORY__CONTAINER__Z_AXIS
        & (z << UUID_BIT_SHIFT__INVENTORY__CONTAINER__Z_AXIS)
        );
}

static inline
void set_inventory_container__x_in__uuid(
        Identifier__u32 *p_uuid,
        u16 x) {
    *p_uuid &= ~UUID_MASK__INVENTORY__CONTAINER__X_AXIS;
    *p_uuid |= (UUID_MASK__INVENTORY__CONTAINER__X_AXIS
        & (x << UUID_BIT_SHIFT__INVENTORY__CONTAINER__X_AXIS)
        );
}

static inline
void set_inventory_container__y_in__uuid(
        Identifier__u32 *p_uuid,
        u16 y) {
    *p_uuid &= ~UUID_MASK__INVENTORY__CONTAINER__Y_AXIS;
    *p_uuid |= (UUID_MASK__INVENTORY__CONTAINER__Y_AXIS & y);
}

static inline
void set_inventory_uuid__item_stack_index(
        Identifier__u32 *p_uuid,
        Index__u8 index_u6) {
    *p_uuid &= ~UUID_MASK__INVENTORY__ITEM_STACK;
    *p_uuid |= (UUID_MASK__INVENTORY__ITEM_STACK
            & (index_u6 << UUID_BIT_SHIFT__INVENTORY__ITEM_STACK)
            );
}

static inline
Identifier__u32 get_uuid_for__container(
        Tile_Vector__3i32 tile_vector__3i32) {
    Identifier__u32 uuid = 0;
    set_inventory_container__y_in__uuid(
            &uuid, 
            tile_vector__3i32.y__i32);
    set_inventory_container__x_in__uuid(
            &uuid, 
            tile_vector__3i32.x__i32);
    set_inventory_container__z_in__uuid(
            &uuid, 
            tile_vector__3i32.z__i32);
    set_inventory_uuid_flag_for__container(
            &uuid);
    return uuid;
}

bool does_inventory_have_this_many_of__item_kind(
        Inventory *p_inventory,
        enum Item_Kind the_kind_of__item,
        Quantity__u32 quantity_of__items);

bool does_inventory_have__available_item_stacks(
        Inventory *p_inventory);

#endif
