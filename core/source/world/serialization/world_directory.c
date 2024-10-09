#include "world/serialization/world_directory.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
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
    // assume buffer is of minimium length:
    // WORLD_NAME_MAX_SIZE_OF + "/r_XXXXXX" + "/c_XXXX" + "/c_X" + "/F\0"
    // == WORLD_NAME_MAX_SIZE_OF + 9 + 7 + 4 + 3
    // == WORLD_NAME_MAX_SIZE_OF + 23

    Index__u32 index_of__path_append = 0;

    PLATFORM_append_base_directory_to__path(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            buffer, 
            &index_of__path_append);

    buffer[index_of__path_append++] = '/';

    // TODO: bounds check index_of__path_append + WORLD_NAME_MAX_SIZE_OF
    //                      < MAX_LENGTH_OF__IO_PATH
    strncpy(&buffer[index_of__path_append], 
            get_p_world_from__game(p_game)->name,
            WORLD_NAME_MAX_SIZE_OF);

    index_of__path_append += 
        get_p_world_from__game(p_game)->length_of__world_name;

    DIR *p_dir;
    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }

    buffer[index_of__path_append++] = '/';
    buffer[index_of__path_append++] = 'r';
    buffer[index_of__path_append++] = '_';
    
    Region_Vector__3i32 region_vector__3i32 =
        get_region_that__this_chunk_map_node_is_in(
                p_chunk_map_node);

    for (Index__u8 i=0;i<6;i++) {
        buffer[index_of__path_append++] =
            'A'
            + (region_vector__3i32.x__i32 & MASK(4));
        region_vector__3i32.x__i32 >>= 4;
    }
    buffer[index_of__path_append++] = '_';
    for (Index__u8 i=0;i<6;i++) {
        buffer[index_of__path_append++] =
            'A'
            + (region_vector__3i32.y__i32 & MASK(4));
        region_vector__3i32.y__i32 >>= 4;
    }

    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }

    buffer[index_of__path_append++] = '/';
    buffer[index_of__path_append++] = 'c';
    buffer[index_of__path_append++] = '_';
    
    Chunk_Vector__3i32 chunk_vector__3i32 =
        p_chunk_map_node->position_of__chunk_3i32;

    for (Index__u8 i=0;i<3;i++) {
        buffer[index_of__path_append++] =
            'A'
            + (chunk_vector__3i32.x__i32 & MASK(4));
        chunk_vector__3i32.x__i32 >>= 4;
    }
    buffer[index_of__path_append++] = '_';
    for (Index__u8 i=0;i<3;i++) {
        buffer[index_of__path_append++] =
            'A'
            + (chunk_vector__3i32.y__i32 & MASK(4));
        chunk_vector__3i32.y__i32 >>= 4;
    }

    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }

    buffer[index_of__path_append++] = '/';
    buffer[index_of__path_append++] = 'c';
    buffer[index_of__path_append++] = '_';
    
    i32 z__i32 =
        p_chunk_map_node->position_of__chunk_3i32.z__i32;

    for (Index__u8 i=0;i<2;i++) {
        buffer[index_of__path_append++] =
            'A'
            + (z__i32 & MASK(4));
        z__i32 >>= 8;
    }

    if (!(p_dir = opendir(buffer))) {
        if (mkdir(buffer, 0777)) {
            return 0;
        }
    } else {
        closedir(p_dir);
    }
    return 
        index_of__path_append;
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
