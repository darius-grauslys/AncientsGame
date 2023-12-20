#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <defines.h>

typedef struct UI_Element_t {

} UI_Element;

void move_ui_element(UI_Overlay* overlay, UI_Element* element, int x, int y);
void resize_ui_element(UI_Overlay* overlay, UI_Element* element, int w, int h);

#endif
