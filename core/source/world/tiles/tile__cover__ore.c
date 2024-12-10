#include "debug/debug.h"
#include "defines_weak.h"
#include "game.h"
#include "world/chunk_manager.h"
#include "world/tile.h"
#include "world/tile_logic_manager.h"
#include "world/tile_logic_record.h"
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

bool f_tile_handler__destroy__ore(
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    Tile *p_tile__left;
    Tile *p_tile__right;
    switch (the_kind_of__tile_cover) {
        default:
            return false;
        case Tile_Cover_Kind__Ore__Large__Stone_1__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Gold_1__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Iron_1__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Coal_1__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Bottom_Left:
        case Tile_Cover_Kind__Ore__Large__Coal_2__Bottom_Left:
            p_tile__left = p_tile;
            p_tile__right =
                get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                        get_p_chunk_manager_from__game(p_game), 
                        add_vectors__3i32(
                            tile_vector__3i32,
                            VECTOR__3i32__1_0_0));
            break;
        case Tile_Cover_Kind__Ore__Large__Stone_1__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Gold_1__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Iron_1__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Coal_1__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Bottom_Right:
        case Tile_Cover_Kind__Ore__Large__Coal_2__Bottom_Right:
            p_tile__right = p_tile;
            p_tile__left =
                get_p_tile_from__chunk_manager_with__tile_vector_3i32(
                        get_p_chunk_manager_from__game(p_game), 
                        add_vectors__3i32(
                            tile_vector__3i32,
                            VECTOR__3i32__n1_0_0));
            break;
        case Tile_Cover_Kind__Ore__Small__Stone_1:
        case Tile_Cover_Kind__Ore__Small__Stone_2:
        case Tile_Cover_Kind__Ore__Small__Stone_3:
        case Tile_Cover_Kind__Ore__Small__Amethyst_1:
        case Tile_Cover_Kind__Ore__Small__Amethyst_2:
        case Tile_Cover_Kind__Ore__Small__Amethyst_3:
        case Tile_Cover_Kind__Ore__Small__Diamond_1:
        case Tile_Cover_Kind__Ore__Small__Diamond_2:
        case Tile_Cover_Kind__Ore__Small__Diamond_3:
        case Tile_Cover_Kind__Ore__Small__Gold_1:
        case Tile_Cover_Kind__Ore__Small__Gold_2:
        case Tile_Cover_Kind__Ore__Small__Gold_3:
        case Tile_Cover_Kind__Ore__Small__Iron_1:
        case Tile_Cover_Kind__Ore__Small__Iron_2:
        case Tile_Cover_Kind__Ore__Small__Iron_3:
        case Tile_Cover_Kind__Ore__Small__Coal_1:
        case Tile_Cover_Kind__Ore__Small__Coal_2:
        case Tile_Cover_Kind__Ore__Small__Coal_3:
            clear_tile_cover(p_tile);
            return true;
    }

    if (!p_tile__left || !p_tile__right) {
        return false;
    }

    clear_tile_cover(p_tile__left);
    clear_tile_cover(p_tile__right);

    return true;
}

static inline
void register_default_tile_handlers_for__ore(
        Tile_Logic_Manager *p_tile_logic_manager,
        Tile_Cover_Kind the_kind_of__ore,
        Item_Kind the_kind_of__resource,
        Quantity__u32 quantity_of__resource) {
    register_tile_logic_record_for__cover_kind(
            p_tile_logic_manager, 
            the_kind_of__ore, 
            TILE_LOGIC_RECORD(
                0,
                0,
                0,
                f_tile_handler__destroy__ore,
                TILE_LOGIC_FLAG__IS_UNPASSABLE,
                Tool_Kind__Pickaxe,
                the_kind_of__resource,
                quantity_of__resource));
}

void register_tile_handlers_for__ore(
        Tile_Logic_Manager *p_tile_logic_manager) {
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Stone_1__Bottom_Left,
            Item_Kind__Pile__Stone__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Stone_1__Bottom_Right,
            Item_Kind__Pile__Amethyst__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Amethyst_1__Bottom_Left,
            Item_Kind__Pile__Amethyst__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Amethyst_1__Bottom_Right,
            Item_Kind__Pile__Amethyst__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Diamond_1__Bottom_Left,
            Item_Kind__Pile__Diamond__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Diamond_1__Bottom_Right,
            Item_Kind__Pile__Diamond__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Gold_1__Bottom_Left,
            Item_Kind__Pile__Gold__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Gold_1__Bottom_Right,
            Item_Kind__Pile__Gold__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Iron_1__Bottom_Left,
            Item_Kind__Pile__Iron__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Iron_1__Bottom_Right,
            Item_Kind__Pile__Iron__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Coal_1__Bottom_Left,
            Item_Kind__Pile__Iron__Plenty, //TODO: coal item_kind
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Coal_1__Bottom_Right,
            Item_Kind__Pile__Iron__Plenty, //TODO: coal item_kind
            8);




    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Stone_2__Bottom_Left,
            Item_Kind__Pile__Stone__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Stone_2__Bottom_Right,
            Item_Kind__Pile__Stone__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Amethyst_2__Bottom_Left,
            Item_Kind__Pile__Amethyst__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Amethyst_2__Bottom_Right,
            Item_Kind__Pile__Amethyst__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Diamond_2__Bottom_Left,
            Item_Kind__Pile__Diamond__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Diamond_2__Bottom_Right,
            Item_Kind__Pile__Diamond__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Gold_2__Bottom_Left,
            Item_Kind__Pile__Gold__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Gold_2__Bottom_Right,
            Item_Kind__Pile__Gold__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Iron_2__Bottom_Left,
            Item_Kind__Pile__Iron__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Iron_2__Bottom_Right,
            Item_Kind__Pile__Iron__Plenty,
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Coal_2__Bottom_Left,
            Item_Kind__Pile__Iron__Plenty, // TODO: coal item_kind
            8);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Large__Coal_2__Bottom_Right,
            Item_Kind__Pile__Iron__Plenty, // TODO: coal item_kind
            8);





    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Stone_1,
            Item_Kind__Pile__Stone__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Stone_2,
            Item_Kind__Pile__Stone__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Stone_3,
            Item_Kind__Pile__Stone__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Amethyst_1,
            Item_Kind__Pile__Amethyst__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Amethyst_2,
            Item_Kind__Pile__Amethyst__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Amethyst_3,
            Item_Kind__Pile__Amethyst__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Diamond_1,
            Item_Kind__Pile__Diamond__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Diamond_2,
            Item_Kind__Pile__Diamond__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Diamond_3,
            Item_Kind__Pile__Diamond__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Gold_1,
            Item_Kind__Pile__Gold__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Gold_2,
            Item_Kind__Pile__Gold__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Gold_3,
            Item_Kind__Pile__Gold__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Iron_1,
            Item_Kind__Pile__Iron__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Iron_2,
            Item_Kind__Pile__Iron__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Iron_3,
            Item_Kind__Pile__Iron__Plenty,
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Coal_1,
            Item_Kind__Pile__Iron__Plenty, //TODO: coal item_kind
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Coal_2,
            Item_Kind__Pile__Iron__Plenty, //TODO: coal item_kind
            1);
    register_default_tile_handlers_for__ore(
            p_tile_logic_manager, 
            Tile_Cover_Kind__Ore__Small__Coal_3,
            Item_Kind__Pile__Iron__Plenty, //TODO: coal item_kind
            1);
}
