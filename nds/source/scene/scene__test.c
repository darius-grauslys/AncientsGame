#include <defines.h>
#include "debug/debug.h"
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "nds/arm9/background.h"
#include "nds_defines.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/sprite.h"
#include "ui/nds_ui.h"
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
enum UI_Window_Kind ui_window_kind = UI_Window_Kind__None;

PLATFORM_Sprite *p_item_sprite;

int y, x, a, b, c, d;

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    y = 0; x = 0; a = 0; b = 0; c = 0; d = 0;
    NDS_set_vram_for__backgrounds_on__sub();
    NDS_set_vram_and__oam_for__sprites_on__sub();
    NDS_load_sprite_palletes__default_into__vram();
    NDS_initialize_debug__main();

    Sprite_Allocation_Specification
        sprite_allocation_specification;

    initialize_sprite_allocation_specification_for__item(
            &sprite_allocation_specification, 
            TEXTURE_FLAGS__NONE, 
            get_p_ui_manager_from__game(p_game)
                ->p_PLATFORM_graphics_window_for__ui_manager, 
            Item_Kind__Stick);

    p_item_sprite = PLATFORM_allocate_sprite(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            &sprite_allocation_specification);

    PLATFORM_set_sprite__position(
            p_item_sprite, 40, 40);

    // PLATFORM_open_ui(
    //         p_game,
    //         UI_Window_Kind__Trade);
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
        if (is_input__forward_held(get_p_input_from__game(p_game))) {
            y--;
            debug_info("y: %d", y);
        }
        if (is_input__backward_held(get_p_input_from__game(p_game))) {
            y++;
            debug_info("y: %d", y);
        }
        if (is_input__left_held(get_p_input_from__game(p_game))) {
            x--;
            debug_info("x: %d", x);
        }
        if (is_input__right_held(get_p_input_from__game(p_game))) {
            x++;
            debug_info("x: %d", x);
        }
        if (is_input__use_released(get_p_input_from__game(p_game))) {
            item_kind++;
            ui_window_kind =
                clamp__u8((uint8_t)(ui_window_kind + 1), 0,
                        UI_Window_Kind__Typer);
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            debug_info("ui_window_kind: %d", ui_window_kind);
        }
        if (is_input__use_secondary_released(get_p_input_from__game(p_game))) {
            item_kind--;
            ui_window_kind = 
                clamp__u8((uint8_t)(ui_window_kind - 1), 0,
                        UI_Window_Kind__Typer);
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            debug_info("ui_window_kind: %d", ui_window_kind);
        }
        bgSetScroll(
                p_game
                ->p_gfx_context
                ->backgrounds__sub[
                    NDS_BACKGROUND_SLOT__UI__SCROLL]
                    .background_index_from__hardware, x, y);
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
