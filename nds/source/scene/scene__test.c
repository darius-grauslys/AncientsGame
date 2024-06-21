#include <defines.h>
#include "defines_weak.h"
#include "platform_defines.h"
#include "rendering/nds_gfx_context.h"
#include "ui/nds_ui.h"
#include "ui/ui_manager.h"
#include "world/world.h"
#include <scene/scene__test.h>
#include <debug/nds_debug.h>
#include <scene/scene.h>
#include <ui/nds_ui__draggable.h>

PLATFORM_Sprite item_sprite;

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_initialize_gfx_for__world(&p_game->gfx_context);
    initialize_world(&p_game->world);
    NDS_initialize_debug__main();
    NDS_initialize_gfx_for__ui(
            &p_game->gfx_context);
    NDS_set_ui_background_to__equip(
            &p_game->gfx_context);

    PLATFORM_initialize_sprite_for__item(
            &item_sprite,
            Item_Kind__Arrow__Iron,
            TEXTURE_FLAGS__NONE);
}

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__game_handler;
}
