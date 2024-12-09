#include "defines_weak.h"
#include "serialization/sdl_filesystem_defines.h"
#include <serialization/unix/unix_filesystem.h>

#ifdef __unix__

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <libgen.h>

bool SDL_get_path_to__the_game(char path[1024]) {
    bool result = (bool)(uint64_t)realpath("/proc/self/exe", path);
    if (!result) return false;
    dirname(path);
    return access(path, F_OK) == 0;
}

typedef struct PLATFORM_Directory_t {
    DIR *p_UNIX_dir;
} PLATFORM_Directory;

int PLATFORM_access(const char *p_c_str, IO_Access_Kind io_access_kind) {
    switch (io_access_kind) {
        default:
            // TODO: impl the cases
            return access(p_c_str, F_OK);
    }
}

PLATFORM_Directory *PLATFORM_opendir(const char *p_c_str) {
    DIR *p_UNIX_dir = opendir(p_c_str);
    if (!p_UNIX_dir)
        return 0;
    PLATFORM_Directory *p_dir = malloc(sizeof(PLATFORM_Directory));
    p_dir->p_UNIX_dir = p_UNIX_dir;
    return p_dir;
}

void PLATFORM_closedir(PLATFORM_Directory *p_dir) {
    if (!p_dir)
        return;

    closedir(p_dir->p_UNIX_dir);

    free(p_dir);
}

bool PLATFORM_mkdir(const char *p_c_str, uint32_t file_code) {
    return mkdir(p_c_str, file_code);
}

#endif
