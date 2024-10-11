#include "defines_weak.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include "vectors.h"
#include "world/tiles/tile__cover__ore.h"
#include "world/tiles/tile__cover__tree.h"
#include "world/world.h"
#include <defines.h>
#include <world/generators/generator_flat_world.h>
#include <world/world_parameters.h>
#include <game.h>

#include <debug/debug.h>

#include <world/tile.h>

typedef struct Local_Parameters_t {
    Psuedo_Random__u32 random_result__greater__u32;
    Psuedo_Random__u32 random_result__local__u32;
} Local_Parameters;

typedef struct Weight_Matrix_t {
    Quantity__u8 A, B, C;
    Quantity__u8 D, E, F;
    Quantity__u8 G, H, I;
} Weight_Matrix;

typedef struct Weight_Map_t {
    Weight_Matrix map[CHUNK_QUANTITY_OF__TILES];
} Weight_Map;

Weight_Map weight_map;

void flip_xy__weight_matrix(
        Weight_Matrix *p_source, Weight_Matrix *p_dest) {
    p_dest->E = p_source->E;

    p_dest->A = p_source->I;
    p_dest->B = p_source->H;
    p_dest->C = p_source->G;

    p_dest->F = p_source->D;
    p_dest->I = p_source->A;

    p_dest->H = p_source->B;
    p_dest->G = p_source->C;

    p_dest->D = p_source->F;
}

void flip_y__weight_matrix(
        Weight_Matrix *p_source, Weight_Matrix *p_dest) {
    p_dest->E = p_source->E;

    p_dest->A = p_source->C;
    p_dest->B = p_source->B;
    p_dest->C = p_source->A;

    p_dest->F = p_source->D;
    p_dest->I = p_source->G;

    p_dest->H = p_source->H;
    p_dest->G = p_source->I;

    p_dest->D = p_source->F;
}

void flip_x__weight_matrix(
        Weight_Matrix *p_source, Weight_Matrix *p_dest) {
    p_dest->E = p_source->E;

    p_dest->A = p_source->G;
    p_dest->B = p_source->H;
    p_dest->C = p_source->I;

    p_dest->F = p_source->F;
    p_dest->I = p_source->C;

    p_dest->H = p_source->B;
    p_dest->G = p_source->A;

    p_dest->D = p_source->D;
}

void initialize_weight_map(void) {
    weight_map.map[0].A = 6;
    weight_map.map[0].B = 4;
    weight_map.map[0].C = 3;

    weight_map.map[0].D = 3;
    weight_map.map[0].E = 7;
    weight_map.map[0].F = 2;

    weight_map.map[0].G = 3;
    weight_map.map[0].H = 2;
    weight_map.map[0].I = 1;
    


    weight_map.map[1].A = 6;
    weight_map.map[1].B = 5;
    weight_map.map[1].C = 3;

    weight_map.map[1].D = 4;
    weight_map.map[1].E = 7;
    weight_map.map[1].F = 2;

    weight_map.map[1].G = 2;
    weight_map.map[1].H = 2;
    weight_map.map[1].I = 1;



    weight_map.map[2].A = 5;
    weight_map.map[2].B = 6;
    weight_map.map[2].C = 4;

    weight_map.map[2].D = 3;
    weight_map.map[2].E = 7;
    weight_map.map[2].F = 2;

    weight_map.map[2].G = 2;
    weight_map.map[2].H = 2;
    weight_map.map[2].I = 1;



    weight_map.map[3].A = 4;
    weight_map.map[3].B = 6;
    weight_map.map[3].C = 4;

    weight_map.map[3].D = 3;
    weight_map.map[3].E = 7;
    weight_map.map[3].F = 3;

    weight_map.map[3].G = 2;
    weight_map.map[3].H = 2;
    weight_map.map[3].I = 1;



    weight_map.map[8].A = 6;
    weight_map.map[8].B = 4;
    weight_map.map[8].C = 2;

    weight_map.map[8].D = 5;
    weight_map.map[8].E = 7;
    weight_map.map[8].F = 2;

    weight_map.map[8].G = 3;
    weight_map.map[8].H = 2;
    weight_map.map[8].I = 1;



    weight_map.map[9].A = 5;
    weight_map.map[9].B = 4;
    weight_map.map[9].C = 3;

    weight_map.map[9].D = 4;
    weight_map.map[9].E = 8;
    weight_map.map[9].F = 2;

    weight_map.map[9].G = 3;
    weight_map.map[9].H = 2;
    weight_map.map[9].I = 1;



    weight_map.map[10].A = 4;
    weight_map.map[10].B = 4;
    weight_map.map[10].C = 4;

    weight_map.map[10].D = 3;
    weight_map.map[10].E = 9;
    weight_map.map[10].F = 2;

    weight_map.map[10].G = 3;
    weight_map.map[10].H = 2;
    weight_map.map[10].I = 1;



    weight_map.map[11].A = 4;
    weight_map.map[11].B = 4;
    weight_map.map[11].C = 3;

    weight_map.map[11].D = 3;
    weight_map.map[11].E = 10;
    weight_map.map[11].F = 2;

    weight_map.map[11].G = 3;
    weight_map.map[11].H = 2;
    weight_map.map[11].I = 1;



    weight_map.map[16].A = 5;
    weight_map.map[16].B = 3;
    weight_map.map[16].C = 2;

    weight_map.map[16].D = 6;
    weight_map.map[16].E = 7;
    weight_map.map[16].F = 2;

    weight_map.map[16].G = 4;
    weight_map.map[16].H = 2;
    weight_map.map[16].I = 1;



    weight_map.map[17].A = 4;
    weight_map.map[17].B = 3;
    weight_map.map[17].C = 3;

    weight_map.map[17].D = 4;
    weight_map.map[17].E = 9;
    weight_map.map[17].F = 2;

    weight_map.map[17].G = 4;
    weight_map.map[17].H = 2;
    weight_map.map[17].I = 1;



    weight_map.map[18].A = 4;
    weight_map.map[18].B = 3;
    weight_map.map[18].C = 3;

    weight_map.map[18].D = 3;
    weight_map.map[18].E = 11;
    weight_map.map[18].F = 2;

    weight_map.map[18].G = 3;
    weight_map.map[18].H = 2;
    weight_map.map[18].I = 1;



    weight_map.map[19].A = 3;
    weight_map.map[19].B = 4;
    weight_map.map[19].C = 3;

    weight_map.map[19].D = 3;
    weight_map.map[19].E = 11;
    weight_map.map[19].F = 2;

    weight_map.map[19].G = 3;
    weight_map.map[19].H = 2;
    weight_map.map[19].I = 1;



    weight_map.map[24].A = 4;
    weight_map.map[24].B = 3;
    weight_map.map[24].C = 1;

    weight_map.map[24].D = 6;
    weight_map.map[24].E = 7;
    weight_map.map[24].F = 2;

    weight_map.map[24].G = 4;
    weight_map.map[24].H = 3;
    weight_map.map[24].I = 2;



    weight_map.map[25].A = 4;
    weight_map.map[25].B = 3;
    weight_map.map[25].C = 3;

    weight_map.map[25].D = 4;
    weight_map.map[25].E = 10;
    weight_map.map[25].F = 2;

    weight_map.map[25].G = 3;
    weight_map.map[25].H = 2;
    weight_map.map[25].I = 1;



    weight_map.map[26].A = 3;
    weight_map.map[26].B = 3;
    weight_map.map[26].C = 3;

    weight_map.map[26].D = 4;
    weight_map.map[26].E = 11;
    weight_map.map[26].F = 2;

    weight_map.map[26].G = 3;
    weight_map.map[26].H = 2;
    weight_map.map[26].I = 1;



    weight_map.map[27].A = 3;
    weight_map.map[27].B = 3;
    weight_map.map[27].C = 2;

    weight_map.map[27].D = 3;
    weight_map.map[27].E = 13;
    weight_map.map[27].F = 2;

    weight_map.map[27].G = 2;
    weight_map.map[27].H = 2;
    weight_map.map[27].I = 2;

    // for (uint32_t y=0;y<8;y++) {
    //     if (y >= 4) continue;
    //     for (uint32_t x=0;x<8;x++) {
    //         if (x < 4) continue;
    //         flip_x__weight_matrix(
    //                 &weight_map.map[(y%4) * 8 + (x%4)],
    //                 &weight_map.map[y*8+x]);
    //         // weight_map.map[y * 8 + x] =
    //         //     weight_map.map[(y%4) * 8 + (x%4)];
    //     }
    // }

    // return;

    //TODO: magic numbers
    for (uint32_t y=0; y<4;y++) {
        for (uint32_t x=0; x<4;x++) {
            flip_y__weight_matrix(
                    &weight_map.map[x + (8*y)], 
                    &weight_map.map[7 - x + (8*y)]);
        }
    }
    for (uint32_t y=0; y<4;y++) {
        for (uint32_t x=0; x<4;x++) {
            flip_x__weight_matrix(
                    &weight_map.map[x + (8*y)], 
                    &weight_map.map[x + (8*(7-y))]);
        }
    }
    for (uint32_t y=0; y<4;y++) {
        for (uint32_t x=0; x<4;x++) {
            flip_xy__weight_matrix(
                    &weight_map.map[x + (8*y)], 
                    &weight_map.map[7 - x + (8*(7-y))]);
        }
    }
}

enum Item_Kind loot_table__wood[] = {
    Item_Kind__Stick,
    Item_Kind__Bread,
    Item_Kind__Armor__Cloth,
    Item_Kind__Dagger__Iron,
    Item_Kind__Dagger__Rusted,
};
enum Item_Kind loot_table__stone[] = {
    Item_Kind__Stick,
    Item_Kind__Bread,
    Item_Kind__Armor__Cloth,
    Item_Kind__Dagger__Iron,
    Item_Kind__Sword__Iron,
    Item_Kind__Battleaxe__Iron,
    Item_Kind__Scimitar__Iron,
    Item_Kind__Rapier__Iron,
    Item_Kind__Dagger__Rusted,
    Item_Kind__Sword__Rusted,
    Item_Kind__Battleaxe__Rusted,
    Item_Kind__Scimitar__Rusted,
    Item_Kind__Rapier__Rusted,
    Item_Kind__Armor__Iron__Rusted,
};
enum Item_Kind loot_table__gold[] = {
    Item_Kind__Armor__Iron,
    Item_Kind__Armor__Gold,
    Item_Kind__Dagger__Iron,
    Item_Kind__Sword__Iron,
    Item_Kind__Battleaxe__Iron,
    Item_Kind__Scimitar__Iron,
    Item_Kind__Rapier__Iron,
    Item_Kind__Armor__Iron__Rusted,
};
enum Item_Kind loot_table__iron[] = {
    Item_Kind__Dagger__Iron,
    Item_Kind__Sword__Iron,
    Item_Kind__Battleaxe__Iron,
    Item_Kind__Scimitar__Iron,
    Item_Kind__Rapier__Iron,
    Item_Kind__Armor__Iron__Rusted,
    Item_Kind__Armor__Gold,
    Item_Kind__Armor__Iron,
};
enum Item_Kind loot_table__diamond[] = {
    Item_Kind__Dagger__Steel,
    Item_Kind__Sword__Steel,
    Item_Kind__Battleaxe__Steel,
    Item_Kind__Scimitar__Steel,
    Item_Kind__Rapier__Steel,
    Item_Kind__Dagger__Steel__Order,
    Item_Kind__Sword__Steel__Order,
    Item_Kind__Battleaxe__Steel__Order,
    Item_Kind__Scimitar__Steel__Order,
    Item_Kind__Rapier__Steel__Order,
    Item_Kind__Armor__Steel,
    Item_Kind__Armor__Gold,
    Item_Kind__Armor__Gold__Order,
    // Item_Kind__Armor__Steel__Order,
};
enum Item_Kind loot_table__amethyst[] = {
    Item_Kind__Dagger__Steel,
    Item_Kind__Sword__Steel,
    Item_Kind__Battleaxe__Steel,
    Item_Kind__Scimitar__Steel,
    Item_Kind__Rapier__Steel,
    Item_Kind__Dagger__Steel__Chaos,
    Item_Kind__Sword__Steel__Chaos,
    Item_Kind__Battleaxe__Steel__Chaos,
    Item_Kind__Scimitar__Steel__Chaos,
    Item_Kind__Rapier__Steel__Chaos,
    Item_Kind__Armor__Steel,
    Item_Kind__Armor__Gold,
    Item_Kind__Armor__Steel,
    Item_Kind__Armor__Gold__Chaos,
    Item_Kind__Armor__Steel__Chaos,
};
enum Item_Kind loot_table__sandstone[] = {
    Item_Kind__Stick,
    Item_Kind__Bread,
    Item_Kind__Armor__Cloth,
    Item_Kind__Dagger__Iron,
    Item_Kind__Sword__Iron,
    Item_Kind__Battleaxe__Iron,
    Item_Kind__Scimitar__Iron,
    Item_Kind__Rapier__Iron,
    Item_Kind__Dagger__Rusted,
    Item_Kind__Sword__Rusted,
    Item_Kind__Battleaxe__Rusted,
    Item_Kind__Scimitar__Rusted,
    Item_Kind__Rapier__Rusted,
    Item_Kind__Armor__Iron__Rusted,
};

void f_chunk_generator__flat_world(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    Chunk *p_chunk =
        p_chunk_map_node
        ->p_chunk__here;

    Signed_Index__i32 x__index =
        p_chunk_map_node
        ->position_of__chunk_3i32.x__i32;
    Signed_Index__i32 y__index =
        p_chunk_map_node
        ->position_of__chunk_3i32.y__i32;

    Local_Parameters random_results[9];

    u32 chance_for__shrine =
        get_pseudo_random_i32_with__xy_from__game(
                p_game, 
                x__index, 
                y__index) & 127;

    if (chance_for__shrine < 1
            && (x__index < 0
                || x__index >= 8)
            && (y__index < 0
                || y__index >= 8)) {
        chance_for__shrine =
            get_pseudo_random_i32_with__xy_from__game(
                    p_game, 
                    ~x__index, 
                    ~y__index) % 7;
        for (Index__u8 y=0;y<8;y++) {
            for (Index__u8 x=0;x<8;x++) {
                Tile *p_tile =
                    &p_chunk->tiles[(7-y) * CHUNK_WIDTH__IN_TILES + x];
                p_tile->the_kind_of_tile__this_tile_is =
                    (enum Tile_Kind)((chance_for__shrine % 7) + 1);
            }
        }

        Item armor;
        Item weapon;

        u32 size_of__p_loot_table;
        enum Item_Kind *p_loot_table;
        switch (chance_for__shrine) {
            default:
            case 0:
                p_loot_table =
                    loot_table__wood;
                size_of__p_loot_table = sizeof(loot_table__wood)
                    / sizeof(enum Item_Kind);
                weapon = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Stick);
                armor = get_item__empty();
                break;
            case 1:
                p_loot_table =
                    loot_table__stone;
                size_of__p_loot_table = sizeof(loot_table__stone)
                    / sizeof(enum Item_Kind);
                weapon = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Sword__Rusted);
                armor = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Armor__Cloth);
                break;
            case 2:
                p_loot_table =
                    loot_table__gold;
                size_of__p_loot_table = sizeof(loot_table__gold)
                    / sizeof(enum Item_Kind);
                weapon = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Scimitar__Iron);
                armor = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Armor__Gold);
                break;
            case 3:
                p_loot_table =
                    loot_table__iron;
                size_of__p_loot_table = sizeof(loot_table__iron)
                    / sizeof(enum Item_Kind);
                weapon = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Scimitar__Iron);
                armor = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Armor__Iron);
                break;
            case 4:
                p_loot_table =
                    loot_table__diamond;
                size_of__p_loot_table = sizeof(loot_table__diamond)
                    / sizeof(enum Item_Kind);
                weapon = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Scimitar__Steel);
                armor = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Armor__Steel);
                break;
            case 5:
                p_loot_table =
                    loot_table__amethyst;
                size_of__p_loot_table = sizeof(loot_table__amethyst)
                    / sizeof(enum Item_Kind);
                weapon = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Scimitar__Steel);
                armor = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Armor__Steel);
                break;
            case 6:
                p_loot_table =
                    loot_table__sandstone;
                size_of__p_loot_table = sizeof(loot_table__sandstone)
                    / sizeof(enum Item_Kind);
                weapon = 
                    get_item_from__item_manager(
                            get_p_item_manager_from__game(p_game), 
                            Item_Kind__Scimitar__Steel);
                armor = 
                    get_item__empty();
                break;
        }

        Vector__3i32F4 positions[4];
        positions[0] = 
            get_vector__3i32F4_using__i32(
                    (x__index << 6) + (4 << 3), 
                    (y__index << 6),
                    0);
        positions[1] = 
            get_vector__3i32F4_using__i32(
                    (x__index << 6), 
                    (y__index << 6) + (4 << 3),
                    0);
        positions[2] = 
            get_vector__3i32F4_using__i32(
                    (x__index << 6) + (7 << 3), 
                    (y__index << 6) + (4 << 3),
                    0);
        positions[3] = 
            get_vector__3i32F4_using__i32(
                    (x__index << 6) + (4 << 3), 
                    (y__index << 6) + (7 << 3),
                    0);

        for (Quantity__u8 step = 0;
                step < 4;
                step++) {
            Entity *p_skeleton = 
                allocate_entity_into__world(
                        p_game, 
                        get_p_world_from__game(p_game), 
                        Entity_Kind__Skeleton, 
                        positions[step]);
            if (!p_skeleton)
                continue;
            p_skeleton->equipment.item_stack__main_hand.item =
                weapon;
            p_skeleton->equipment.item_stack__armor.item =
                armor;
            if (armor.m_item_equip_handler) {
                armor.m_item_equip_handler(
                        &armor,
                        p_skeleton,
                        Entity_Equipment_Slot_Kind__Armor,
                        p_game);
            }
        }

        Tile *p_tile =
            &p_chunk->tiles[4*8+4];
        p_tile->the_kind_of_tile_cover__this_tile_has =
            Tile_Cover_Kind__Chest_Single;
        set_tile__is_unpassable(p_tile, true);
        set_tile__container(p_tile, true);
        Tile_Vector__3i32 tile_vector__3i32 =
            get_vector__3i32(
                    (x__index << 3) + 4, 
                    (y__index << 3) + 3, 
                    0);
        Identifier__u32 container_uuid__u32 =
            get_uuid_for__container(
                    tile_vector__3i32);
        Inventory *p_inventory =
            allocate_p_inventory_using__this_uuid_in__inventory_manager(
                    get_p_inventory_manager_from__game(p_game), 
                    container_uuid__u32);

        u32 quantity_of__items = 
            add_u32__clamped(
                    get_pseudo_random_i32_with__xy_from__game(
                        p_game, 
                        x__index, 
                        y__index) % size_of__p_loot_table,
                    1,
                    size_of__p_loot_table - 1);
        for (Quantity__u8 step = 0;
                step < quantity_of__items;
                step++) {
            chance_for__shrine =
                get_pseudo_random_i32_with__xy_from__game(
                        p_game, 
                        step % 3 + x__index,
                        step / 3 + y__index) % size_of__p_loot_table;
            add_item_to__inventory(
                    p_inventory, 
                    get_item_from__item_manager(
                        get_p_item_manager_from__game(p_game), 
                        p_loot_table[chance_for__shrine]), 
                    1, 1);
        }

        return;
    }

    //TODO: debug_warning("f_chunk_generator__flat_world uses magic numbers.");
    
    for (Signed_Index__i32 y=-1;y< 2;y++) {
        for (Signed_Index__i32 x=-1;x<2;x++) {
            Index__u32 index = (x+1) + (3*(2 - (y+1)));
            random_results[index]
                .random_result__local__u32 =
                get_pseudo_random_i32_with__xy_from__game(
                        p_game, 
                        x__index + x, 
                        y__index + y);
            random_results[index]
                .random_result__greater__u32 =
                get_pseudo_random_i32_with__xy_from__game(
                        p_game,
                        (x__index + x) >> 4, 
                        (y__index + y) >> 4);

            // for flat_world, we will use these randomized values
            // as a sort of "moisture" level.

            random_results[index]
                .random_result__greater__u32 =
                random_results[index]
                .random_result__greater__u32 % 5;

            random_results[index]
                .random_result__local__u32 =
                random_results[index]
                .random_result__local__u32 % 5;

            random_results[index]
                .random_result__local__u32 = 
                (random_results[index].random_result__greater__u32 * 3
                + random_results[index].random_result__local__u32 * 5)
                 >> 3;
        }
    }

    for (Signed_Index__i32 y=0;y<CHUNK_WIDTH__IN_TILES;y++) {
        for (Signed_Index__i32 x=0;x<CHUNK_WIDTH__IN_TILES;x++) {
            Index__u32 tile_index =
                y * CHUNK_WIDTH__IN_TILES + x;
            Quantity__u32 moisture = 0;

            moisture +=
                random_results[6].random_result__local__u32 
                * weight_map.map[tile_index].A
                + random_results[7].random_result__local__u32 
                * weight_map.map[tile_index].B
                + random_results[8].random_result__local__u32 
                * weight_map.map[tile_index].C
                + random_results[3].random_result__local__u32 
                * weight_map.map[tile_index].D
                + random_results[4].random_result__local__u32 
                * weight_map.map[tile_index].E
                + random_results[5].random_result__local__u32 
                * weight_map.map[tile_index].F
                + random_results[0].random_result__local__u32 
                * weight_map.map[tile_index].G
                + random_results[1].random_result__local__u32 
                * weight_map.map[tile_index].H
                + random_results[2].random_result__local__u32 
                * weight_map.map[tile_index].I
                ;
            tile_index =
                (7-y) * CHUNK_WIDTH__IN_TILES + x;

            moisture = moisture >> 5;
            if (moisture >= 5)
                moisture = 4;

            Tile *p_tile = 
                &p_chunk->tiles[tile_index];
            initialize_tile(
                    p_tile,
                    Tile_Kind__Oak_Wood,
                    Tile_Cover_Kind__None,
                    TILE_FLAGS__NONE);

            Psuedo_Random__u32 chance_plant =
                get_pseudo_random_i32_from__game(
                        p_game)
                % 10000;
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__None;

            switch (moisture) {
                default:
                case 0:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Sand;
                    if (chance_plant > 9700)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Cactus;
                    break;
                case 1:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Stone;
                    if (chance_plant > 9996)
                        set_tile_cover_as__ore(
                                p_tile, 
                                0, 
                                Item_Kind__Pile__Diamond, 
                                chance_plant,
                                false);
                    else if (chance_plant > 9993)
                        set_tile_cover_as__ore(
                                p_tile, 
                                0, 
                                Item_Kind__Pile__Amethyst, 
                                chance_plant,
                                false);
                    else if (chance_plant > 9987)
                        set_tile_cover_as__ore(
                                p_tile, 
                                0, 
                                Item_Kind__Pile__Gold, 
                                chance_plant,
                                false);
                    else if (chance_plant > 9975)
                        set_tile_cover_as__ore(
                                p_tile, 
                                0, 
                                Item_Kind__Pile__Iron, 
                                chance_plant,
                                false);
                    else if (chance_plant > 9945)
                        set_tile_cover_as__ore(
                                p_tile, 
                                0, 
                                Item_Kind__Bag_Of__Coal, 
                                chance_plant,
                                false);
                    else if (chance_plant > 9900)
                        set_tile_cover_as__ore(
                                p_tile, 
                                0, 
                                Item_Kind__Pile__Stone, 
                                chance_plant,
                                false);
                    break;
                case 2:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Dirt;
                    if (chance_plant > 9990)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Blue;
                    else if (chance_plant > 9970)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Red;
                    else if (chance_plant > 9960)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Yellow;
                    else if (chance_plant > 9940)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Fern;
                    else if (chance_plant > 9400)
                        set_tile_cover_as__tree(p_tile, 
                                chance_plant);
                    break;
                case 3:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Grass;
                    if (chance_plant > 9970)
                        set_tile_cover_as__tree(p_tile, 
                                chance_plant);
                    else if (chance_plant > 9700)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Blue;
                    else if (chance_plant > 9500)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Red;
                    else if (chance_plant > 9200)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Yellow;
                    else if (chance_plant > 8800)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Fern;
                    break;
                case 4:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Water;
                    break;
            }
        }
    }
}
