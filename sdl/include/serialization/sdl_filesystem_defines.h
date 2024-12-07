#ifndef SDL_FILESYSTEM_DEFINES_H
#define SDL_FILESYSTEM_DEFINES_H

typedef enum {
    Asset_Directory_Kind__None,
    Asset_Directory_Kind__Assets,
    Asset_Directory_Kind__Audio,
    Asset_Directory_Kind__Entities,
    Asset_Directory_Kind__Entity_Sprite__16x16,
    Asset_Directory_Kind__Entity_Sprite__8x8,
    Asset_Directory_Kind__UI,
    Asset_Directory_Kind__UI__Default,
    Asset_Directory_Kind__UI__Font,
    Asset_Directory_Kind__UI__Log,
    Asset_Directory_Kind__UI__Sprite__8x8,
    Asset_Directory_Kind__UI__Sprite__16x16,
    Asset_Directory_Kind__UI__Sprite__32x32,
    Asset_Directory_Kind__UI__Typer,
    Asset_Directory_Kind__World,
} Asset_Directory_Kind;


bool SDL_get_path_to__the_game(char path[1024]);

#ifdef __unix__
#define PATH_SEPERATOR '/'
#elif
#define PATH_SEPERATOR '\\'
#endif

#endif
