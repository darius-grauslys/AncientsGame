#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include <defines.h>
#include "world/tile_vectors.h"
#include "entity/entity_util.h"
#include "game.h"

static inline
Tile_Vector__3i32 get_tile_vector_thats__infront_of_this__entity(
        Entity *p_entity) {
    return vector_3i32F4_to__tile_vector(
            get_vector_3i32F4_thats__infront_of_this__entity(
                p_entity));
}

static inline
Tile *get_p_tile_thats__infront_of__this_entity(
        Game *p_game,
        Entity *p_entity) {
    return get_p_tile_from__chunk_manager_with__tile_vector_3i32(
            get_p_chunk_manager_from__game(p_game), 
            get_tile_vector_thats__infront_of_this__entity(p_entity));
} 

#endif
