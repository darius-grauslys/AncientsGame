#ifndef UI_OVERLAY_H
#define UI_OVERLAY_H

#include <defines.h>

typedef struct UI_Overlay_t {

} UI_Overlay;

void add_ui_element_to_overlay(UI_Overlay* overlay, UI_Element* element);
void remove_ui_element_from_overlay(UI_Overlay* overlay, UI_Element* element);

#endif
