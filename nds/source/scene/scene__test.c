#include <defines.h>
#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines_weak.h"
#include "entity/humanoid.h"
#include "game.h"
#include "input/input.h"
#include "inventory/equipment.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_stack.h"
#include "nds/arm9/background.h"
#include "nds/arm9/video.h"
#include "nds_defines.h"
#include "platform.h"
#include "platform_defines.h"
#include "process/process.h"
#include "process/process_manager.h"
#include "rendering/font/message.h"
#include "rendering/font/typer.h"
#include "rendering/nds_background.h"
#include "rendering/sprite.h"
#include "ui/game/nds_ui_window__game__equip.h"
#include "ui/game/nds_ui_window__game__trade.h"
#include "ui/nds_ui.h"
#include "ui/nds_ui__equipment.h"
#include "ui/nds_ui__inventory_column.h"
#include "ui/nds_ui__slider.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include "world/world.h"
#include <scene/nds_scene__test.h>
#include <debug/nds_debug.h>
#include <scene/scene.h>
#include <ui/nds_ui__draggable.h>
#include <rendering/gfx_context.h>
#include <numerics.h>

enum Item_Kind item_kind = Item_Kind__Stick;

PLATFORM_Sprite *p_item_sprite;

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_set_vram_for__backgrounds_on__sub();
    NDS_set_vram_and__oam_for__sprites_on__sub();
    NDS_load_sprite_palletes__default_into__vram();
    NDS_initialize_debug__main();

    PLATFORM_open_ui(
            p_game,
            UI_Window_Kind__Idle);

    // debug_info("game: %d", sizeof(Game));
    // debug_info("process_manager: %d", sizeof(Process_Manager));
    // debug_info("sort_list_manager: %d", sizeof(Sort_List_Manager));
    // debug_info("path_list_manager: %d", sizeof(Path_List_Manager));
    // debug_info("path: %d", sizeof(Path));
    // debug_info("chunk: %d", sizeof(Chunk));
    // debug_info("tile: %d", sizeof(Tile));
    // debug_info("entity: %d", sizeof(Entity));
    // debug_info("ray: %d", sizeof(Ray__3i32F20));
    // debug_info("inv: %d", sizeof(Inventory));
    // debug_info("nav cap: %d", UI_Sprite_Kind__16x16__Nav__Cap);
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    enum UI_Window_Kind ui_window_kind = UI_Window_Kind__Idle;

    Entity humanoid;
    initialize_entity_as__humanoid(
            &humanoid, 
            Entity_Kind__Player, 
            VECTOR__3i32F4__0_0_0, 
            1, 1);

    Inventory *p_inventory =
        resolve_p_inventory_of__humanoid(
                p_game, 
                &humanoid);

    Item item;
    initialize_item(
            &item, 
            0, 0, 
            0, 
            Item_Kind__Stick, 
            0);

    add_item_stack_to__inventory(
            p_inventory, 
            item, 
            16, 
            32);

    initialize_item(
            &item, 
            0, 0, 
            0, 
            Item_Kind__Armor__Cloth, 
            0);

    add_item_stack_to__inventory(
            p_inventory, 
            item, 
            16, 
            32);

    Item_Stack *p_item_stack__armor =
        get_p_item_stack__armor_slot_from__equipment(
                &humanoid.equipment);

    initialize_item_stack(
            p_item_stack__armor, 
            item, 
            p_item_stack__armor->_serialization_header.uuid, 
            1, 1);

    initialize_item(
            &item, 
            0, 0, 
            0, 
            Item_Kind__Armor__Steel__Chaos, 
            0);

    add_item_stack_to__inventory(
            p_inventory, 
            item, 
            16, 
            32);

    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
        if (is_input__use_released(get_p_input_from__game(p_game))) {
            item_kind++;
            ui_window_kind++;
            debug_info("ui_window_kind: %d", ui_window_kind);
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            if (ui_window_kind
                    == UI_Window_Kind__Equip) {
                UI_Element *p_ui_element__inventory_column =
                    get_p_ui_element_by__index_from__ui_manager(
                            get_p_ui_manager_from__game(p_game), 
                            NDS_UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13);

                UI_Element *p_ui_element__equipment_column =
                    get_p_ui_element_by__index_from__ui_manager(
                            get_p_ui_manager_from__game(p_game), 
                            NDS_UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_7);

                NDS_load_ui_inventory_column_for__inventory(
                        p_game,
                        p_ui_element__inventory_column,
                        p_inventory);

                NDS_load_ui_equipment_column_for__equipment(
                        p_game, 
                        p_ui_element__equipment_column, 
                        &humanoid.equipment);
            }
        }
        if (is_input__use_secondary_released(get_p_input_from__game(p_game))) {
            item_kind--;
            ui_window_kind--;
            debug_info("ui_window_kind: %d", ui_window_kind);
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            if (ui_window_kind
                    == UI_Window_Kind__Equip) {
                UI_Element *p_ui_element__inventory_column =
                    get_p_ui_element_by__index_from__ui_manager(
                            get_p_ui_manager_from__game(p_game), 
                            NDS_UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13);

                UI_Element *p_ui_element__equipment_column =
                    get_p_ui_element_by__index_from__ui_manager(
                            get_p_ui_manager_from__game(p_game), 
                            NDS_UI_WINDOW__GAME__EQUIP_P_EQUIPMENT_7);

                NDS_load_ui_inventory_column_for__inventory(
                        p_game,
                        p_ui_element__inventory_column,
                        p_inventory);

                NDS_load_ui_equipment_column_for__equipment(
                        p_game, 
                        p_ui_element__equipment_column, 
                        &humanoid.equipment);
            }
        }
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
