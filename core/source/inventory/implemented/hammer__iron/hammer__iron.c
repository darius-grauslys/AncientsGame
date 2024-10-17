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

static inline
Tile_Cover_Kind use_hammer__verify_door_placement(
        Tile *p_tile__adjacent_one,
        Tile *p_tile__adjacent_two,
        Item_Kind the_kind_of__offhand_item,
        bool is_vertical_or__horizontal) {
    if (!p_tile__adjacent_one
            || !p_tile__adjacent_two) {
        return Tile_Cover_Kind__None;
    }

    if (!is_tiles_with__same_tile_cover(
                p_tile__adjacent_one, 
                p_tile__adjacent_two)) {
        return Tile_Cover_Kind__None;
    }

    switch (the_kind_of__offhand_item) {
        default:
            return false;
        case Item_Kind__Door__Wood:
            switch (get_tile_cover_kind_from__tile(
                        p_tile__adjacent_one)) {
                default:
                    return Tile_Cover_Kind__None;
                case Tile_Cover_Kind__Wall__Oak_Wood:
                    return 
                        (is_vertical_or__horizontal)
                        ? Tile_Cover_Kind__Door__Vertical__Wood
                        : Tile_Cover_Kind__Door__Horizontal__Wood
                        ;
                case Tile_Cover_Kind__Wall__Stone_Brick:
                    return 
                        (is_vertical_or__horizontal)
                        ? Tile_Cover_Kind__Door__Vertical__Stone_Brick
                        : Tile_Cover_Kind__Door__Horizontal__Stone_Brick
                        ;
                case Tile_Cover_Kind__Wall__Sandstone:
                    return 
                        (is_vertical_or__horizontal)
                        ? Tile_Cover_Kind__Door__Vertical__Sandstone
                        : Tile_Cover_Kind__Door__Horizontal__Sandstone
                        ;
                case Tile_Cover_Kind__Wall__Dirt:
                    return 
                        (is_vertical_or__horizontal)
                        ? Tile_Cover_Kind__Door__Vertical__Dirt
                        : Tile_Cover_Kind__Door__Horizontal__Dirt
                        ;
                case Tile_Cover_Kind__Wall__Sand:
                    return 
                        (is_vertical_or__horizontal)
                        ? Tile_Cover_Kind__Door__Vertical__Sand
                        : Tile_Cover_Kind__Door__Horizontal__Sand
                        ;
            }
            break;
        case Item_Kind__Door__Gold:
            if (is_tile_with__this_kind_of__tile_cover(
                    p_tile__adjacent_one, 
                    Tile_Cover_Kind__Wall__Gold)) {
                return 
                    (is_vertical_or__horizontal)
                    ? Tile_Cover_Kind__Door__Vertical__Gold
                    : Tile_Cover_Kind__Door__Horizontal__Gold
                    ;
            }
            break;
        case Item_Kind__Door__Diamond:
            if (is_tile_with__this_kind_of__tile_cover(
                    p_tile__adjacent_one, 
                    Tile_Cover_Kind__Wall__Diamond)) {
                return 
                    (is_vertical_or__horizontal)
                    ? Tile_Cover_Kind__Door__Vertical__Diamond
                    : Tile_Cover_Kind__Door__Horizontal__Diamond
                    ;
            }
            break;
        case Item_Kind__Door__Amethyst:
            if (is_tile_with__this_kind_of__tile_cover(
                    p_tile__adjacent_one, 
                    Tile_Cover_Kind__Wall__Amethyst)) {
                return 
                    (is_vertical_or__horizontal)
                    ? Tile_Cover_Kind__Door__Vertical__Amethyst
                    : Tile_Cover_Kind__Door__Horizontal__Amethyst
                    ;
            }
            break;
        case Item_Kind__Door__Iron:
            if (is_tile_with__this_kind_of__tile_cover(
                    p_tile__adjacent_one, 
                    Tile_Cover_Kind__Wall__Iron)) {
                return 
                    (is_vertical_or__horizontal)
                    ? Tile_Cover_Kind__Door__Vertical__Iron
                    : Tile_Cover_Kind__Door__Horizontal__Iron
                    ;
            }
            break;
    }
    return Tile_Cover_Kind__None;
}

bool use_hammer__set_tile_to__door_type_of__this_item(
        World *p_world,
        Tile *p_tile,
        Item_Kind the_kind_of__offhand_item,
        Vector__3i32F4 vector_front__3i32F4) {
    Tile *p_tile__south, *p_tile__north;

    p_tile__south =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32F4(
                    vector_front__3i32F4, 
                    get_vector__3i32F4_using__i32(
                        0, -8, 0)
                    ));
    p_tile__north =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32F4(
                    vector_front__3i32F4, 
                    get_vector__3i32F4_using__i32(
                        0, 8, 0)
                    ));
    
    Tile_Cover_Kind the_kind_of__door_placed =
        use_hammer__verify_door_placement(
                p_tile__south, 
                p_tile__north, 
                the_kind_of__offhand_item,
                true);
    if (the_kind_of__door_placed
            != Tile_Cover_Kind__None) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                the_kind_of__door_placed);
        set_tile__is_unpassable(
                p_tile, 
                true);
        return true;
    }

    Tile *p_tile__west, *p_tile__east;

    p_tile__west =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32F4(
                    vector_front__3i32F4, 
                    get_vector__3i32F4_using__i32(
                        -8, 0, 0)
                    ));
    p_tile__east =
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__world(p_world), 
                add_vectors__3i32F4(
                    vector_front__3i32F4, 
                    get_vector__3i32F4_using__i32(
                        8, 0, 0)
                    ));

    the_kind_of__door_placed =
        use_hammer__verify_door_placement(
                p_tile__west, 
                p_tile__east, 
                the_kind_of__offhand_item,
                false);
    if (the_kind_of__door_placed
            != Tile_Cover_Kind__None) {
        set_tile_cover_kind_of__tile(
                p_tile, 
                the_kind_of__door_placed);
        set_tile__is_unpassable(
                p_tile, 
                true);
        return true;
    }

    return false;
}

bool use_hammer__set_tile_to__cover_type_of__this_item(
        Game *p_game,
        Tile *p_tile,
        Item_Kind the_kind_of__offhand_item,
        Vector__3i32F4 vector_front__3i32F4) {
    if (!is_tile_with__this_kind_of__tile_cover(
                p_tile,
                Tile_Cover_Kind__None)) {
        return false;
    }
    switch (the_kind_of__offhand_item) {
        default:
            return false;
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
        case Item_Kind__Chest:
            ;
            Inventory *p_inventory =
                allocate_p_inventory_using__this_uuid_in__inventory_manager(
                        get_p_inventory_manager_from__game(p_game), 
                        get_uuid_for__container(
                            vector_3i32F4_to__tile_vector(
                                vector_front__3i32F4)));
            if (!p_inventory)
                return false;
            set_tile_cover_kind_of__tile(
                    p_tile, 
                    Tile_Cover_Kind__Chest__Single);
            break;
        case Item_Kind__Door__Wood:
        case Item_Kind__Door__Amethyst:
        case Item_Kind__Door__Diamond:
        case Item_Kind__Door__Gold:
        case Item_Kind__Door__Iron:
            return use_hammer__set_tile_to__door_type_of__this_item(
                    get_p_world_from__game(p_game),
                    p_tile,
                    the_kind_of__offhand_item,
                    vector_front__3i32F4);
            break;
    }
    return true;
}

bool use_hammer__set_tile_to__ground_type_of__this_item(
        Tile *p_tile,
        Item_Kind the_kind_of__offhand_item) {
    if (!is_tile_of__this_kind(
                p_tile, 
                Tile_Kind__None)) {
        return false;
    }
    switch (the_kind_of__offhand_item) {
        default:
            return false;
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

    // TODO: make a look up table in tile_logic_manager
    //      which will determine if a tile is passable or not.
    //      because currently if you place a wall, remove the ground
    //      underneath it, and then put the ground back, the wall
    //      is now passable.
    set_tile__is_unpassable(
            p_tile, 
            false);

    return true;
}

bool use_hammer__place_offhand(
        Game *p_game,
        Item *p_item_self,
        Item_Stack *p_item_stack__offhand,
        Tile *p_tile,
        Vector__3i32F4 vector_front__3i32F4) {
    Item_Kind the_kind_of__offhand_item =
        p_item_stack__offhand
        ->item.the_kind_of_item__this_item_is;

    if (is_item_tool_mode__labor(p_item_self)) {
        bool result__wall = 
            use_hammer__set_tile_to__cover_type_of__this_item(
                p_game,
                p_tile, 
                the_kind_of__offhand_item,
                vector_front__3i32F4);
        if (result__wall) {
            set_tile__is_unpassable(p_tile, true);
        }
        return result__wall;
    } else if (is_item_tool_mode__labor_secondary(p_item_self)) {
        return use_hammer__set_tile_to__ground_type_of__this_item(
                p_tile, 
                the_kind_of__offhand_item);
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
