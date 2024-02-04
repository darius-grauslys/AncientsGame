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

void init_viewing_fulcrum(
        Viewing_Fulcrum *viewing_fulcrum);

static bool inline is_chunk_position_within__viewing_fulcrum(
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

static void inline 
init_hitbox_point_as__most_north_western_chunk_in__viewing_fulcrum(
        Hitbox_Point *hitbox_point,
        Viewing_Fulcrum *viewing_fulcrum) {
    hitbox_point->x =
        get_aa__x__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
    hitbox_point->y =
        get_bb__y__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
}

static void inline 
init_hitbox_point_as__most_south_eastern_chunk_in__viewing_fulcrum(
        Hitbox_Point *hitbox_point,
        Viewing_Fulcrum *viewing_fulcrum) {
    hitbox_point->x =
        get_bb__x__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
    hitbox_point->y =
        get_aa__y__chunk_from__hitbox(&viewing_fulcrum->fulcrum);
}

///
/// This helper function only works if:
/// 1) original__position is inside the viewing_fulcrum
/// 2) original__position x is less than current__position
/// 3) original__position y is greater than current__position
///
/// It will determine the next node while scanning chunks within
/// the viewing_fulcrum.
///
/// Returns true if the current call is in bounds
/// Returns false if the current call is out of bounds.
///
static bool inline
get_next_chunk_position_in__viewing_fulcrum(
        Viewing_Fulcrum *viewing_fulcrum,
        Hitbox_Point *current__position,
        Hitbox_Point *original__position) {
    if (!is_chunk_position_within__viewing_fulcrum(
                viewing_fulcrum, 
                current__position->x,
                current__position->y)) {
        Hitbox_Point next__position =
            *original__position;
        while (next__position.y >= 
                current__position->y) {
            next__position.y--;
        }
        if (!is_chunk_position_within__viewing_fulcrum(
                    viewing_fulcrum, 
                    next__position.x,
                    next__position.y)) {
            return 0;
        }
        *current__position =
            next__position;
        return true;
    }
    return false;
}

static bool inline is_entity_within__viewing_fulcrum(
        Entity *entity,
        Viewing_Fulcrum *viewing_fulcrum) {
    return is_this_hitbox_center__inside_this_hitbox(
            &entity->hitbox, &viewing_fulcrum->fulcrum);
}

static void inline focus_viewing_fulcrum_at__entity(
        Viewing_Fulcrum *viewing_fulcrum,
        Entity *entity) {
    set_hitbox__position(
            &viewing_fulcrum->fulcrum, 
            get_global_x_from__hitbox(&entity->hitbox), 
            get_global_y_from__hitbox(&entity->hitbox), 
            get_global_z_from__hitbox(&entity->hitbox)
            );
}

#endif
