#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "game.h"
#include "inventory/implemented/weapon.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "inventory/item_stack.h"
#include "numerics.h"
#include "platform.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include "world/tile_vectors.h"
#include "world/tiles/tile__cover__table.h"
#include "world/world.h"
#include <inventory/implemented/hammer__iron/hammer__iron.h>

void register_into__item_manager__hammer__iron_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Hammer__Iron, 
            get_item(
                Item_Kind__Hammer__Iron, 
                ITEM_USAGE_FLAG__IS_LABOR
                | ITEM_USAGE_FLAG__IS_LABOR__SECONDARY
                | ITEM_USAGE_FLAG__IS_COMBAT,
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(4), 
                m_item_use_handler__hammer, 
                0, 
                0));
}

bool use_hammer__place_offhand(
        Game *p_game,
        Item *p_item_self,
        Item_Stack *p_item_stack__offhand,
        Tile *p_tile,
        Vector__3i32F4 vector_front__3i32F4) {
    Tile_Vector__3i32 tile_vector__3i32 =
        vector_3i32F4_to__tile_vector(
                vector_front__3i32F4);

    if (is_item_tool_mode__labor(p_item_self)) {
        bool result__wall = 
            attempt_tile_placement(
                    p_game,
                    Tile_Kind__None,
                    p_item_self
                    ->the_kind_of__tile_cover__this_item_builds,
                    tile_vector__3i32);
        if (result__wall) {
            set_tile__is_unpassable(p_tile, true);
        }
        return result__wall;
    } else if (is_item_tool_mode__labor_secondary(p_item_self)) {
        return attempt_tile_placement(
                    p_game,
                    p_item_self
                    ->the_kind_of__ground__this_item_builds,
                    Tile_Cover_Kind__None,
                    tile_vector__3i32);
    }

    return false;
}

void m_item_use_handler__hammer(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game) {
    Equipment *p_equipment =
        &p_entity_user
        ->equipment;
    Item_Stack *p_item_stack__offhand =
        &p_equipment->item_stack__off_hand;

    // TODO: We should shift control of item placement
    //       to a callback handler on the offhand item.
    //
    //       For example, if a player attempts to
    //       place a faulty door, the door implementation
    //       should be the one to reject it, not the tool's.

    if (is_item_tool_mode_a__combat_mode(p_item_self)) {
        m_item_use_handler__weapon(
                p_item_self, 
                p_entity_user, 
                p_game_action, 
                p_game);
        return;
    }

    // TODO: replace with get_p_tile_thats__infront_of_this__entity 
    Vector__3i32F4 vector_front__3i32F4;
    Tile *p_tile =
        get_p_tile_and_vector_3i32F4_thats__infront_of_this__entity(
                get_p_world_from__game(p_game), 
                p_entity_user,
                &vector_front__3i32F4);

    if (!p_tile)
        return;

    if (use_hammer__place_offhand(
                p_game,
                p_item_self, 
                p_item_stack__offhand, 
                p_tile,
                vector_front__3i32F4)) {
        remove_quantity_of_items_from__item_stack(
                p_item_stack__offhand, 
                1);
    }

    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            get_p_chunk_manager_from__game(p_game));
}
