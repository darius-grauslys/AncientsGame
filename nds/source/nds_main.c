#include "defines_weak.h"
#include "game.h"
#include "rendering/handlers/nds_gfx_handler__player.h"
#include "rendering/handlers/nds_gfx_handler__skeleton.h"
#include "rendering/handlers/nds_gfx_handler__zombie.h"
#include "rendering/handlers/nds_gfx_handler__item.h"
#include <platform.h>
#include <nds_defines.h>
#include <scene/nds_scene_manager.h>
#include <rendering/gfx_context.h>

PLATFORM_Gfx_Context _NDS_gfx_context;

int PLATFORM_main(Game *p_game) {
    NDS_initialize_gfx_context(
            &_NDS_gfx_context);
    p_game->p_gfx_context =
        &_NDS_gfx_context;

    NDS_register_sprite_gfx_allocator_for__entity(
            &_NDS_gfx_context, 
            Entity_Kind__Player, 
            f_sprite_gfx_allocator__handler_for__player);
    NDS_register_sprite_gfx_allocator_for__entity(
            &_NDS_gfx_context, 
            Entity_Kind__Skeleton, 
            f_sprite_gfx_allocator__handler_for__skeleton);
    NDS_register_sprite_gfx_allocator_for__entity(
            &_NDS_gfx_context, 
            Entity_Kind__Zombie, 
            f_sprite_gfx_allocator__handler_for__zombie);

    NDS_register_sprite_gfx_allocator_for__items(
            &_NDS_gfx_context,
            f_sprite_gfx_allocator__handler_for__items);

    NDS_establish_scenes(
            &p_game->scene_manager);

    return run_game(p_game);
}
