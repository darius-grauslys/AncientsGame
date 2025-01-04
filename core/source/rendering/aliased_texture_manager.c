#include "rendering/aliased_texture_manager.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/aliased_texture.h"
#include "defines.h"
#include "rendering/texture_strings.h"

static inline
Aliased_Texture *get_p_aliased_texture_by__index_from__aliased_texture_manager(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Index__u32 index_of__aliased_texture) {
    if (MAX_QUANTITY_OF__ALIASED_TEXTURES
            <= index_of__aliased_texture) {
        debug_error("get_p_aliased_texture_by__index_from__aliased_texture_manager, index out of bounds: %d/%d", index_of__aliased_texture, MAX_QUANTITY_OF__ALIASED_TEXTURES);
        return 0;
    }
    return &p_aliased_texture_manager
        ->aliased_textures[index_of__aliased_texture];
}

void initialize_aliased_texture_manager(
        Aliased_Texture_Manager *p_aliased_texture_manager) {
    for (Index__u32 index_of__aliased_texture = 0;
            index_of__aliased_texture
            < MAX_QUANTITY_OF__ALIASED_TEXTURES;
            index_of__aliased_texture++) {
        Aliased_Texture *p_aliased_texture =
            get_p_aliased_texture_by__index_from__aliased_texture_manager(
                    p_aliased_texture_manager, 
                    index_of__aliased_texture);

        initialize_aliased_texture(p_aliased_texture);
    }
}

Aliased_Texture *get_p_aliased_texture_thats__available_from__manager(
        Aliased_Texture_Manager *p_aliased_texture_manager) {
    Aliased_Texture *p_aliased_texture__available = 0;
    for (Index__u32 index_of__aliased_texture = 0;
            index_of__aliased_texture
            < MAX_QUANTITY_OF__ALIASED_TEXTURES;
            index_of__aliased_texture++) {
        Aliased_Texture *p_aliased_texture =
            get_p_aliased_texture_by__index_from__aliased_texture_manager(
                    p_aliased_texture_manager, 
                    index_of__aliased_texture);
        if (is_aliased_texture__used(p_aliased_texture)) {
            continue;
        }
        p_aliased_texture__available = 
            p_aliased_texture;
        break;
    }

    return p_aliased_texture__available;
}

///
/// WARNING: You do not own the returned texture.
///
PLATFORM_Texture *allocate_p_PLATFORM_texture_with__alias(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Texture_Name__c_str name_of__texture__c_str,
        Texture_Flags texture_flags) {
    if (!name_of__texture__c_str[0]) {
        debug_error("allocate_p_PLATFORM_texture_with__alias, alias cannot be empty.");
        return 0;
    }

    Aliased_Texture *p_aliased_texture__available =
        get_p_aliased_texture_thats__available_from__manager(
                p_aliased_texture_manager);
    if (!p_aliased_texture__available) {
        debug_error("allocate_p_PLATFORM_texture_with__alias, too many aliased textures are allocated.");
        return 0;
    }

    PLATFORM_Texture *P_PLATFORM_texture =
        PLATFORM_allocate_texture__TMP(
                p_PLATFORM_gfx_context, 
                p_PLATFORM_gfx_window,
                texture_flags);

    if (!P_PLATFORM_texture) {
        debug_error("allocate_p_PLATFORM_texture_with__alias, failed to allocate texture.");
        return 0;
    }

    set_c_str_of__aliased_texture(
            p_aliased_texture__available, 
            name_of__texture__c_str);
    give_PLATFORM_texture_to__aliased_texture(
            p_aliased_texture__available, 
            P_PLATFORM_texture);
    return P_PLATFORM_texture;
}

PLATFORM_Texture *load_p_PLATFORM_texture_from__path_with__alias(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Texture_Name__c_str name_of__texture__c_str,
        Texture_Flags texture_flags,
        const char *c_str__path) {
    if (!name_of__texture__c_str[0]) {
        debug_error("load_p_PLATFORM_texture_from__path_with__alias, alias cannot be empty.");
        return 0;
    }

    Aliased_Texture *p_aliased_texture__available =
        get_p_aliased_texture_thats__available_from__manager(
                p_aliased_texture_manager);
    if (!p_aliased_texture__available) {
        debug_error("load_p_PLATFORM_texture_from__path_with__alias, too many aliased textures are allocated.");
        return 0;
    }

    IO_path full_path;
    memset(full_path,
            0,
            sizeof(full_path));
    Quantity__u32 length_of__base_directory = 
        PLATFORM_get_base_directory(full_path);
    if (MAX_LENGTH_OF__IO_PATH 
            <= length_of__base_directory) {
        debug_error("load_p_PLATFORM_texture_from__path_with__alias, game directory exceeds MAX_LENGTH_OF__IO_PATH.");
        return 0;
    }
    full_path[length_of__base_directory++] = '/';
    memcpy(&full_path[length_of__base_directory],
            c_str__path,
            MAX_LENGTH_OF__IO_PATH
            - length_of__base_directory);

    PLATFORM_Texture *P_PLATFORM_texture =
        PLATFORM_allocate_texture_with__path__TMP(
                p_PLATFORM_gfx_context,
                p_PLATFORM_gfx_window,
                texture_flags,
                full_path);

    if (!P_PLATFORM_texture) {
        debug_error("load_p_PLATFORM_texture_from__path_with__alias, failed to allocate texture.");
        return 0;
    }

    set_c_str_of__aliased_texture(
            p_aliased_texture__available, 
            name_of__texture__c_str);
    give_PLATFORM_texture_to__aliased_texture(
            p_aliased_texture__available, 
            P_PLATFORM_texture);
    return P_PLATFORM_texture;
}

PLATFORM_Texture *get_p_PLATFORM_texture_by__alias(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Texture_Name__c_str name_of__texture__c_str) {
    Aliased_Texture *p_aliased_texture__matching = 0;
    for (Index__u32 index_of__aliased_texture = 0;
            index_of__aliased_texture
            < MAX_QUANTITY_OF__ALIASED_TEXTURES;
            index_of__aliased_texture++) {
        Aliased_Texture *p_aliased_texture =
            get_p_aliased_texture_by__index_from__aliased_texture_manager(
                    p_aliased_texture_manager, 
                    index_of__aliased_texture);
        if (!is_aliased_texture__used(p_aliased_texture)) {
            continue;
        }
        if (is_c_str_matching__aliased_texture(
                    p_aliased_texture, 
                    name_of__texture__c_str)) {
            p_aliased_texture__matching = 
                p_aliased_texture;
            break;
        }
    }
    if (!p_aliased_texture__matching) {
        name_of__texture__c_str[MAX_LENGTH_OF__TEXTURE_NAME-1] = 0;
        debug_error("get_p_PLATFORM_texture_by__alias, failed to find texture for given name: %s", name_of__texture__c_str);
        return 0;
    }

    return p_aliased_texture__matching
        ->P_PLATFORM_texture;
}

void release_all_aliased_textures(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Aliased_Texture_Manager *p_aliased_texture_manager) {
    for (Index__u32 index_of__aliased_texture = 0;
            index_of__aliased_texture
            < MAX_QUANTITY_OF__ALIASED_TEXTURES;
            index_of__aliased_texture++) {
        Aliased_Texture *p_aliased_texture =
            get_p_aliased_texture_by__index_from__aliased_texture_manager(
                    p_aliased_texture_manager, 
                    index_of__aliased_texture);
        PLATFORM_release_texture(
                p_PLATFORM_gfx_context, 
                p_aliased_texture->P_PLATFORM_texture);
        initialize_aliased_texture(p_aliased_texture);
    }
}

void load_aliased_textures(
        Game *p_game,
        Aliased_Texture_Manager *p_aliased_texture_manager) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    ///
    /// TILESHEETS
    ///

    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__tilesheet_ground__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__tilesheet_ground__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__tilesheet_cover__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__tilesheet_cover__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__tilesheet_ui__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__tilesheet_ui__c_str);

    ///
    /// ENTITIES
    ///
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__player__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__player__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__player__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__player__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__items__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__items__c_str);

    ///
    /// UI sprites
    ///
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui_8x8__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui_8x8__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui_16x16__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui_16x16__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui_32x32__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui_32x32__c_str);
}
