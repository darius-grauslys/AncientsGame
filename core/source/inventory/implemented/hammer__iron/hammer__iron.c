#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "game.h"
#include "inventory/implemented/weapon.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "inventory/item_stack.h"
#include "numerics.h"
#include "platform.h"
#include "vectors.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
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

static inline
void use_hammer__set_tile_to__wall_type_of__this_item(
        Tile *p_tile,
        Item_Kind the_kind_of__offhand_item) {
    switch (the_kind_of__offhand_item) {
        default:
            return;
        case Item_Kind__Pile__Amethyst__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Amethyst;
            break;
        case Item_Kind__Pile__Diamond__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Diamond;
            break;
        case Item_Kind__Pile__Stone__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Stone;
            break;
        case Item_Kind__Pile__Iron__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Iron;
            break;
        case Item_Kind__Pile__Gold__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Gold;
            break;
        case Item_Kind__Pile__Stone_Brick__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Stone_Brick;
            break;
        case Item_Kind__Pile__Sand__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Sand;
            break;
        case Item_Kind__Pile__Dirt__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Dirt;
            break;
        case Item_Kind__Pile__Wood__Plenty:
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__Wall__Oak_Wood;
            break;
    }
}

static inline
void use_hammer__set_tile_to__ground_type_of__this_item(
        Tile *p_tile,
        Item_Kind the_kind_of__offhand_item) {
    switch (the_kind_of__offhand_item) {
        default:
            return;
        case Item_Kind__Pile__Amethyst__Plenty:
            p_tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Amethyst;
            break;
        case Item_Kind__Pile__Diamond__Plenty:
            p_tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Diamond;
            break;
        case Item_Kind__Pile__Stone__Plenty:
            p_tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Stone;
            break;
        case Item_Kind__Pile__Stone_Brick__Plenty:
            p_tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Stone_Brick;
            break;
        case Item_Kind__Pile__Sand__Plenty:
            p_tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Sand;
            break;
        case Item_Kind__Pile__Dirt__Plenty:
            p_tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Dirt;
            break;
        case Item_Kind__Pile__Wood__Plenty:
            p_tile->the_kind_of_tile__this_tile_is =
                Tile_Kind__Oak_Wood;
            break;
    }
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

    if (is_item_tool_mode__combat(p_item_self)
            || is_item_tool_mode__combat_lockon(p_item_self)) {
        m_item_use_handler__weapon(
                p_item_self, 
                p_entity_user, 
                p_game_action, 
                p_game);
        return;
    }

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

    if (!p_tile)
        return;

    Item_Kind the_kind_of__offhand_item =
        p_item_stack__offhand
        ->item.the_kind_of_item__this_item_is;

    if (is_item_tool_mode__labor(p_item_self)) {
        if (p_tile->the_kind_of_tile_cover__this_tile_has
                != Tile_Cover_Kind__None) {
            return;
        }

        use_hammer__set_tile_to__wall_type_of__this_item(
                p_tile, 
                the_kind_of__offhand_item);
        set_tile__is_unpassable(p_tile, true);
    } else if (is_item_tool_mode__labor_secondary(p_item_self)) {
        use_hammer__set_tile_to__ground_type_of__this_item(
                p_tile, 
                the_kind_of__offhand_item);
    }

    remove_quantity_of_items_from__item_stack(
            p_item_stack__offhand, 
            1);

    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            get_p_chunk_manager_from__game(p_game));
}
