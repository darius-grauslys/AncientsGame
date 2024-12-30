#ifndef ALIASED_TEXTURE_MANAGER_H
#define ALIASED_TEXTURE_MANAGER_H

#include "defines.h"

void initialize_aliased_texture_manager(
        Aliased_Texture_Manager *p_aliased_texture_manager);

///
/// WARNING: You do not own the returned texture.
/// NOTE: repeated names will shadow textures in an
/// unpredictable manner.
///
PLATFORM_Texture *allocate_p_PLATFORM_texture_with__alias(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Texture_Name__c_str name_of__texture__c_str,
        Texture_Flags texture_flags);

PLATFORM_Texture *get_p_PLATFORM_texture_by__alias(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Texture_Name__c_str name_of__texture__c_str);

void release_all_aliased_textures(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Aliased_Texture_Manager *p_aliased_texture_manager);

#endif
