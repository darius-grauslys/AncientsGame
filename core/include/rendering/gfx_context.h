#ifndef GFX_CONTEXT_H
#define GFX_CONTEXT_H

void PLATFORM_init_gfx_context(PLATFORM_Gfx_Context *gfx_context);

///
/// On NDS, this will init both main and sub.
///
void PLATFORM_init_rendering__menu(PLATFORM_Gfx_Context *gfx_context);
/// 
/// On NDS, this will init both main and sub.
///
void PLATFORM_init_rendering__game(PLATFORM_Gfx_Context *gfx_context);

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager);

#endif
