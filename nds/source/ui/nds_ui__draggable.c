#include <platform_defines.h>
#include "defines.h"
#include "ui/nds_ui.h"
#include "ui/ui_draggable.h"
#include "ui/ui_element.h"
#include "vectors.h"
#include <ui/nds_ui__draggable.h>

void m_NDS_ui_dragged__handler(
        UI_Element *p_this_ui_element,
        Game *p_game) {
    m_ui_draggable__dragged_handler__default(
            p_this_ui_element, p_game);
}
