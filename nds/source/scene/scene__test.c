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
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    enum UI_Window_Kind ui_window_kind = UI_Window_Kind__Idle;

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
        }
        if (is_input__use_secondary_released(get_p_input_from__game(p_game))) {
            item_kind--;
            ui_window_kind--;
            debug_info("ui_window_kind: %d", ui_window_kind);
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
        }
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
