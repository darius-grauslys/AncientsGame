#include <defines.h>
#include <world/generators/generator_flat_world.h>
#include <world/world_parameters.h>

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

void f_chunk_generator__flat_world(
        World_Parameters *p_world_parameters,
        Chunk *p_chunk) {
    Local_Parameters random_results[9];

    //TODO: debug_warning("f_chunk_generator__flat_world uses magic numbers.");
    
    for (Signed_Index__i32 y=-1;y< 2;y++) {
        for (Signed_Index__i32 x=-1;x<2;x++) {
            Index__u32 index = (x+1) + (3*(2 - (y+1)));
            random_results[index]
                .random_result__local__u32 =
                get_repeatable_pseudo_random_i32_with__xy_from__world_parameters(
                        p_world_parameters, 
                        p_chunk->x__signed_index_i32 + x, 
                        p_chunk->y__signed_index_i32 + y);
            random_results[index]
                .random_result__greater__u32 =
                get_repeatable_pseudo_random_i32_with__xy_from__world_parameters(
                        p_world_parameters, 
                        (p_chunk->x__signed_index_i32 + x) >> 4, 
                        (p_chunk->y__signed_index_i32 + y) >> 4);

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
                get_pseudo_random_i32__from_world_parameters(
                        p_world_parameters)
                % 100;
            p_tile->the_kind_of_tile_cover__this_tile_has =
                Tile_Cover_Kind__None;

            switch (moisture) {
                default:
                case 0:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Sand;
                    if (chance_plant > 97)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Cactus;
                    break;
                case 1:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Stone;
                    break;
                case 2:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Dirt;
                    if (chance_plant > 94)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Plant;
                    if (chance_plant > 96)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Yellow;
                    if (chance_plant > 97)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Red;
                    if (chance_plant > 98)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Blue;
                    break;
                case 3:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Grass;
                    if (chance_plant > 88)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Plant;
                    if (chance_plant > 92)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Yellow;
                    if (chance_plant > 95)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Red;
                    if (chance_plant > 97)
                        p_tile->the_kind_of_tile_cover__this_tile_has =
                            Tile_Cover_Kind__Flower_Blue;
                    break;
                case 4:
                    p_tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Water;
                    break;
            }
        }
    }
}
