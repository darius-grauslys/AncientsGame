#include "inventory/implemented/hatchet__iron/hatchet__iron.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "game.h"
#include "inventory/implemented/tool.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "inventory/implemented/weapon.h"
#include "numerics.h"
#include "platform.h"
#include "world/chunk_manager.h"
#include "world/chunk_vectors.h"

void register_into__item_manager__hatchet__iron_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Hatchet__Iron, 
            get_item(
                Item_Kind__Hatchet__Iron, 
                ITEM_USAGE_FLAG__IS_LABOR
                | ITEM_USAGE_FLAG__IS_LABOR__SECONDARY
                | ITEM_USAGE_FLAG__IS_COMBAT,
                ITEM_FILTER_FLAGS__NONE, 
                i32_to__i32F20(4), 
                m_item_use_handler__hatchet__iron, 
                0, 
                0));
}

void m_item_use_handler__hatchet__iron(
        Item *p_item_self,
        Entity *p_entity_user,
        Game_Action *p_game_action,
        Game *p_game) {
    Chunk_Vector__3i32 chunk_vector =
        vector_3i32F4_to__chunk_vector_3i32(
                get_vector_3i32F4_from__entity(p_entity_user));
    Chunk_Manager__Chunk_Map_Node *p_chunk_node =
        get_p_chunk_map_node_from__chunk_manager_using__i32(
                get_p_chunk_manager_from__game(p_game), 
                chunk_vector.x__i32, 
                chunk_vector.y__i32, 
                chunk_vector.z__i32);

    Vector__3i32F4 offset =
        get_2i32F4_offset_from__angle(
            get_angle_from__direction(
                p_entity_user->direction));
    offset.x__i32F4 <<= 4;
    offset.y__i32F4 <<= 4;
    Vector__3i32F4 position =
        add_vectors__3i32F4(
                get_vector_3i32F4_from__entity(p_entity_user), 
                offset);
    Tile *p_tile =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__game(p_game), 
                position);

    use_tool__harvest_tree(
            p_game, 
            p_entity_user, 
            p_tile);

    PLATFORM_update_chunk(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            get_p_chunk_manager_from__game(p_game), 
            p_chunk_node);
}
