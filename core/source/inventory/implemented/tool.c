#include "defines_weak.h"
#include "entity/entity.h"
#include "entity/humanoid.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item_manager.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include <inventory/implemented/tool.h>
#include <defines.h>
#include <game_util.h>

void use_tool__harvest_soil(
        Game *p_game,
        Entity *p_entity_user,
        bool is_harvesting_wall_or__ground) {
    Tile_Vector__3i32 tile_vector__3i32 =
        get_tile_vector_thats__infront_of_this__entity(
                p_entity_user);

    Tile *p_tile = get_p_tile_from__chunk_manager_with__tile_vector_3i32(
            get_p_chunk_manager_from__game(p_game), 
            tile_vector__3i32);

    Item_Kind the_kind_of__item_harvested =
        Item_Kind__None;

    if (is_harvesting_wall_or__ground) {
        switch (get_tile_cover_kind_from__tile(p_tile)) {
            default:
                return;
            case Tile_Cover_Kind__Wall__Dirt:
                the_kind_of__item_harvested =
                    Item_Kind__Pile__Dirt__Plenty;
                break;
            case Tile_Cover_Kind__Wall__Sand:
                the_kind_of__item_harvested =
                    Item_Kind__Pile__Sand__Plenty;
                break;
        }
        set_tile_cover_kind_of__tile(
                p_tile, 
                Tile_Cover_Kind__None);
        set_tile__is_unpassable(
                p_tile, 
                false);
    } else {
        switch (get_tile_kind_from__tile(p_tile)) {
            default:
                return;
            case Tile_Kind__Dirt:
                the_kind_of__item_harvested =
                    Item_Kind__Pile__Dirt__Plenty;
                break;
            case Tile_Kind__Sand:
                the_kind_of__item_harvested =
                    Item_Kind__Pile__Sand__Plenty;
                break;
        }
        set_tile_kind_of__tile(
                p_tile, 
                Tile_Kind__None);
        set_tile__is_unpassable(
                p_tile,
                true);
    }

    humanoid__add_item_to__inventory(
            p_game, 
            p_entity_user, 
            get_item_from__item_manager(
                get_p_item_manager_from__game(p_game), 
                the_kind_of__item_harvested), 
            1,
            128); // TODO: magic numbers

    update_chunk_at__tile_vector__3i32(
            p_game, 
            tile_vector__3i32);
}

bool use_tool__harvest_ore__cover(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile) {
    Item resource;
    Quantity__u8 quantity_of__items = 1;
    switch (p_tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            return false;
        case Tile_Cover_Kind__Ore__Large__Stone_1__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Stone_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Top_Right:
            // TODO: big ore
            // if (p_tile__other)
            //     clear_tile_cover(p_tile__other);
            quantity_of__items = 8;
        case Tile_Cover_Kind__Ore__Small__Stone_1:
        case Tile_Cover_Kind__Ore__Small__Stone_2:
        case Tile_Cover_Kind__Ore__Small__Stone_3:
        case Tile_Cover_Kind__Wall__Stone:
            resource = 
                get_item_from__item_manager(
                    get_p_item_manager_from__game(p_game), 
                    Item_Kind__Pile__Stone__Plenty);
            break;
        // TODO: add coal.
        case Tile_Cover_Kind__Ore__Large__Gold_1__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Gold_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Top_Right:
            // TODO: big ore
            // if (p_tile__other)
            //     clear_tile_cover(p_tile__other);
            quantity_of__items = 8;
        case Tile_Cover_Kind__Ore__Small__Gold_1:
        case Tile_Cover_Kind__Ore__Small__Gold_2:
        case Tile_Cover_Kind__Ore__Small__Gold_3:
        case Tile_Cover_Kind__Wall__Gold:
            resource = 
                get_item_from__item_manager(
                    get_p_item_manager_from__game(p_game), 
                    Item_Kind__Pile__Gold__Plenty);
            break;
        case Tile_Cover_Kind__Ore__Large__Iron_1__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Iron_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Top_Right:
            // TODO: big ore
            // if (p_tile__other)
            //     clear_tile_cover(p_tile__other);
            quantity_of__items = 8;
        case Tile_Cover_Kind__Ore__Small__Iron_1:
        case Tile_Cover_Kind__Ore__Small__Iron_2:
        case Tile_Cover_Kind__Ore__Small__Iron_3:
        case Tile_Cover_Kind__Wall__Iron:
            resource = 
                get_item_from__item_manager(
                    get_p_item_manager_from__game(p_game), 
                    Item_Kind__Pile__Iron__Plenty);
            break;
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Top_Right:
            // TODO: big ore
            // if (p_tile__other)
            //     clear_tile_cover(p_tile__other);
            quantity_of__items = 8;
        case Tile_Cover_Kind__Ore__Small__Diamond_1:
        case Tile_Cover_Kind__Ore__Small__Diamond_2:
        case Tile_Cover_Kind__Ore__Small__Diamond_3:
        case Tile_Cover_Kind__Wall__Diamond:
            resource = 
                get_item_from__item_manager(
                    get_p_item_manager_from__game(p_game), 
                    Item_Kind__Pile__Diamond__Plenty);
            break;
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Top_Right:
            // TODO: big ore
            // if (p_tile__other)
            //     clear_tile_cover(p_tile__other);
            quantity_of__items = 8;
        case Tile_Cover_Kind__Ore__Small__Amethyst_1:
        case Tile_Cover_Kind__Ore__Small__Amethyst_2:
        case Tile_Cover_Kind__Ore__Small__Amethyst_3:
        case Tile_Cover_Kind__Wall__Amethyst:
            resource = 
                get_item_from__item_manager(
                    get_p_item_manager_from__game(p_game), 
                    Item_Kind__Pile__Amethyst__Plenty);
            break;
    }
    humanoid__add_item_to__inventory(
            p_game, 
            p_entity_user, 
            resource, 
            quantity_of__items, 
            128); //TODO: magic number, item max
    set_tile_cover_kind_of__tile(
            p_tile, 
            Tile_Cover_Kind__None);
    set_tile__is_unpassable( //TODO: passability rules
            p_tile,
            false);
    return true;
}

bool use_tool__harvest_ore__ground(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile) {
    Item_Kind the_kind_of__resource =
        Item_Kind__None;
    switch (get_tile_kind_from__tile(p_tile)) {
        default:
            return false;
        case Tile_Kind__Stone:
            the_kind_of__resource =
                Item_Kind__Pile__Stone__Plenty;
            break;
        case Tile_Kind__Stone_Brick:
            the_kind_of__resource =
                Item_Kind__Pile__Stone_Brick__Plenty;
            break;
        case Tile_Kind__Sandstone:
            the_kind_of__resource =
                Item_Kind__Pile__Sandstone__Plenty;
            break;
        case Tile_Kind__Iron:
            the_kind_of__resource =
                Item_Kind__Pile__Iron__Plenty;
            break;
        case Tile_Kind__Gold:
            the_kind_of__resource =
                Item_Kind__Pile__Gold__Plenty;
            break;
        case Tile_Kind__Amethyst:
            the_kind_of__resource =
                Item_Kind__Pile__Amethyst__Plenty;
            break;
        case Tile_Kind__Diamond:
            the_kind_of__resource =
                Item_Kind__Pile__Diamond__Plenty;
            break;
    }
    humanoid__add_item_to__inventory(
            p_game, 
            p_entity_user, 
            get_item_from__item_manager(
                get_p_item_manager_from__game(p_game), 
                the_kind_of__resource), 
            1, 
            128); //TODO: magic number, item max
    set_tile_kind_of__tile(
            p_tile, 
            Tile_Kind__None);
    set_tile__is_unpassable(
            p_tile,
            true);
    return true;
}

void use_tool__harvest_ore(
        Game *p_game,
        Entity *p_entity_user,
        bool is_harvesting_wall_or__ground) {
    Tile *p_tile = 
        get_p_tile_thats__infront_of__this_entity(
                p_game, 
                p_entity_user);

    if (is_harvesting_wall_or__ground) {
        if (!use_tool__harvest_ore__cover(
                p_game, 
                p_entity_user, 
                p_tile)) {
            return;
        }
        goto update_chunk;
    }

    if (!use_tool__harvest_ore__ground(
            p_game, 
            p_entity_user, 
            p_tile)) {
        return;
    }
update_chunk:
    update_chunk_at__tile_vector__3i32(
            p_game, 
            get_tile_vector_thats__infront_of_this__entity(
                p_entity_user));
}

void use_tool__harvest_tree(
        Game *p_game,
        Entity *p_entity_user) {
    Tile_Vector__3i32 tile_vector__3i32 =
        get_tile_vector_thats__infront_of_this__entity(
                p_entity_user);
    Tile *p_tile =
        get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                get_p_chunk_manager_from__game(p_game),
                tile_vector__3i32);

    Item resource = get_item_from__item_manager(
            get_p_item_manager_from__game(p_game), 
            Item_Kind__Pile__Wood__Plenty);
    Quantity__u8 quantity_of__items = 1;
    switch (p_tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            return;
        case Tile_Cover_Kind__Stump:
            break;
        case Tile_Cover_Kind__Tree__Oak:
        case Tile_Cover_Kind__Tree__Pine:
        case Tile_Cover_Kind__Wall__Oak_Wood:
            quantity_of__items = 8;
            break;
    }
    clear_tile_cover(p_tile);
    humanoid__add_item_to__inventory(
            p_game, 
            p_entity_user, 
            resource, 
            quantity_of__items, 
            128); //TODO: magic number, item max
    update_chunk_at__tile_vector__3i32(
            p_game, 
            tile_vector__3i32);
}
