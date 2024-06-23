#include <defines.h>
#include "defines_weak.h"
#include "game.h"
#include "input/input.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/nds_gfx_context.h"
#include "ui/nds_ui.h"
#include "ui/nds_ui__slider.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include "world/world.h"
#include <scene/scene__test.h>
#include <debug/nds_debug.h>
#include <scene/scene.h>
#include <ui/nds_ui__draggable.h>

PLATFORM_Sprite item_sprite;
enum Item_Kind item_kind = Item_Kind__Stick;

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_initialize_gfx_for__sub_background();
    NDS_initialize_gfx_for__sub_sprites();
    NDS_load_sprite_palletes();
    NDS_initialize_debug__main();

    PLATFORM_initialize_sprite_for__item(
            &item_sprite,
            item_kind,
            TEXTURE_FLAGS__NONE);

    UI_Element *p_ui_slider =
        get_new__ui_element_from__ui_manager(
                &p_game->ui_manager);

    NDS_initialize_ui_element_as__nds_slider(
            p_ui_slider, 
            get_vector__3i32(80,80,0),
            100,
            16,
            true,
            &item_sprite);
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
        if (is_input__use_released(get_p_input_from__game(p_game))) {
            item_kind++;
            PLATFORM_set_sprite_graphics_to__item_kind(
                    &item_sprite, 
                    item_kind);
        }
        if (is_input__use_secondary_released(get_p_input_from__game(p_game))) {
            item_kind--;
            PLATFORM_set_sprite_graphics_to__item_kind(
                    &item_sprite, 
                    item_kind);
        }
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
