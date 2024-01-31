#ifndef VIEWING_FULCRUM_H
#define VIEWING_FULCRUM_H

///
/// This module is reponsible for determining
/// what is on the screen and what isn't.
///
/// If an entity is not on the screen, it will
/// set it as being hidden, but not disabled.
///
/// The viewing_fulcrum struct (in defines.h)
/// also has a width and height in chunks
/// which is utilized with a chunk_manager
/// reference to determine what chunks are
/// visible.
///

#include <defines.h>
#include <collisions/hitbox_aabb.h>
#include <world/chunk_manager.h>

static bool inline is_chunk_within__viewing_fulcrum(
        Viewing_Fulcrum *viewing_fulcrum,
        int32_t x__chunk,
        int32_t y__chunk) {
    int32_t x__chunk__min =
        get_aa__x__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
    int32_t y__chunk__min =
        get_aa__y__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
    int32_t x__chunk__max =
        get_bb__x__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
    int32_t y__chunk__max =
        get_bb__y__chunk_from__hitbox(&viewing_fulcrum->fulcrum);

    return 
        x__chunk >= x__chunk__min 
        &&
        x__chunk <= x__chunk__max
        &&
        y__chunk >= y__chunk__min
        &&
        y__chunk <= y__chunk__max
        ;
}

static Chunk_Manager__Chunk_Map_Node inline 
*get_most_north_western__chunk_map_node_in__viewing_fulcrum(
        Viewing_Fulcrum *viewing_fulcrum,
        Chunk_Manager *chunk_manager,
        int32_t z__chunk) {
    int32_t x__chunk =
        get_aa__x__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
    int32_t y__chunk =
        get_bb__y__chunk_from__hitbox(&viewing_fulcrum->fulcrum);

    return get_chunk_map_node_from__chunk_manager(
            chunk_manager, 
            x__chunk, 
            y__chunk, 
            z__chunk);
}

static Chunk_Manager__Chunk_Map_Node inline 
*get_most_south_eastern__chunk_map_node_in__viewing_fulcrum(
        Viewing_Fulcrum *viewing_fulcrum,
        Chunk_Manager *chunk_manager,
        int32_t z__chunk) {
    int32_t x__chunk =
        get_bb__x__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
    int32_t y__chunk =
        get_aa__y__chunk_from__hitbox(&viewing_fulcrum->fulcrum);

    return get_chunk_map_node_from__chunk_manager(
            chunk_manager, 
            x__chunk, 
            y__chunk, 
            z__chunk);
}

///
/// This helper function only works if:
/// 1) original__chunk_map_node is inside the viewing_fulcrum
/// 2) original__chunk_map_node x is less than current__chunk_map_node
/// 3) original__chunk_map_node y is greater than current__chunk_map_node
///
/// It will determine the next node while scanning chunks within
/// the viewing_fulcrum.
///
static Chunk_Manager__Chunk_Map_Node inline
*get_next_chunk_map_node_in__viewing_fulcrum(
        Viewing_Fulcrum *viewing_fulcrum,
        Chunk_Manager__Chunk_Map_Node *current__chunk_map_node,
        Chunk_Manager__Chunk_Map_Node *original__chunk_map_node) {
    if (!is_chunk_within__viewing_fulcrum(
                viewing_fulcrum, 
                current__chunk_map_node
                ->chunk_map_node__east->chunk__here->x,
                current__chunk_map_node
                ->chunk_map_node__east->chunk__here->y)) {
        Chunk_Manager__Chunk_Map_Node *next_node =
            original__chunk_map_node;
        while (next_node->chunk__here->y >= 
                current__chunk_map_node->chunk__here->y) {
            next_node = next_node->chunk_map_node__south;
        }
        if (!is_chunk_within__viewing_fulcrum(
                    viewing_fulcrum, 
                    next_node->chunk__here->x,
                    next_node->chunk__here->y)) {
            return 0;
        }
        return next_node;
    }
    return current__chunk_map_node->chunk_map_node__east;
}

static bool inline is_entity_within__viewing_fulcrum(
        Entity *entity,
        Viewing_Fulcrum *viewing_fulcrum) {
    return is_this_hitbox_center__inside_this_hitbox(
            &entity->hitbox, &viewing_fulcrum->fulcrum);
}

///
/// This macro is to be used in the context which
/// the viewing_fulcrum is overlapping the chunk_manager.
///
/// The macro exists in the first place because this
/// is inlined code that pretty much every backend implementation
/// wants to reuse. The usage caveat here is that the platform
/// specific code wants to occur within the loop.
///
#define FOREACH_CHUNK_MAP_NODE_IN__VIEWING_FULCRUM( \
        viewing_fulcrum, \
        chunk_manager, \
        z__chunk, \
        alias_for_current_chunk) \
        Chunk_Manager__Chunk_Map \
            *most_north_western__node_in__viewing_fulcrum; \
        Chunk_Manager__Chunk_Map_Node \
            *alias_for_current_chunk = \
            most_north_western__node_in__viewing_fulcrum = \
                get_most_north_western__chunk_map_node_in__viewing_fulcrum( \
                        viewing_fulcrum, chunk_manager, z__chunk); \
        alias_for_current_chunk = \
            alias_for_current_chunk->chunk_map_node__west; \
        while ((alias_for_current_chunk = \
                    get_next_chunk_map_node_in__viewing_fulcrum( \
                        viewing_fulcrum, \
                        alias_for_current_chunk , \
                        most_north_western__node_in__viewing_fulcrum)))

#endif
