#ifndef TILE_LOGIC_RECORD_H
#define TILE_LOGIC_RECORD_H

#include <defines.h>

#define TILE_LOGIC_RECORD(\
        f_tile_handler__interact,\
        f_tile_handler__touch,\
        f_tile_handler__place)\
            (Tile_Logic_Record){\
                f_tile_handler__interact,\
                f_tile_handler__touch,\
                f_tile_handler__place\
            }

void initialize_tile_logic_record(
        Tile_Logic_Record *p_tile_logic_record,
        f_Tile_Handler__Interact f_tile_handler__interact,
        f_Tile_Handler__Touch f_tile_handler__touch,
        f_Tile_Handler__Place f_tile_handler__place);

static inline
void initialize_tile_logic_record_as__unused(
        Tile_Logic_Record *p_tile_logic_record) {
    initialize_tile_logic_record(
            p_tile_logic_record,
            0, 0, 0);
}

static inline
void invoke_tile_logic_record__interact(
        Tile_Logic_Record *p_tile_logic_record,
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity) {
    p_tile_logic_record
        ->f_tile_handler__interact(
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
}

static inline
void invoke_tile_logic_record__touch(
        Tile_Logic_Record *p_tile_logic_record,
        Game *p_game,
        Tile *p_tile,
        Tile_Vector__3i32 tile_vector__3i32,
        Entity *p_entity) {
    p_tile_logic_record
        ->f_tile_handler__touch(
                p_game,
                p_tile,
                tile_vector__3i32,
                p_entity);
}

static inline
bool invoke_tile_logic_record__place(
        Tile_Logic_Record *p_tile_logic_record,
        Game *p_game,
        Tile *p_tile,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover,
        Tile_Vector__3i32 tile_vector__3i32) {
    return p_tile_logic_record
        ->f_tile_handler__place(
                p_game,
                p_tile,
                the_kind_of__tile,
                the_kind_of__tile_cover,
                tile_vector__3i32);
}

static inline
bool is_tile_logic_record_possessing__interact(
        Tile_Logic_Record *p_tile_logic_record) {
    return p_tile_logic_record->f_tile_handler__interact;
}

static inline
bool is_tile_logic_record_possessing__touch(
        Tile_Logic_Record *p_tile_logic_record) {
    return p_tile_logic_record->f_tile_handler__touch;
}

static inline
bool is_tile_logic_record_possessing__place(
        Tile_Logic_Record *p_tile_logic_record) {
    return p_tile_logic_record->f_tile_handler__place;
}

#endif
