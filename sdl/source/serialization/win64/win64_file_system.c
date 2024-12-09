#include "defines_weak.h"
#include "serialization/sdl_filesystem_defines.h"
#include <serialization/unix/unix_filesystem.h>

#ifdef _WIN32

#include <windows.h>
#include <stdio.h>

bool SDL_get_path_to__the_game(char path[1024]) {
    DWORD length = GetCurrentDirectory(1024, path);
    if (!length) 
        return false;

    return PLATFORM_access(path, IO_Access_Kind__File) == 0;
}

typedef struct PLATFORM_Directory_t {
    HANDLE handle;
} PLATFORM_Directory;

int PLATFORM_access(const char *p_c_str, IO_Access_Kind io_access_kind) {
    switch (io_access_kind) {
        default:
            DWORD fileAttr = GetFileAttributes(p_c_str);

            if (fileAttr == INVALID_FILE_ATTRIBUTES) {
                return INVALID_FILE_ATTRIBUTES;
            }
            
            return 0;
    }
}

PLATFORM_Directory *PLATFORM_opendir(const char *p_c_str) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(p_c_str, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PLATFORM_Directory *p_dir = malloc(sizeof(PLATFORM_Directory));
    p_dir->handle = hFind;
    return p_dir;
}

void PLATFORM_closedir(PLATFORM_Directory *p_dir) {
    if (!p_dir)
        return;

    FindClose(p_dir->handle);

    free(p_dir);
}

bool PLATFORM_mkdir(const char *p_c_str, uint32_t file_code) {
    return !CreateDirectory(p_c_str, 0);
}

#endif
