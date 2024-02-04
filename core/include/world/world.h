#ifndef WORLD_H
#define WORLD_H

#include <world/chunk_manager.h>
#include <world/viewing_fulcrum.h>
#include <defines.h>

static Entity_Manager inline 
*get_entity_manager_from__world(World *world) {
    return &world->entity_manager;
}

static Chunk_Manager inline 
*get_chunk_manager_from__world(World *world) {
    return &world->chunk_manager;
}

static Collision_Manager inline 
*get_collision_manager_from__world(World *world) {
    return &world->collision_manager;
}

static World_Parameters inline
*get_world_parameters_from__world(World *world) {
    return &world->world_params;
}

void init_world(World *world);

void add_entity_to__world(
        World *world,
        Entity *entity);

bool poll_world_for__scrolling(
        World *world);

static bool inline get_next_chunk_map_node_in__viewing_fulcrum(
        World *world,
        Chunk_Manager__Chunk_Map_Node **current__chunk_map_node,
        Hitbox_Point *original__chunk_position,
        int32_t z__chunk) {
    Hitbox_Point current__chunk_position = {
        (*current__chunk_map_node)->chunk__here->x,
        (*current__chunk_map_node)->chunk__here->y,
        0
    };
    bool result =
        get_next_chunk_position_in__viewing_fulcrum(
                &world->viewing_fulcrum, 
                &current__chunk_position, 
                original__chunk_position);
    if (!result) 
        return result;
    if (current__chunk_position.x
            < (*current__chunk_map_node)->chunk__here->x) {
        (*current__chunk_map_node) =
            get_chunk_map_node_from__chunk_manager(
                    &world->chunk_manager, 
                    current__chunk_position.x, 
                    current__chunk_position.y, 
                    z__chunk);
        return result;
    }
    (*current__chunk_map_node) =
        (*current__chunk_map_node)
        ->chunk_map_node__east;
    return result;
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
        world_ptr, \
        z__chunk, \
        alias_for_current_chunk) \
        Hitbox_Point\
            chunk_position__most_north_western_in__viewing_fulcrum; \
        init_hitbox_point_as__most_north_western_chunk_in__viewing_fulcrum( \
                &chunk_position__most_north_western_in__viewing_fulcrum, \
                &world_ptr->viewing_fulcrum); \
        Chunk_Manager__Chunk_Map_Node \
            * alias_for_current_chunk = \
                get_chunk_map_node_from__chunk_manager( \
                        &world_ptr->chunk_manager, \
                        chunk_position__most_north_western_in__viewing_fulcrum.x, \
                        chunk_position__most_north_western_in__viewing_fulcrum.y, \
                        z__chunk); \
        alias_for_current_chunk = \
            alias_for_current_chunk->chunk_map_node__west; \
        while(get_next_chunk_map_node_in__viewing_fulcrum( \
                    world_ptr, \
                    & alias_for_current_chunk, \
                    &chunk_position__most_north_western_in__viewing_fulcrum, \
                    z__chunk))


#endif
