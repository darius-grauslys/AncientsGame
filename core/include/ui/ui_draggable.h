#ifndef UI_DRAGGABLE_H
#define UI_DRAGGABLE_H
#include <defines.h>

// TODO: move to private header
void init_ui_draggable(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_draggable);

void f_ui_draggable__dragged_handler__default(
        UI_Element *p_this_draggable);

#endif
