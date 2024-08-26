#include "defines_weak.h"
#include "game.h"
#include "inventory/inventory.h"
#include "inventory/item_manager.h"
#include "world/tile.h"
#include <inventory/implemented/tool.h>
#include <defines.h>

void use_tool__harvest_ore(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile,
        Tile *p_tile__other) {
    Item resource;
    Quantity__u8 quantity_of__items = 1;
    switch (p_tile->the_kind_of_tile_cover__this_tile_has) {
        default:
            return;
        case Tile_Cover_Kind__Ore__Large__Stone_1__Left:
        case Tile_Cover_Kind__Ore__Large__Stone_1__Right:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Left:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Right:
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
        case Tile_Cover_Kind__Ore__Large__Gold_1__Left:
        case Tile_Cover_Kind__Ore__Large__Gold_1__Right:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Left:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Right:
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
        case Tile_Cover_Kind__Ore__Large__Iron_1__Left:
        case Tile_Cover_Kind__Ore__Large__Iron_1__Right:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Left:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Right:
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
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Left:
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Left:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Right:
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
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Left:
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Left:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Right:
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
    add_item_to__inventory(
            p_entity_user->s_humanoid__inventory_ptr
                .p_serialized_field__inventory, 
            resource,
            quantity_of__items, 
            128); //TODO: magic number, item max
    clear_tile_cover(p_tile);
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
