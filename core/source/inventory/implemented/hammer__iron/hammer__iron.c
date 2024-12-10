#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "entity/humanoid.h"
#include "game.h"
#include "inventory/implemented/weapon.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/implemented/tool.h"
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
#include "game_util.h"

void register_into__item_manager__hammer__iron_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Hammer__Iron, 
            get_tool(
                Item_Kind__Hammer__Iron, 
                ITEM_USAGE_FLAG__IS_LABOR
                | ITEM_USAGE_FLAG__IS_LABOR__SECONDARY
                | ITEM_USAGE_FLAG__IS_COMBAT,
                i32_to__i32F20(4), 
                Tool_Kind__Hammer, 
                m_item_use_handler__hammer, 
                0, 
                0));
}

bool use_hammer__place_offhand(
        Game *p_game,
        Item *p_item_self,
        Item_Stack *p_item_stack__offhand,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile = 
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    if (!p_tile)
        return false;

    bool is_placing__ground_or_cover =
        get_tool_mode_of__item(p_item_self)
        == Tool_Mode__Labor_Secondary;
    return attempt_tile_placement(
            p_game,
            is_placing__ground_or_cover
            ? p_item_stack__offhand
                ->item
                .the_kind_of__ground__this_item_builds
            : Tile_Kind__None,
            p_item_stack__offhand
                ->item
                .the_kind_of__tile_cover__this_item_builds,
            tile_vector__3i32);
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

    Tile_Vector__3i32 tile_vector__3i32 =
        get_tile_vector_thats__infront_of_this__entity(
                p_entity_user);

    if (use_hammer__place_offhand(
                p_game,
                p_item_self, 
                p_item_stack__offhand, 
                tile_vector__3i32)) {
        humanoid__remove_quantity_of__item_kinds_from__posessions(
                p_game,
                p_entity_user,
                get_item_kind_of__item_stack(p_item_stack__offhand), 
                1);

        update_chunk_at__tile_vector__3i32(
                p_game, 
                tile_vector__3i32);
    }
}
