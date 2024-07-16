#include <defines.h>
#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "inventory/inventory.h"
#include "inventory/item.h"
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
            UI_Window_Kind__Trade);

    Inventory inventory;
    initialize_inventory(&inventory);
    Item item;
    initialize_item(
            &item, 
            0, 0, 
            0, 
            Item_Kind__Stick, 
            0);

    add_item_stack_to__inventory(
            &inventory, 
            item, 
            0, 
            16, 
            32);

    initialize_item(
            &item, 
            0, 0, 
            0, 
            Item_Kind__Battleaxe__Steel__Chaos, 
            0);

    add_item_stack_to__inventory(
            &inventory, 
            item, 
            4, 
            16, 
            32);

    UI_Element *p_ui_element__inventory_column =
        get_p_ui_element_by__index_from__ui_manager(
                get_p_ui_manager_from__game(p_game), 
                NDS_UI_WINDOW__GAME__TRADE_P_INVENTORY_COLUMN__LEFT_8);

    NDS_load_inventory_column_for__inventory(
            p_game,
            p_ui_element__inventory_column,
            &inventory);

    debug_info("game: %d", sizeof(Game));
    debug_info("process_manager: %d", sizeof(Process_Manager));
    debug_info("sort_list_manager: %d", sizeof(Sort_List_Manager));
    debug_info("path_list_manager: %d", sizeof(Path_List_Manager));
    debug_info("path: %d", sizeof(Path));
    debug_info("chunk: %d", sizeof(Chunk));
    debug_info("entity: %d", sizeof(Entity));
    debug_info("ray: %d", sizeof(Ray__3i32F20));
    debug_info("inv: %d", sizeof(Inventory));

}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    enum UI_Window_Kind ui_window_kind = UI_Window_Kind__None;
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
        if (is_input__use_released(get_p_input_from__game(p_game))) {
            item_kind++;
            ui_window_kind++;
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            debug_info("ui_window_kind: %d", ui_window_kind);
        }
        if (is_input__use_secondary_released(get_p_input_from__game(p_game))) {
            item_kind--;
            ui_window_kind--;
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            debug_info("ui_window_kind: %d", ui_window_kind);
        }
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
