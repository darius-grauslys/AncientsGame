#include <defines.h>
#include "debug/debug.h"
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "platform.h"
#include "platform_defines.h"
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

Quantity__u16 __x = 0;
Quantity__u16 __y = 0;
PLATFORM_Sprite item_sprite;
enum Item_Kind item_kind = Item_Kind__Stick;
enum UI_Window_Kind ui_window_kind = UI_Window_Kind__None;

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_set_vram_for__backgrounds_on__sub();
    NDS_set_vram_and__oam_for__sprites_on__sub();
    NDS_load_sprite_palletes__default_into__vram();
    NDS_initialize_debug__main();

    PLATFORM_initialize_sprite_for__item(
            &item_sprite,
            item_kind,
            TEXTURE_FLAGS__NONE);

    UI_Element *p_ui_slider =
        allocate_ui_element_from__ui_manager(
                &p_game->ui_manager);

    NDS_initialize_ui_element_as__nds_slider(
            p_ui_slider, 
            get_vector__3i32(80,80,0),
            100,
            100,
            true,
            &item_sprite);

    PLATFORM_open_ui(
            p_game,
            UI_Window_Kind__Trade);
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
        if (is_input__forward_held(get_p_input_from__game(p_game))) {
            __y += 1;
        }
        if (is_input__backward_held(get_p_input_from__game(p_game))) {
            __y -= 1;
        }
        if (is_input__left_held(get_p_input_from__game(p_game))) {
            __x -= 1;
        }
        if (is_input__right_held(get_p_input_from__game(p_game))) {
            __x += 1;
        }
        PLATFORM_set_sprite__position(
                &item_sprite, 
                __x, __y);
        if (is_input__use_released(get_p_input_from__game(p_game))) {
            item_kind++;
            ui_window_kind =
                clamp__u8((uint8_t)(ui_window_kind + 1), 0,
                        UI_Window_Kind__Typer);
            PLATFORM_set_sprite_graphics_to__item_kind(
                    &item_sprite, 
                    item_kind);
            PLATFORM_open_ui(
                    p_game,
                    ui_window_kind);
            debug_info("ui_window_kind: %d", ui_window_kind);
        }
        if (is_input__use_secondary_released(get_p_input_from__game(p_game))) {
            item_kind--;
            PLATFORM_set_sprite_graphics_to__item_kind(
                    &item_sprite, 
                    item_kind);
            ui_window_kind = 
                clamp__u8((uint8_t)(ui_window_kind - 1), 0,
                        UI_Window_Kind__Typer);
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
