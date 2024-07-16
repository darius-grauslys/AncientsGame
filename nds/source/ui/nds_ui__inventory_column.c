#include "defines_weak.h"
#include "game.h"
#include "inventory/item_stack.h"
#include "rendering/sprite.h"
#include "ui/nds_ui__draggable.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include <ui/nds_ui__inventory_column.h>
#include <inventory/inventory.h>
#include "ui/ui_draggable.h"
#include "vectors.h"
#include "nds_defines.h"

void NDS_load_inventory_column_for__inventory(
        Game *p_game,
        UI_Element *p_ui_element__inventory_column,
        Inventory *p_inventory) {
    PLATFORM_Graphics_Window *p_graphics_window =
        &get_p_PLATFORM_gfx_context_from__game(p_game)
        ->graphics_window__sub;
    UI_Manager *p_ui_manager =
        get_p_ui_manager_from__game(p_game);
    UI_Element *p_ui_element__current_inventory_slot =
        p_ui_element__inventory_column;
    Index__u32 index_of__inventory_column_slot = 0;
    do {
        if (does_ui_element_have__child(
                    p_ui_element__current_inventory_slot)) {
            release__ui_element_from__ui_manager(
                    p_ui_element__current_inventory_slot
                    ->p_child, 
                    p_game);
        }
        if (p_inventory) {
            Item_Stack *p_item_stack =
                get_p_item_stack_from__inventory(
                        p_inventory, 
                        index_of__inventory_column_slot);

            UI_Element *p_child = 
                allocate_ui_element_from__ui_manager_as__child(
                        p_ui_manager,
                        p_ui_element__current_inventory_slot);
            initialize_ui_element_as__draggable(
                    p_child, 
                    16, 16, 
                    vector_3i32F4_to__vector_3i32(
                        p_child
                        ->ui_bounding_box__aabb.position__3i32F4), 
                    m_NDS_ui_dragged__handler);

            if (!is_p_item_stack__empty(p_item_stack)) {
                PLATFORM_Sprite *p_PLATFORM_sprite =
                    allocate_sprite_for__item(
                            get_p_PLATFORM_gfx_context_from__game(p_game),
                            p_graphics_window,
                            p_item_stack
                            ->item.the_kind_of_item__this_item_is);
                if (p_PLATFORM_sprite) {
                    set_ui_element__PLATFORM_sprite(
                            p_child, p_PLATFORM_sprite);
                }
            }
        }
        index_of__inventory_column_slot++;
    } while (iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot);
}
