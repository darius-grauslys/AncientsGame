#include "ui/ui_inventory_equipment.h"
#include "game.h"
#include "inventory/equipment.h"
#include "inventory/item_stack.h"
#include "platform.h"
#include "rendering/sprite.h"
#include "rendering/sprite_gfx_allocator_manager.h"
#include "serialization/serialized_field.h"
#include "ui/ui_draggable.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"

void allocate_ui_equipment_into__ui_element_container(
        Game *p_game,
        Graphics_Window *p_gfx_window,
        UI_Element *p_ui_element,
        Equipment *p_equipment) {
    UI_Manager *p_ui_manager =
#warning TODO: remove PLATFORM_ func here, and take ui_manager from p_gfx_window
        PLATFORM_get_p_ui_manager_from__gfx_window(
                p_gfx_window->p_PLATFORM_gfx_window);
    UI_Element *p_ui_element__current_equipment_slot =
        p_ui_element;
    Index__u32 index_of__inventory_column_slot = 0;
    do {
        if (does_ui_element_have__child(
                    p_ui_element__current_equipment_slot)) {
            release__ui_element_from__ui_manager(
                    p_ui_manager,
                    p_ui_element__current_equipment_slot
                    ->p_child, 
                    p_game);
        }
        if (p_equipment) {
            Item_Stack *p_item_stack =
                get_p_item_stack_by__index_in__equipment(
                        p_equipment, 
                        index_of__inventory_column_slot);
            point_serialized_field_to__this_serialized_struct(
                    &p_ui_element__current_equipment_slot->s_serialized_field, 
                    p_item_stack);

            UI_Element *p_child = 
                allocate_ui_element_from__ui_manager_as__child(
                        p_ui_manager,
                        p_ui_element__current_equipment_slot);
            initialize_ui_element_as__draggable(
                    p_child, 
                    16, 16, 
                    vector_3i32F4_to__vector_3i32(
                        p_child
                        ->ui_bounding_box__aabb.position__3i32F4), 
                    m_ui_draggable__dragged_handler__default);

            if (!is_p_item_stack__empty(p_item_stack)) {
                bool result_of__sprite_allocation =
                    allocate_sprite__item(
                            get_p_gfx_context_from__game(p_game),
                            p_gfx_window,
                            get_p_sprite_gfx_allocation_manager_from__game(
                                p_game),
                            &p_child->ui_sprite_wrapper,
                            p_item_stack
                            ->item.the_kind_of_item__this_item_is);
                if (result_of__sprite_allocation) {
                    set_ui_element__render_handler(
                            p_child, 
                            m_ui_element__render_handler_for__sprite__default);
                }
            }
        }
        index_of__inventory_column_slot++;
    } while (iterate_to_next__ui_element(
                &p_ui_element__current_equipment_slot)
            && p_ui_element__current_equipment_slot);
}
