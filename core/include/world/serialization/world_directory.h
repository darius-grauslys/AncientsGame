#ifndef WORLD_DIRECTORY_H
#define WORLD_DIRECTORY_H

#include "defines_weak.h"
#include <defines.h>

Index__u8 stat_chunk_directory(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer);

Index__u8 stat_chunk_file__tiles(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer);

Index__u8 stat_chunk_file__entities(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer);

Index__u8 stat_chunk_file__inventories(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer);

static inline
bool append_chunk_file__tiles_to__path(
        char *buffer,
        Quantity__u16 length_of__path,
        Quantity__u16 max_length_of__path) {
    if (length_of__path + 2 > max_length_of__path)
        return false;

    buffer[length_of__path] = '/';
    buffer[length_of__path+1] = 't';
    return true;
}

static inline
bool append_chunk_file__entities_to__path(
        char *buffer,
        Quantity__u16 length_of__path,
        Quantity__u16 max_length_of__path) {
    if (length_of__path + 2 > max_length_of__path)
        return false;

    buffer[length_of__path] = '/';
    buffer[length_of__path+1] = 'e';
    return true;
}

static inline
bool append_chunk_file__inventories_to__path(
        char *buffer,
        Quantity__u16 length_of__path,
        Quantity__u16 max_length_of__path) {
    if (length_of__path + 2 > max_length_of__path)
        return false;

    buffer[length_of__path] = '/';
    buffer[length_of__path+1] = 'i';
    return true;
}

#endif
