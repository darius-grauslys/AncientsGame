#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "inventory/item_stack.h"
#include "numerics.h"
#include "platform.h"
#include "serialization/hashing.h"
#include "serialization/identifiers.h"
#include "serialization/serialization_header.h"
#include "serialization/serialized_field.h"
#include "inventory/inventory.h"
#include "serialization/serializer.h"

void remove_all_unequiped_item_stacks_from__inventory(
        Inventory *p_inventory) {
    for (Index__u8 index_of__item_stack=0;
            index_of__item_stack < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item_stack++) {
        initialize_item_stack_as__empty(
                &p_inventory->items[index_of__item_stack], 
                p_inventory->_serialization_header.uuid
                + index_of__item_stack);
        set_inventory_uuid__item_stack_index(
                &p_inventory->items[index_of__item_stack]
                    ._serialization_header.uuid,
                index_of__item_stack);
    }
}

void initialize_inventory(
        Inventory *p_inventory,
        Identifier__u32 identifier_for__inventory) {
    // TODO: replace the 0, 0 with serialize/deserialize handlers.
    intialize_serializer(
            &p_inventory->_serializer, 
            sizeof(Inventory),
            identifier_for__inventory, 
            m_serialize__inventory,
            m_deserialize__inventory);
    remove_all_unequiped_item_stacks_from__inventory(
            p_inventory);
}

void initialize_inventory_as__empty(
        Inventory *p_inventory) {
    initialize_serialization_header_for__deallocated_struct(
            &p_inventory->_serialization_header,
            sizeof(Inventory));
    remove_all_unequiped_item_stacks_from__inventory(
            p_inventory);
}

void m_serialize__inventory(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {

    Inventory *p_inventory =
        (Inventory*)p_this_serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    Index__u32 position_of__serialized_item_stack__quantity =
        PLATFORM_get_position_in__file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_file_handler);

    Quantity__u8 quantity_of__serialized_item_stacks = 0;
    enum PLATFORM_Write_File_Error error = PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                &quantity_of__serialized_item_stacks, 
                1, 
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_serialize__inventory, error: %d", error);
        return;
    }

    for (Index__u32 index_of__item_stack = 0;
            index_of__item_stack < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item_stack++) {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, index_of__item_stack);

        if (is_p_item_stack__empty(p_item_stack))
            continue;

        quantity_of__serialized_item_stacks++;

        p_item_stack->_serializer.m_serialize_handler(
                p_game,
                p_serialization_request,
                (Serializer*)p_item_stack);
    }

    Index__u32 position_at__end_of__file =
        PLATFORM_get_position_in__file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_file_handler);

    PLATFORM_set_position_in__file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            position_of__serialized_item_stack__quantity, 
            p_file_handler);

    error = PLATFORM_write_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                &quantity_of__serialized_item_stacks, 
                1, 
                1, 
                p_file_handler);

    PLATFORM_set_position_in__file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            position_at__end_of__file, 
            p_file_handler);
}

void m_deserialize__inventory(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_inventory__serializer) {

    Inventory *p_inventory =
        (Inventory*)p_inventory__serializer;

    void *p_file_handler =
        p_serialization_request
        ->p_file_handler;

    Quantity__u32 length_of__read = 0;

    Quantity__u8 quantity_of__serialized_item_stacks = 0;
    length_of__read = sizeof(quantity_of__serialized_item_stacks);
    enum PLATFORM_Read_File_Error error = 
        PLATFORM_read_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                &quantity_of__serialized_item_stacks, 
                &length_of__read, 
                1, 
                p_file_handler);
    if (error) {
        debug_error("m_deserialize__inventory, failed error: %d", error);
        return;
    }

    if (length_of__read
            != sizeof(quantity_of__serialized_item_stacks)) {
        debug_error("m_deserialize__inventory, bad read length: %d/%d", 
                length_of__read,
                sizeof(quantity_of__serialized_item_stacks));
        return;
    }

    for (Index__u8 index_of__item_stack = 0;
            index_of__item_stack < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item_stack++) {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, index_of__item_stack);

        p_item_stack->_serializer.m_deserialize_handler(
                p_game,
                p_serialization_request,
                (Serializer*)p_item_stack);
    }
}

Item_Stack *get_p_item_stack_from__inventory_by__index(
        Inventory *p_inventory,
        Index__u8 index_of__item) {
    return &p_inventory->items[index_of__item];
}

Index__u8 get_next_available_item_stack_by___index_from__inventory(
        Inventory *p_inventory) {
    for (Index__u8 index_of__item=0;
            index_of__item < INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
            index_of__item++) {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, 
                    index_of__item);
        if (is_p_item_stack__empty(p_item_stack))
            return index_of__item;
    }
    return INDEX__UNKNOWN__u8;
}

Item_Stack *get_next_available_item_stack_in__inventory(
        Inventory *p_inventory) {
    Identifier__u32 uuid__u32 =
        get_next_available_item_stack_by___index_from__inventory(
                p_inventory);

    if (is_index_u8__out_of_bounds(uuid__u32)) {
        debug_warning("get_next_available_p_item_stack_from__inventory, fail to get next item_stack.");
        debug_warning("is the inventory full?");
        return 0;
    }

    Item_Stack *p_item_stack =
        get_p_item_stack_from__inventory_by__index(
                p_inventory, 
                uuid__u32);

    p_inventory->quantity_of__item_stacks++;

    return p_item_stack;
}

///
/// Calls initialize_item_stack to
/// an empty spot in inventory. Does nothing
/// if the inventory is already full.
///
Item_Stack *add_item_to__inventory(
        Inventory *p_inventory,
        Item item,
        Quantity__u8 quantity_of__items,
        Quantity__u8 max_quantity_of__items) {
#ifndef NDEBUG
    if (!p_inventory) {
        debug_abort("add_stack_to__inventory, p_inventory is null.");
        return 0;
    }
#endif
    Item_Stack *p_item_stack =
        get_next_p_item_stack_of__this_item_kind_from__inventory(
                p_inventory, 
                p_inventory->items, 
                item.the_kind_of_item__this_item_is);
    if (!p_item_stack) {
        p_item_stack =
            get_next_available_item_stack_in__inventory(
                    p_inventory);
    }

    if (!p_item_stack) {
        debug_error("add_item_to__inventory, p_item_stack is null.");
        return 0;
    }

    max_quantity_of__items =
        max__u8(max_quantity_of__items,
            p_item_stack->max_quantity_of__items);

    quantity_of__items =
        clamp__u8(
                quantity_of__items
                + p_item_stack->quantity_of__items, 
                0, 
                max_quantity_of__items);
    
    set_item_stack(
            p_item_stack,
            item,
            quantity_of__items,
            max_quantity_of__items);
    return p_item_stack;
}

void copy_p_item_stack_to__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__copy_origin) {
    Item_Stack *p_item_stack =
        get_next_available_item_stack_in__inventory(
                p_inventory);

    if (!p_item_stack) {
        debug_warning("copy_p_item_stack_to__inventory, p_item_stack==0");
        debug_warning("is the inventory full?");
        return;
    }

    copy_item_stack(
            p_item_stack__copy_origin,
            p_item_stack);
}

void move_p_item_stack_to__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack__move_origin) {
    copy_p_item_stack_to__inventory(
            p_inventory, 
            p_item_stack__move_origin);
    initialize_item_stack_as__empty(
            p_item_stack__move_origin,
            p_item_stack__move_origin->_serialization_header.uuid);
}

void remove_p_item_stack_from__inventory(
        Inventory *p_inventory,
        Item_Stack *p_item_stack) {
#ifndef NDEBUG
    if (p_inventory){ 
        debug_abort("remove_p_item_stack_from__inventory, p_inventory is null.");
        return;
    }
    if (!p_item_stack) {
        debug_abort("remove_p_item_stack_from__inventory, p_item_stack is null.");
        return;
    }
    if (p_item_stack
            - p_inventory->items
            >= INVENTORY_ITEM_MAXIMUM_QUANTITY_OF) {
        debug_abort("remove_p_item_stack_from__inventory, p_item_stack: %p, is not from this p_inventory: %p.",
                p_item_stack,
                p_inventory);
        return;
    }
#endif
    initialize_item_stack_as__empty(
            p_item_stack,
            p_item_stack->_serialization_header.uuid);
    p_inventory->quantity_of__item_stacks--;
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
        if (is_p_item_stack__empty(p_item_stack)) {
            remove_p_item_stack_from__inventory(
                    p_inventory, 
                    p_item_stack);
        }
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
        Identifier__u32 identifier_for__item_stack) {
    identifier_for__item_stack &=
        UUID_MASK__INVENTORY__ITEM_STACK;
    identifier_for__item_stack >>=
        UUID_BIT_SHIFT__INVENTORY__ITEM_STACK;
    return &p_inventory->items[identifier_for__item_stack];
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
    return p_inventory->quantity_of__item_stacks
        >= INVENTORY_ITEM_MAXIMUM_QUANTITY_OF;
}
