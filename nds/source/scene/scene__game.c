#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "debug/nds_debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "entity/handlers/entity_handlers.h"
#include "entity/humanoid.h"
#include "game.h"
#include "game_action/game_action.h"
#include "input/input.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "nds/arm9/background.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/sprite.h"
#include "scene/scene_manager.h"
#include "ui/game/nds_ui_background__game__hud.h"
#include "ui/nds_ui.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "world/chunk.h"
#include "world/chunk_manager.h"
#include "world/container.h"
#include "world/tile.h"
#include "world/tile_vectors.h"
#include "world/world.h"
#include <scene/nds_scene__game.h>
#include <stdint.h>
#include <timer.h>
#include <vectors.h>
#include <rendering/gfx_context.h>

#include <assets/ui/default/ui_tileset_default.h>

Scene_Data__Game scene_data__game;

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void initialize_scene_as__game(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__game_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__game_handler;
    p_scene->m_unload_scene_handler =
        m_unload_scene_as__game_handler;

    p_scene->p_scene_data =
        &scene_data__game;

    //TODO: magic number
    initialize_timer_u8(
            &scene_data__game
            .timer_for__hud_notification__u8,
            30);
    initialize_timer_u8(
            &scene_data__game
            .timer_for__typer_sliding__u8,
            16);
}

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    NDS_initialize_gfx_for__world(p_gfx_context);
    initialize_world(
            p_game,
            get_p_world_from__game(p_game),
            NDS_get_graphics_window__main_from__gfx_context(
                get_p_PLATFORM_gfx_context_from__game(p_game)));

    //NDS_initialize_debug__sub();
    //return;
    NDS_initialize_gfx_for__ui(
            get_p_PLATFORM_gfx_context_from__game(p_game));
    // TODO: re-impl
    // NDS_set_ui_background_to__equip(&p_game->gfx_context);

    PLATFORM_open_ui(
            p_game,
            UI_Window_Kind__Idle);
}

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {

    // TODO: prob wanna remove some of the stuff below
    Entity *p_player = 
        allocate_entity_into__world(
                p_game,
                get_p_world_from__game(p_game),
                Entity_Kind__Player,
                get_vector__3i32F4_using__i32(0, 0, 0));

    p_game->world.entity_manager
        .p_local_player =
        p_player;

    set_camera_to__track_this__entity(
            &p_game->world.camera, 
            p_player);

    move_chunk_manager(
            p_game,
            &p_game->world.chunk_manager, 
            DIRECTION__SOUTH_WEST,
            2);

    Tile *p_tile =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__game(p_game), 
                get_vector__3i32F4_using__i32(0, 0, 0));

    p_tile->the_kind_of_tile_cover__this_tile_has =
        Tile_Cover_Kind__Chest_Single;
    set_tile__container(p_tile, true);
    set_tile__is_unpassable(p_tile, true);

    Identifier__u32 uuid__u32 =
        get_container__uuid(
                get_vector__3i32(0, 2, 0));

    Inventory *p_inventory =
        allocate_p_inventory_using__this_uuid_in__inventory_manager(
                get_p_inventory_manager_from__game(p_game),
                uuid__u32);

    Item_Manager *p_item_manager =
        get_p_item_manager_from__game(p_game);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Stick), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Cloth), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Iron), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Iron__Rusted), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Gold), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Gold__Chaos), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Gold__Order), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Steel), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Steel__Chaos), 
            1, 
            1);
    add_item_stack_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Armor__Steel__Order), 
            1, 
            1);

    Entity *p_skele_bro = 
        allocate_entity_into__world(
                p_game, 
                get_p_world_from__game(p_game), 
                Entity_Kind__Skeleton, 
                get_vector__3i32F4_using__i32(8, 8, 0));

    p_skele_bro->equipment.item_stack__main_hand.item =
        get_item_from__item_manager(
                p_item_manager, 
                Item_Kind__Stick);

    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game),
            get_p_chunk_manager_from__game(p_game));

    while (1) {
        if (p_game->scene_manager.p_active_scene == 0)
            break;
        manage_game(p_game);
        NDS_update_ui_for__hud(
                get_p_PLATFORM_gfx_context_from__game(p_game),
                p_this_scene,
                p_player);
        manage_world(p_game);
    }
}

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    //TODO: impl
    debug_error("not impl, unload game");
}
