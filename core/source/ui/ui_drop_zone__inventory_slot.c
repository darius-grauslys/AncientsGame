#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory_manager.h"
#include "inventory/item_stack.h"
#include "platform.h"
#include "serialization/serialized_field.h"
#include "ui/ui_element.h"
#include "ui/ui_drop_zone.h"
#include <ui/ui_drop_zone__inventory_slot.h>

void initialize_ui_element_as__drop_zone__inventory_slot(
        UI_Element *p_ui_drop_zone__inventory_slot,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        Serialized_Item_Stack_Ptr s_item_stack_ptr) {
    initialize_ui_element_as__drop_zone(
            p_ui_drop_zone__inventory_slot,
            width__u8,
            height__u8,
            position__3i32,
            m_ui_drop_zone__receive_drop_handler__inventory_slot);
    p_ui_drop_zone__inventory_slot
        ->s_serialized_field =
        s_item_stack_ptr;
}

void m_ui_drop_zone__receive_drop_handler__inventory_slot(
        UI_Manager *p_ui_manager,
        UI_Element *p_this_drop_zone,
        UI_Element *p_ui_element__dropped,
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        Input *p_input) {
    Inventory_Manager *p_inventory_manager =
        get_p_inventory_manager_from__world(p_world);

    if (!resolve_s_item_stack_ptr_to__inventory_manager(
                p_inventory_manager,
                &p_this_drop_zone
                ->s_serialized_field)) {
        debug_error("m_ui_drop_zone__receive_drop_handler__inventory_slot, failed to resolve s_serialized_field: %x",
                p_this_drop_zone
                    ->s_serialized_field
                    .identifier_for__serialized_field
                );
        return;
    }

    UI_Element *p_ui_element__parent_of__dropped =
        p_ui_element__dropped->p_parent;

    if (!p_ui_element__parent_of__dropped)
        return;
    if (p_ui_element__parent_of__dropped
            == p_this_drop_zone)
        return;

    // TODO: we should restrict this even better
    if (!is_ui_element_of__this_kind(
                p_ui_element__parent_of__dropped, 
                UI_Element_Kind__Drop_Zone))
        return;

    if (!resolve_s_item_stack_ptr_to__inventory_manager(
                p_inventory_manager,
                &p_ui_element__parent_of__dropped
                ->s_serialized_field)) {
        debug_error("m_ui_drop_zone__receive_drop_handler__inventory_slot, failed to resolve s_serialized_field of originating drop_zone: %x",
                p_this_drop_zone
                    ->s_serialized_field
                    .identifier_for__serialized_field
                );
        return;
    }

    Item_Stack *p_item_stack__source =
        p_ui_element__parent_of__dropped
        ->s_serialized_field
        .p_serialized_field__item_stack;
    Item_Stack *p_item_stack__destination =
        p_this_drop_zone
        ->s_serialized_field
        .p_serialized_field__item_stack;

    // TODO: this should be done as a Game_Action
    if (resolve_item_stack__merge_or_swap(
            p_item_stack__source, 
            p_item_stack__destination)) {
        // reflect the swap on the ui via the default handler.
        m_ui_drop_zone__receive_drop_handler__default(
                p_ui_manager,
                p_this_drop_zone, 
                p_ui_element__dropped, 
                p_gfx_context,
                p_gfx_window,
                p_world,
                p_input);
    } else {
        // check for empty item_stacks, and if empty, release
        // associated sprites.
        if (is_p_serialized_field__linked(
                    &p_this_drop_zone
                    ->s_serialized_field)) {
            if (is_p_item_stack__empty(
                        p_this_drop_zone
                        ->s_serialized_field
                        .p_serialized_field__item_stack)
                    && does_ui_element_have__PLATFORM_sprite(
                            p_this_drop_zone->p_child)) {
                release_ui_element__PLATFORM_sprite(
                        p_gfx_context,
                        p_this_drop_zone->p_child);
            }
        }
        if (is_p_serialized_field__linked(
                    &p_ui_element__parent_of__dropped
                    ->s_serialized_field)) {
            if (is_p_item_stack__empty(
                        p_ui_element__parent_of__dropped
                        ->s_serialized_field
                        .p_serialized_field__item_stack)
                    && does_ui_element_have__PLATFORM_sprite(
                        p_ui_element__parent_of__dropped->p_child)) {
                release_ui_element__PLATFORM_sprite(
                        p_gfx_context,
                        p_ui_element__parent_of__dropped->p_child);
            }
        }
    }
}
