#include <defines.h>
#include <world/generators/generator_flat_world.h>
#include <world/world_parameters.h>

#include <debug/debug.h>

typedef struct Local_Parameters_t {
    uint32_t random__result__greater;
    uint32_t random__result__local;
} Local_Parameters;

typedef struct Weight_Matrix_t {
    uint8_t A, B, C;
    uint8_t D, E, F;
    uint8_t G, H, I;
} Weight_Matrix;

typedef struct Weight_Map_t {
    Weight_Matrix map[CHUNK_QUANTITY_OF__TILES];
} Weight_Map;

Weight_Map weight_map;

void flip_xy__weight_matrix(
        Weight_Matrix *source, Weight_Matrix *dest) {
    dest->E = source->E;

    dest->A = source->I;
    dest->B = source->H;
    dest->C = source->G;

    dest->F = source->D;
    dest->I = source->A;

    dest->H = source->B;
    dest->G = source->C;

    dest->D = source->F;
}

void flip_y__weight_matrix(
        Weight_Matrix *source, Weight_Matrix *dest) {
    dest->E = source->E;

    dest->A = source->C;
    dest->B = source->B;
    dest->C = source->A;

    dest->F = source->D;
    dest->I = source->G;

    dest->H = source->H;
    dest->G = source->I;

    dest->D = source->F;
}

void flip_x__weight_matrix(
        Weight_Matrix *source, Weight_Matrix *dest) {
    dest->E = source->E;

    dest->A = source->G;
    dest->B = source->H;
    dest->C = source->I;

    dest->F = source->F;
    dest->I = source->C;

    dest->H = source->B;
    dest->G = source->A;

    dest->D = source->D;
}

void init_weight_map(void) {
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

    Weight_Matrix *source_matrix;
    Weight_Matrix *current_matrix;
    uint32_t index;

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

void chunk_generator__flat_world_f(
        World_Parameters *world_params,
        Chunk *chunk) {
    Local_Parameters random__results[9];

    debug_warning("chunk_generator__flat_world_f uses magic numbers.");
    
    for (int32_t y=-1;y<2;y++) {
        for (int32_t x=-1;x<2;x++) {
            uint32_t index = (x+1) + (3*(2 - (y+1)));
            random__results[index]
                .random__result__local =
                get_repeatable_random__xy__from_world_parameters(
                        world_params, 
                        chunk->x + x, chunk->y + y);
            random__results[index]
                .random__result__greater =
                get_repeatable_random__xy__from_world_parameters(
                        world_params, 
                        (chunk->x + x) >> 4, (chunk->y + y) >> 4);

            // for flat_world, we will use these randomized values
            // as a sort of "moisture" level.

            random__results[index]
                .random__result__greater =
                random__results[index]
                .random__result__greater % 5;

            random__results[index]
                .random__result__local =
                random__results[index]
                .random__result__local % 5;

            random__results[index]
                .random__result__local = 
                (random__results[index].random__result__greater * 3
                + random__results[index].random__result__local * 5)
                 >> 3;
        }
    }

    // debug_info("chunk x,y,greater,local: %d, %d, %d , %d",
    //         chunk->x, chunk->y, 
    //         random__results[4].random__result__greater,
    //         random__results[4].random__result__local);

    for (int32_t y=0;y<CHUNK_WIDTH__IN_TILES;y++) {
        for (int32_t x=0;x<CHUNK_WIDTH__IN_TILES;x++) {
            uint32_t tile_index =
                y * CHUNK_WIDTH__IN_TILES + x;
            uint32_t moisture = 0;

            moisture +=
                random__results[6].random__result__local *
                weight_map.map[tile_index].A
                +
                random__results[7].random__result__local *
                weight_map.map[tile_index].B
                +
                random__results[8].random__result__local *
                weight_map.map[tile_index].C
                +
                random__results[3].random__result__local *
                weight_map.map[tile_index].D
                +
                random__results[4].random__result__local *
                weight_map.map[tile_index].E
                +
                random__results[5].random__result__local *
                weight_map.map[tile_index].F
                +
                random__results[0].random__result__local *
                weight_map.map[tile_index].G
                +
                random__results[1].random__result__local *
                weight_map.map[tile_index].H
                +
                random__results[2].random__result__local *
                weight_map.map[tile_index].I
                ;

            moisture = moisture >> 5;
            if (moisture >= 5)
                moisture = 4;

            Tile *tile = 
                &chunk->tiles[tile_index];

            switch (moisture) {
                default:
                case 0:
                    tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Sand;
                    break;
                case 1:
                    tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Stone;
                    break;
                case 2:
                    tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Dirt;
                    break;
                case 3:
                    tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Grass;
                    break;
                case 4:
                    tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Water;
                    break;
            }
        }
    }
}
