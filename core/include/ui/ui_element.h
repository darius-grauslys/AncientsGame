#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <defines.h>

static bool inline is_ui_element__enabled(UI_Element *ui_element) {
    return (bool)(ui_element->ui_flags & UI_FLAGS__BIT_IS_ENABLED);
}

#endif
