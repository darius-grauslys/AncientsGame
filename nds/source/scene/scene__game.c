#include "debug/debug.h"
#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "game.h"
#include "rendering/nds_gfx_context.h"
#include "world/chunk_manager.h"
#include <scene/scene__game.h>

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void init_scene_as__game(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__game_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__game_handler;
    p_scene->m_unload_scene_handler =
        m_unload_scene_as__game_handler;
}

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    PLATFORM_Gfx_Context *gfx_context =
        &p_game->gfx_context;

    NDS_init_gfx_for__world(gfx_context);
    init_world(&p_game->world);
}

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {

    // TODO: prob wanna remove some of the stuff below
    get_new__player(
            &p_game->world.entity_manager, 
            true,
            0, 0, 0);

    move_chunk_manager(
            &p_game->world.chunk_manager, 
            &p_game->world.world_parameters, 
            DIRECTION__NORTH_WEST,
            2);

    PLATFORM_update_chunks(
            &p_game->gfx_context,
            &p_game->world.chunk_manager);

    while (1) {
        manage_game(p_game);
        manage_world(p_game);
    }
}

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    //TODO: impl
    debug_error("not impl, unload game");
}
