#include "debug/debug.h"
#include "defines_weak.h"
#include "world/tile.h"
#include <world/tiles/tile__cover__ore.h>

void set_tile_cover_as__ore(
        Tile *p_tile,
        Tile *p_tile__right,
        enum Item_Kind the_kind_of__ore,
        u8 variation,
        bool is_large) {
    if (is_large && !p_tile__right) {
        debug_error("set_tile_cover_as__ore, p_tile__right cannot be null for large ores.");
        return;
    }
    enum Tile_Cover_Kind the_kind_of__tile_cover_for__ore =
        Tile_Cover_Kind__Ore__Small__Stone_1;
    switch (the_kind_of__ore) {
        default:
            debug_warning__verbose(
                    "set_tile_cover_as__ore, unrecognized: the_kind_of__ore, %d",
                    the_kind_of__ore);
        case Item_Kind__Pile__Stone:
            the_kind_of__tile_cover_for__ore =
                (is_large)
                ? Tile_Cover_Kind__Ore__Large__Stone_1__Top_Left
                : Tile_Cover_Kind__Ore__Small__Stone_1
                ;
            break;
        case Item_Kind__Bag_Of__Coal:
            the_kind_of__tile_cover_for__ore =
                (is_large)
                ? Tile_Cover_Kind__Ore__Large__Stone_1__Top_Left
                : Tile_Cover_Kind__Ore__Small__Stone_1
                ; // TODO: make coal.
            break;
        case Item_Kind__Pile__Amethyst:
            the_kind_of__tile_cover_for__ore =
                (is_large)
                ? Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Left
                : Tile_Cover_Kind__Ore__Small__Amethyst_1
                ;
            break;
        case Item_Kind__Pile__Diamond:
            the_kind_of__tile_cover_for__ore =
                (is_large)
                ? Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Left
                : Tile_Cover_Kind__Ore__Small__Diamond_1
                ;
            break;
        case Item_Kind__Pile__Gold:
            the_kind_of__tile_cover_for__ore =
                (is_large)
                ? Tile_Cover_Kind__Ore__Large__Gold_1__Top_Left
                : Tile_Cover_Kind__Ore__Small__Gold_1
                ;
            break;
        case Item_Kind__Pile__Iron:
            the_kind_of__tile_cover_for__ore =
                (is_large)
                ? Tile_Cover_Kind__Ore__Large__Iron_1__Top_Left
                : Tile_Cover_Kind__Ore__Small__Iron_1
                ;
            break;
    }

    set_tile__is_unpassable(p_tile, true);

    if (is_large) {
        variation %= 2; //TODO: magic num, number of large ore variants.
        the_kind_of__tile_cover_for__ore += variation * 2;

        p_tile->the_kind_of_tile_cover__this_tile_has =
            the_kind_of__tile_cover_for__ore;
        p_tile__right->the_kind_of_tile_cover__this_tile_has =
            the_kind_of__tile_cover_for__ore + 1;

        set_tile__is_unpassable(p_tile__right, true);

        return;
    }

    variation %= 3; //TODO: magic num, number of small ore variants.
    the_kind_of__tile_cover_for__ore += variation;

    p_tile->the_kind_of_tile_cover__this_tile_has =
        the_kind_of__tile_cover_for__ore;
}
