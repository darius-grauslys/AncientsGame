#include "ui/ui_inventory_equipment.h"
#include "game.h"
#include "inventory/equipment.h"
#include "inventory/item_stack.h"
#include "platform.h"
#include "rendering/sprite.h"
#include "serialization/serialized_field.h"
#include "ui/ui_draggable.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"

void allocate_ui_equipment_into__ui_element_container(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        UI_Element *p_ui_element,
        Equipment *p_equipment) {
    UI_Manager *p_ui_manager =
        PLATFORM_get_p_ui_manager_from__gfx_window(
                p_PLATFORM_gfx_window);
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
                PLATFORM_Sprite *p_PLATFORM_sprite =
                    allocate_sprite_for__item(
                            get_p_PLATFORM_gfx_context_from__game(p_game),
                            p_PLATFORM_gfx_window,
                            p_item_stack
                            ->item.the_kind_of_item__this_item_is);
                if (p_PLATFORM_sprite) {
                    set_ui_element__PLATFORM_sprite(
                            p_child, 
                            p_PLATFORM_sprite);
                    p_child->ui_sprite_wrapper
                        .frame__current =
                        p_item_stack
                        ->item.the_kind_of_item__this_item_is - 1;
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
