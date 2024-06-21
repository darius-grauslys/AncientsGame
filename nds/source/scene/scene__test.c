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
    NDS_initialize_debug__main();

    PLATFORM_initialize_sprite_for__item(
            &item_sprite,
            Item_Kind__Arrow__Iron,
            TEXTURE_FLAGS__NONE);

    UI_Element *p_ui_draggable =
        get_new__ui_element_from__ui_manager(
                &p_game->ui_manager);

    NDS_initialize_ui_element_as__nds_draggable(
            p_ui_draggable, &item_sprite);
}

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler__default;
}
