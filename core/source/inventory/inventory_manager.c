#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include "numerics.h"
#include "platform_defines.h"
#include "random.h"
#include "serialization/hashing.h"
#include "serialization/serialization_header.h"
#include "serialization/serialized_field.h"
#include "serialization/identifiers.h"
#include "world/region.h"
#include <inventory/inventory_manager.h>

void initialize_inventory_manager(
        Inventory_Manager *p_inventory_manager) {
    initialize_repeatable_psuedo_random(
            &p_inventory_manager
            ->randomizer_of__inventory_manager, 
            (u32)(uint64_t)&p_inventory_manager);
    p_inventory_manager
        ->quantity_of__active_inventories_for__containers = 0;
    p_inventory_manager
        ->quantity_of__active_inventories_for__entities = 0;
    for (Index__u32 index_of__inventory = 0;
            index_of__inventory
            < INVENTORY_MAX_QUANTITY_OF__CONTAINER;
            index_of__inventory++) {
        Inventory *p_inventory =
            get_p_inventory_for__container_by__index_in__inventory_manager(
                    p_inventory_manager,
                    index_of__inventory);
        initialize_inventory_as__empty(
                p_inventory);
    }
    for (Index__u32 index_of__inventory = 0;
            index_of__inventory
            < INVENTORY_MAX_QUANTITY_OF__ENTITY;
            index_of__inventory++) {
        Inventory *p_inventory =
            get_p_inventory_for__entity_by__index_in__inventory_manager(
                    p_inventory_manager,
                    index_of__inventory);
        initialize_inventory_as__empty(
                p_inventory);
    }
}

Inventory *allocate_p_inventory_using__this_uuid_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Identifier__u32 uuid) {
    if (is_identifier_u32__invalid(uuid))
        return 0;

    bool is_inventory_for__entity_or__container =
        is_inventory_uuid_for__entity_or__container(uuid);

    Serialization_Header *p_inventories =
        (is_inventory_for__entity_or__container)
        ? (Serialization_Header*)p_inventory_manager->inventories_for__entities
        : (Serialization_Header*)p_inventory_manager->inventories_for__containers
        ;

    Quantity__u32 quantity_of__inventories =
        (is_inventory_for__entity_or__container)
        ? INVENTORY_MAX_QUANTITY_OF__ENTITY
        : INVENTORY_MAX_QUANTITY_OF__CONTAINER
        ;

    Index__u32 resolved_index =
        poll_for__uuid_collision(
                p_inventories,
                quantity_of__inventories,
                uuid);

    Inventory *p_inventory =
        (is_inventory_for__entity_or__container)
        ? get_p_inventory_for__entity_by__index_in__inventory_manager(
                p_inventory_manager,
                resolved_index)
        : get_p_inventory_for__container_by__index_in__inventory_manager(
                p_inventory_manager, 
                resolved_index)
        ;

    initialize_inventory(
            p_inventory, 
            uuid);

    if (is_inventory_for__entity_or__container) {
        p_inventory_manager
            ->quantity_of__active_inventories_for__entities++;
    } else {
        p_inventory_manager
            ->quantity_of__active_inventories_for__containers++;
    }

    return p_inventory;
}

Inventory *allocate_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager) {

    Identifier__u32 uuid = 
        get_random__uuid_u32(
                &p_inventory_manager
                ->randomizer_of__inventory_manager)
        & ~UUID_MASK__INVENTORY__ITEM_STACK;

    bool is_inventory_for__entity_or__container =
        is_inventory_uuid_for__entity_or__container(
                uuid);

    Serialization_Header *p_inventories =
        (is_inventory_for__entity_or__container)
        ? (Serialization_Header*)p_inventory_manager->inventories_for__entities
        : (Serialization_Header*)p_inventory_manager->inventories_for__containers
        ;

    Quantity__u32 quantity_of__inventories =
        (is_inventory_for__entity_or__container)
        ? INVENTORY_MAX_QUANTITY_OF__ENTITY
        : INVENTORY_MAX_QUANTITY_OF__CONTAINER
        ;

    uuid =
        get_next_available__uuid_in__contiguous_array(
                p_inventories,
                quantity_of__inventories,
                uuid);

    return 
        allocate_p_inventory_using__this_uuid_in__inventory_manager(
                p_inventory_manager, 
                uuid);
}

void release_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Inventory *p_inventory) {
    debug_info("release: %x",
            p_inventory->_serialization_header.uuid);
    bool is_inventory_for__entity_or__container =
        is_inventory_uuid_for__entity_or__container(
                p_inventory->_serialization_header.uuid);
    Inventory *p_inventories =
        (is_inventory_for__entity_or__container)
        ? p_inventory_manager->inventories_for__entities
        : p_inventory_manager->inventories_for__containers
        ;

    Quantity__u32 max_quantity_of__inventories =
        (is_inventory_for__entity_or__container)
        ? INVENTORY_MAX_QUANTITY_OF__ENTITY
        : INVENTORY_MAX_QUANTITY_OF__CONTAINER
        ;
#ifndef NDEBUG
    if (p_inventory
            - p_inventories
            >= max_quantity_of__inventories) {
        debug_abort("release_p_inventory_in__inventory_manager, p_inventory: %p does not belong to this manager: %p.",
                p_inventory,
                p_inventory_manager);
        return;
    }
#endif
    initialize_inventory_as__empty(
            p_inventory);
    if (is_inventory_for__entity_or__container) {
        p_inventory_manager
            ->quantity_of__active_inventories_for__entities--;
    } else {
        p_inventory_manager
            ->quantity_of__active_inventories_for__containers--;
    }
}

bool resolve_s_inventory_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Inventory_Ptr *s_inventory_ptr) {
#ifndef NDEBUG
    if (!p_inventory_manager) {
        debug_abort("resolve_s_inventory_ptr_to__inventory_manager, p_inventory_manager is null.");
        return false;
    }
    if (!s_inventory_ptr) {
        debug_abort("resolve_s_inventory_ptr_to__inventory_manager, s_inventory_ptr is null.");
        return false;
    }
#endif
    if (is_p_serialized_field__linked(
                s_inventory_ptr)) {
        if (s_inventory_ptr->p_serialized_field__inventory
                - p_inventory_manager->inventories_for__entities
                < INVENTORY_MAX_QUANTITY_OF__ENTITY
                || s_inventory_ptr->p_serialized_field__inventory
                - p_inventory_manager->inventories_for__containers
                < INVENTORY_MAX_QUANTITY_OF__CONTAINER) {
            return true;
        }
    }

    Identifier__u32 inventory_identifier__u32 =
        s_inventory_ptr->identifier_for__serialized_field
        & ~UUID_MASK__INVENTORY__ITEM_STACK
        ;

    Serialized_Inventory_Ptr s_inventory_ptr__copy;
    initialize_serialized_field_as__unlinked(
            &s_inventory_ptr__copy, 
            inventory_identifier__u32);

    bool is_inventory_for__entity_or__container =
        is_inventory_uuid_for__entity_or__container(
                inventory_identifier__u32);
    Serialization_Header *p_inventories =
        (is_inventory_for__entity_or__container)
        ? (Serialization_Header*)p_inventory_manager->inventories_for__entities
        : (Serialization_Header*)p_inventory_manager->inventories_for__containers
        ;

    Quantity__u32 max_quantity_of__inventories =
        (is_inventory_for__entity_or__container)
        ? INVENTORY_MAX_QUANTITY_OF__ENTITY
        : INVENTORY_MAX_QUANTITY_OF__CONTAINER
        ;

    link_serialized_field_against__contiguous_array(
            &s_inventory_ptr__copy, 
            p_inventories,
            max_quantity_of__inventories);

    if (is_p_serialized_field__linked(
                &s_inventory_ptr__copy)) {
        s_inventory_ptr->p_serialized_field__inventory =
            s_inventory_ptr__copy.p_serialized_field__inventory;
        return true;
    }

    return false;
}

bool resolve_s_item_stack_ptr_to__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Serialized_Item_Stack_Ptr *s_item_stack_ptr) {
    if (is_p_serialized_field__linked(s_item_stack_ptr)) {
        return true;
    }

    Serialized_Inventory_Ptr s_inventory;
    initialize_serialized_field_as__unlinked(
            &s_inventory,
            s_item_stack_ptr->identifier_for__serialized_field);
    if (!resolve_s_inventory_ptr_to__inventory_manager(
            p_inventory_manager, 
            &s_inventory)) {
        return false;
    }

    Item_Stack *p_item_stack =
        get_p_item_stack_from__inventory(
                s_inventory.p_serialized_field__inventory, 
                s_item_stack_ptr->identifier_for__serialized_field);

    if (!p_item_stack)
        return false;

    s_item_stack_ptr->p_serialized_field__item_stack =
        p_item_stack;
    return is_p_serialized_field__linked(
            s_item_stack_ptr);
}

void foreach_p_inventory_container_in__chunk_vector(
        Inventory_Manager *p_inventory_manager,
        Chunk_Vector__3i32 chunk_vector__3i32,
        f_Foreach_Inventory_Container f_callback,
        Game *p_game,
        void *p_data) {
    truncate_p_chunk_vector_3i32_to__region(
            &chunk_vector__3i32);

    for (Index__u32 index_of__inventory = 0;
            index_of__inventory
            < INVENTORY_MAX_QUANTITY_OF__CONTAINER;
            index_of__inventory++) {
        Inventory *p_inventory__container =
            get_p_inventory_for__container_by__index_in__inventory_manager(
                    p_inventory_manager, 
                    index_of__inventory);

        Identifier__u32 uuid =
            p_inventory__container->_serialization_header.uuid;

        if (uuid == IDENTIFIER__UNKNOWN__u32)
            continue;

        i32 x__i32 =
            get_inventory_container__x_from__uuid(uuid)
            >> (CHUNK__WIDTH_BIT_SHIFT);
        i32 y__i32 =
            get_inventory_container__y_from__uuid(uuid)
            >> (CHUNK__WIDTH_BIT_SHIFT);
        // TODO: do z-axis

        if (x__i32 == chunk_vector__3i32.x__i32
                && y__i32 == chunk_vector__3i32.y__i32) {
            f_callback(
                    p_game,
                    p_inventory__container,
                    p_inventory_manager,
                    p_data);
        }
    }
}
