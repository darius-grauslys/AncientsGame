#include <nds.h>
#include <ui/nds_ui.h>
#include <assets/ui/_ui_tiles.h>

void NDS_set_ui_to__debug(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(_ui_tilesMap, 
            p_gfx_context->background_ui
            .gfx_map,
            _ui_tilesMapLen);
	dmaCopy(_ui_tilesMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            _ui_tilesMapLen);
}
