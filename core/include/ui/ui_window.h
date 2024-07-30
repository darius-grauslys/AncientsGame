#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "defines_weak.h"
static inline
bool is_ui_window_kind_of__this_kind(
        enum UI_Window_Kind the_kind_of__ui_window,
        enum UI_Window_Kind is_this_kind_of__ui_window) {
    return the_kind_of__ui_window
        == is_this_kind_of__ui_window;
}

#endif
