#include <defines.h>
#include <world/generators/generator_flat_world.h>
#include <world/world_parameters.h>

#include <debug/debug.h>

typedef struct Local_Parameters_t {
    uint32_t random__result__greater;
    uint32_t random__result__local;
} Local_Parameters;

void chunk_generator__flat_world_f(
        World_Parameters *world_params,
        Chunk *chunk) {
    Local_Parameters random__results[9];

    debug_warning("chunk_generator__flat_world_f uses magic numbers.");
    
    for (int32_t y=-1;y<2;y++) {
        for (int32_t x=-1;x<2;x++) {
            uint32_t index = (x+1) + (3*(y+1));
            random__results[index]
                .random__result__local =
                get_repeatable_random__xy__from_world_parameters(
                        world_params, 
                        chunk->x + x, chunk->y + y);
            random__results[(x + 1) + (3 * (y+1))]
                .random__result__greater =
                get_repeatable_random__xy__from_world_parameters(
                        world_params, 
                        (chunk->x + x) >> 4, (chunk->y + y) >> 4);

            // for flat_world, we will use these randomized values
            // as a sort of "moisture" level.

            random__results[index]
                .random__result__greater =
                random__results[index]
                .random__result__greater / (1<<7) % 5;
            random__results[index]
                .random__result__local =
                random__results[index]
                .random__result__local / (1<<7) % 5;
            random__results[index]
                .random__result__local = 
                (random__results[index].random__result__greater * 2
                + random__results[index].random__result__local)
                / 2;
            random__results[index]
                .random__result__local *=
                random__results[index].random__result__local;
        }
    }

    // debug_info("chunk x,y,greater,local: %d, %d, %d , %d",
    //         chunk->x, chunk->y, 
    //         random__results[4].random__result__greater,
    //         random__results[4].random__result__local);

    for (int32_t y=0;y<CHUNK_WIDTH__IN_TILES;y++) {
        for (int32_t x=0;x<CHUNK_WIDTH__IN_TILES;x++) {
            uint32_t moisture = 
                (random__results[0].random__result__local << 1 
					 / ((-1 - x) * (-1 - x) +
                        (-1 - y) * (-1 - y)))
                + 
                (random__results[1].random__result__local << 1
					 / ((4 - x) * (4 - x) +
                        (-1 - y) * (-1 - y)))
                +
                (random__results[2].random__result__local << 1
					 / ((8 - x) * (8 - x) +
                        (-1 - y) * (-1 - y)))
                +
                (random__results[3].random__result__local << 1
					 / ((-5 - x) * (-5 - x) +
                        (4 - y) * (4 - y)))
                + 
                (random__results[4].random__result__local << 1
					 / ((4 - x) * (4 - x) +
                        (4 - y) * (4 - y)) + 1)
                +
                (random__results[5].random__result__local << 1
					 / ((8 - x) * (8 - x) +
                        (4 - y) * (4 - y)))
                +
                (random__results[6].random__result__local << 1
					 / ((-1 - x) * (-1 - x) +
                        (8 - y) * (8 - y)))
                + 
                (random__results[7].random__result__local << 1
					 / ((4 - x) * (4 - x) +
                        (8 - y) * (8 - y)))
                +
                (random__results[8].random__result__local << 1 
					 / ((8 - x) * (8 - x) +
                        (8 - y) * (8 - y)))
                ;
            moisture = (moisture / 9);
            if (moisture >= 5)
                moisture = 4;

            Tile *tile = 
                &chunk->tiles[y * CHUNK_WIDTH__IN_TILES + x];

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
                case 4:
                    tile->the_kind_of_tile__this_tile_is =
                        Tile_Kind__Water;
                    break;
            }
        }
    }
}
