#include <serialization/unix/unix_filesystem.h>
#include <unistd.h>
#include <libgen.h>

#ifdef __unix__

bool UNIX_get_path_to__the_game(char path[1024]) {
    bool result = (bool)(uint64_t)realpath("/proc/self/exe", path);
    if (!result) return false;
    dirname(path);
    return access(path, F_OK) == 0;
}

bool UNIX_get_path_to__assets(
        Asset_Directory_Kind the_kind_of__asset_directory,
        char path[1024]) {
    char buffer[1024];
    if (!UNIX_get_path_to__the_game(buffer)) {
        return false;
    }
    switch (the_kind_of__asset_directory) {
        default:
            break;
        case Asset_Directory_Kind__Assets:
            snprintf(path,
                    1024,
                    "%s/%s",
                    buffer,
                    "assets");
            break;
        case Asset_Directory_Kind__Audio:
            snprintf(path,
                    1024,
                    "%s/%s",
                    buffer,
                    "assets/audio");
            break;
        case Asset_Directory_Kind__Entities:
            snprintf(path,
                    1024,
                    "%s/%s",
                    buffer,
                    "assets/entities");
            break;
        case Asset_Directory_Kind__Entity_Sprite__16x16:
            snprintf(path,
                    1024,
                    "%s/%s",
                    buffer,
                    "assets/entities/entity_sprite__16x16");
            break;
        case Asset_Directory_Kind__Entity_Sprite__8x8:
            snprintf(path,
                    1024,
                    "%s/%s",
                    buffer,
                    "assets/entities/entity_sprite__8x8");
            break;
        case Asset_Directory_Kind__UI:
            snprintf(path,
                    1024,
                    "%s/%s",
                    buffer,
                    "assets/ui");
            break;
        case Asset_Directory_Kind__World:
            snprintf(path,
                    1024,
                    "%s/%s",
                    buffer,
                    "assets/world");
            break;
    }
    return access(path, F_OK) == 0;
}

bool UNIX_get_path_to__texture_file(
        Asset_Directory_Kind the_kind_of__asset_directory,
        char path[1024],
        SDL_Texture_String__Const p_SDL_texture_string) {
    char buffer[1024];
    if (!UNIX_get_path_to__assets(
                the_kind_of__asset_directory,
                buffer)) {
        return false;
    }

    snprintf(path,
            1024,
            "%s/%s",
            buffer,
            (char*)p_SDL_texture_string);

    return access(path, F_OK) == 0;
}

#endif
