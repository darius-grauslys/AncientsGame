#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "defines.h"

void initialize_font_manager(
        Font_Manager *p_font_manager);

Font *allocate_font_from__font_manager(
        Font_Manager *p_font_manager);

void release_font_from__font_manager(
        Font_Manager *p_font_manager,
        Font *p_font);

#endif
