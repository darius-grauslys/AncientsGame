#include "defines.h"
#include "defines_weak.h"
#include "inventory/inventory.h"
#include "numerics.h"
#include "random.h"
#include "serialization/hashing.h"
#include "serialization/serialization_header.h"
#include "serialization/serialized_field.h"
#include "serialization/identifiers.h"
#include <inventory/inventory_manager.h>

void initialize_inventory_manager(
        Inventory_Manager *p_inventory_manager) {
    initialize_repeatable_psuedo_random(
            &p_inventory_manager
            ->randomizer_of__inventory_manager, 
            (u32)(uint64_t)&p_inventory_manager);
    p_inventory_manager
        ->quantity_of__active_inventories = 0;
    for (Index__u32 index_of__inventory = 0;
            index_of__inventory
            < INVENTORY_MAX_QUANTITY_OF;
            index_of__inventory++) {
        Inventory *p_inventory =
            get_p_inventory_by__index_in__inventory_manager(
                    p_inventory_manager,
                    index_of__inventory);
        initialize_inventory_as__empty(
                p_inventory);
    }
}

Inventory *allocate_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager) {
    p_inventory_manager->quantity_of__active_inventories++;

    Identifier__u32 uuid = 
        get_random__uuid_u32(
                &p_inventory_manager
                ->randomizer_of__inventory_manager)
        & ~MASK(ITEM_STACK_IDENTIFIER_BITS);
    uuid =
        get_next_available__uuid_in__contiguous_array(
                (Serialization_Header*)p_inventory_manager
                    ->inventories, 
                INVENTORY_MAX_QUANTITY_OF, 
                uuid);
    
    if (is_identifier_u32__invalid(uuid))
        return 0;

    Inventory *p_inventory =
        get_p_inventory_by__index_in__inventory_manager(
                p_inventory_manager, 
                bound_uuid_to__contiguous_array(
                    uuid, 
                    INVENTORY_MAX_QUANTITY_OF));

    initialize_inventory(
            p_inventory, 
            uuid >> ITEM_STACK_IDENTIFIER_BITS);

    return p_inventory;
}

void release_p_inventory_in__inventory_manager(
        Inventory_Manager *p_inventory_manager,
        Inventory *p_inventory) {
#ifndef NDEBUG
    if (p_inventory
            - p_inventory_manager->inventories
            >= INVENTORY_MAX_QUANTITY_OF) {
        debug_abort("release_p_inventory_in__inventory_manager, p_inventory: %p does not belong to this manager: %p.",
                p_inventory,
                p_inventory_manager);
        return;
    }
#endif
    initialize_inventory_as__empty(
            p_inventory);
    p_inventory_manager->quantity_of__active_inventories--;
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
                - p_inventory_manager->inventories
                < INVENTORY_MAX_QUANTITY_OF) {
            return true;
        }
    }

    Identifier__u32 inventory_identifier__u32 =
        s_inventory_ptr->identifier_for__serialized_field
        >> ITEM_STACK_IDENTIFIER_BITS;

    Serialized_Inventory_Ptr s_inventory_ptr__copy;
    initialize_serialized_field_as__unlinked(
            &s_inventory_ptr__copy, 
            inventory_identifier__u32);

    link_serialized_field_against__contiguous_array(
            &s_inventory_ptr__copy, 
            (Serialization_Header*)p_inventory_manager->inventories, 
            p_inventory_manager->quantity_of__active_inventories);

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

    Identifier__u32 inventory_identifier__u32 =
        merge_identifiers_u32(
                0,
                INVENTORY_IDENTIFIER_BITS, 
                s_item_stack_ptr->identifier_for__serialized_field);

    Item_Stack *p_item_stack =
        get_p_item_stack_from__inventory(
                s_inventory.p_serialized_field__inventory, 
                inventory_identifier__u32);

    if (!p_item_stack)
        return false;

    s_item_stack_ptr->p_serialized_field__item_stack =
        p_item_stack;
    return is_p_serialized_field__linked(
            s_item_stack_ptr);
}
