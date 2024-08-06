#include "world/serialization/world_directory.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "world/region.h"
#include "sys/stat.h"
#include "sys/types.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "world/region.h"
#include <unistd.h>

Index__u8 stat_chunk_directory(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer) {
    char directory__world[WORLD_NAME_MAX_SIZE_OF];
    strncpy(directory__world, 
            get_p_world_from__game(p_game)->name,
            WORLD_NAME_MAX_SIZE_OF);
    Quantity__u8 length_of__world_name =
        strnlen(
                directory__world, 
                WORLD_NAME_MAX_SIZE_OF) + 1;
    char directory__region[16];
    Region_Vector__3i32 region = 
        get_region_that__this_chunk_map_node_is_in(
                p_chunk_map_node);
    snprintf(
            directory__region,
            sizeof(directory__region),
            "r_%lx_%lx",
            region.x__i32 & MASK(21), //TODO:   magic num, this is the quantity
            region.y__i32 & MASK(21));      //  of regions per axis
    Quantity__u8 length_of__directory_region =
        strnlen(
                directory__region,
                16);

    char directory__chunk_column[10];
    snprintf(
            directory__chunk_column,
            sizeof(directory__chunk_column),
            "c_%lx_%lx",
            p_chunk_map_node->position_of__chunk_3i32.x__i32
            & MASK(REGION__WIDTH__BIT_SHIFT),
            p_chunk_map_node->position_of__chunk_3i32.y__i32
            & MASK(REGION__WIDTH__BIT_SHIFT));
    Quantity__u8 length_of__directory_chunk_column =
        strnlen(
                directory__chunk_column,
                sizeof(directory__chunk_column));

    char directory__chunk[4];
    snprintf(
            directory__chunk,
            sizeof(directory__chunk),
            "c_%x",
            0);
    // Quantity__u8 length_of__directory_chunk =
    //     strnlen(
    //             directory__chunk,
    //             sizeof(directory__chunk));

    snprintf(
            buffer,
            length_of__world_name, "%s",
            directory__world);
    DIR *p_dir;
    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }
    snprintf(
            &buffer[length_of__world_name-1],
            sizeof(directory__region)+1, "/%s",
            directory__region);
    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }
    snprintf(
            &buffer[
                length_of__world_name
                +length_of__directory_region],
            sizeof(directory__chunk_column)+1, "/%s",
            directory__chunk_column);
    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }
    snprintf(
            &buffer[
                length_of__world_name
                +length_of__directory_region
                +length_of__directory_chunk_column+1],
            sizeof(directory__chunk)+1, "/%s",
            directory__chunk);
    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }
    return 
        strnlen(buffer, 128);
}

static inline
Index__u8 stat_chunk_file(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer,
        char file_character) {
    Index__u8 end_of__path = 
        stat_chunk_directory(
                p_game, 
                p_chunk_map_node, 
                buffer);
    if (!end_of__path) {
        debug_abort("stat_chunk_file__tile, directories do not exist: %s",
                buffer);
        return false;
    }
    buffer[end_of__path] = '/';
    buffer[end_of__path+1] = file_character;

    if (access(buffer, F_OK)) {
        return false;
    }

    return end_of__path+2;
}

Index__u8 stat_chunk_file__tiles(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer) {
    return stat_chunk_file(
            p_game,
            p_chunk_map_node,
            buffer,
            't');
}

Index__u8 stat_chunk_file__entities(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer) {
    return stat_chunk_file(
            p_game,
            p_chunk_map_node,
            buffer,
            'e');
}

Index__u8 stat_chunk_file__inventories(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *buffer) {
    return stat_chunk_file(
            p_game,
            p_chunk_map_node,
            buffer,
            'i');
}
