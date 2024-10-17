#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item_manager.h"
#include "world/tile.h"
#include <inventory/implemented/tool.h>
#include <defines.h>

void use_tool__harvest_soil(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile,
        bool is_harvesting_wall_or__ground) {
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
        goto add_harvest_item_to__inventory;
    }

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
add_harvest_item_to__inventory:
    ;
    Inventory *p_inventory =
        resolve_s_inventory(
                p_game, 
                &p_entity_user
                ->s_humanoid__inventory_ptr);

    if (!p_inventory)
        return;

    add_item_to__inventory(
            p_inventory, 
            get_item_from__item_manager(
                get_p_item_manager_from__game(p_game), 
                the_kind_of__item_harvested), 
            1, 
            128); // TODO: magic numbers
}

bool use_tool__harvest_ore__cover(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile,
        Tile *p_tile__other) {
    Item resource;
    Quantity__u8 quantity_of__items = 1;
    switch (p_tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            return false;
        case Tile_Cover_Kind__Ore__Large__Stone_1__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Stone_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Top_Left:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Top_Right:
            if (p_tile__other)
                clear_tile_cover(p_tile__other);
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
            if (p_tile__other)
                clear_tile_cover(p_tile__other);
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
            if (p_tile__other)
                clear_tile_cover(p_tile__other);
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
            if (p_tile__other)
                clear_tile_cover(p_tile__other);
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
            if (p_tile__other)
                clear_tile_cover(p_tile__other);
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
    Inventory *p_inventory =
        resolve_s_inventory(
                p_game,
                &p_entity_user
                ->s_humanoid__inventory_ptr);
    if (!p_inventory)
        return true;
    add_item_to__inventory(
            p_inventory,
            resource,
            quantity_of__items, 
            128); //TODO: magic number, item max
    set_tile_cover_kind_of__tile(
            p_tile, 
            Tile_Cover_Kind__None);
    set_tile__is_unpassable(
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
    Inventory *p_inventory =
        resolve_s_inventory(
                p_game,
                &p_entity_user
                ->s_humanoid__inventory_ptr);
    if (!p_inventory)
        return true;
    add_item_to__inventory(
            p_inventory,
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
        Tile *p_tile,
        Tile *p_tile__other,
        bool is_harvesting_wall_or__ground) {
    if (is_harvesting_wall_or__ground) {
        use_tool__harvest_ore__cover(
                p_game, 
                p_entity_user, 
                p_tile, 
                p_tile__other);
        return;
    }

    use_tool__harvest_ore__ground(
            p_game, 
            p_entity_user, 
            p_tile);
}

void use_tool__harvest_tree(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile) {
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
    add_item_to__inventory(
            p_entity_user->s_humanoid__inventory_ptr
                .p_serialized_field__inventory, 
            resource,
            quantity_of__items, 
            128); //TODO: magic number, item max
    clear_tile_cover(p_tile);
}
