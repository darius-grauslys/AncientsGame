#include <serialization/sdl_filesystem.h>

#ifdef __unix__
#include <serialization/unix/unix_filesystem.h>
#endif

bool SDL_get_path_to__the_game(char path[1024]) {
#ifdef __unix__
    return UNIX_get_path_to__the_game(path);
#elif
    return false;
#endif
}

bool SDL_get_path_to__assets(
        Asset_Directory_Kind the_kind_of__asset_directory,
        char path[1024]) {
#ifdef __unix__
    return UNIX_get_path_to__assets(
            the_kind_of__asset_directory,
            path);
#elif
    return false;
#endif
}

bool SDL_get_path_to__texture_file(
        Asset_Directory_Kind the_kind_of__asset_directory,
        char path[1024],
        SDL_Texture_String__Const p_SDL_texture_string) {
#ifdef __unix__
    return UNIX_get_path_to__texture_file(
            the_kind_of__asset_directory,
            path,
            p_SDL_texture_string);
#elif
    return false;
#endif
}
