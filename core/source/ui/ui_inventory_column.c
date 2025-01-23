#include "ui/ui_inventory_column.h"
#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/item_stack.h"
#include "platform.h"
#include "rendering/sprite_gfx_allocator_manager.h"
#include "serialization/serialized_field.h"
#include "ui/ui_draggable.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "ui/ui_slider.h"

bool allocate_ui_item_stack(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_graphics_window,
        World *p_world,
        UI_Manager *p_ui_manager,
        Item_Stack *p_item_stack,
        UI_Element *p_ui_element__inventory_slot) {
    if (does_ui_element_have__child(
                p_ui_element__inventory_slot)) {
        release__ui_element_from__ui_manager(
                p_ui_manager,
                p_ui_element__inventory_slot
                ->p_child, 
                p_gfx_context,
                p_graphics_window,
                p_world);
    }
    point_serialized_field_to__this_serialized_struct(
            &p_ui_element__inventory_slot->s_serialized_field, 
            p_item_stack);

    UI_Element *p_child = 
        allocate_ui_element_from__ui_manager_as__child(
                p_ui_manager,
                p_ui_element__inventory_slot);
    if (!p_child)
        return true;

    initialize_ui_element_as__draggable(
            p_child, 
            16, 16, 
            vector_3i32F4_to__vector_3i32(
                p_child
                ->ui_bounding_box__aabb.position__3i32F4), 
            m_ui_draggable__dragged_handler__default);

    if (is_p_item_stack__empty(p_item_stack)) {
        return false;
    }

    bool result_of__sprite_allocation =
        allocate_sprite__item(
                p_gfx_context,
                p_graphics_window,
                get_p_sprite_gfx_allocation_manager_from__gfx_context(
                    p_gfx_context),
                &p_child->ui_sprite_wrapper,
                p_item_stack
                ->item.the_kind_of_item__this_item_is);
    if (result_of__sprite_allocation) {
        set_ui_element__render_handler(
                p_child, 
                m_ui_element__render_handler_for__sprite__default);
    }

    return !result_of__sprite_allocation;
}


void allocate_ui_inventory_column_into__ui_element_container(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element__inventory_column,
        Inventory *p_inventory) {
    if (!p_inventory)
        return;

    UI_Element *p_ui_element__current_inventory_slot =
        p_ui_element__inventory_column;
    Index__u32 index_of__inventory_column_slot = 0;
    do {
        Item_Stack *p_item_stack =
            get_p_item_stack_from__inventory_by__index(
                    p_inventory, 
                    index_of__inventory_column_slot);
        if (!p_item_stack) 
            break;
        if (allocate_ui_item_stack(
                    p_gfx_context,
                    p_gfx_window,
                    p_world,
                    p_ui_manager,
                    p_item_stack,
                    p_ui_element__current_inventory_slot)) {
            break;
        }
        index_of__inventory_column_slot++;
    } while (iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot);
}
