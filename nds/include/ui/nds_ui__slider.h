#ifndef NDS_UI__SLIDER_H
#define NDS_UI__SLIDER_H

#include <defines.h>

void NDS_initialize_ui_element_as__nds_slider(
        UI_Element *p_ui_element,
        Vector__3i32 position,
        Quantity__u32 width,
        Quantity__u32 height,
        bool is_snapped_x_or_y__axis,
        PLATFORM_Sprite *p_PLATFORM_sprite);

#endif
