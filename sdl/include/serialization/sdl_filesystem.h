#ifndef SDL_FILESYSTEM
#define SDL_FILESYSTEM

#include <sdl_defines.h>
#include <serialization/sdl_filesystem_defines.h>

extern PLATFORM_File_System_Context __SDL_file_system_context;

bool SDL_get_path_to__the_game(char path[1024]);

bool SDL_get_path_to__assets(
        Asset_Directory_Kind the_kind_of__asset_directory,
        char path[1024]);

bool SDL_get_path_to__texture_file(
        Asset_Directory_Kind the_kind_of__asset_directory,
        char path[1024],
        SDL_Texture_String__Const p_SDL_texture_string);

void SDL_poll_serialization_requests(
        Game *p_game);

#endif
