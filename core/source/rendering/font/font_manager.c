#include "rendering/font/font_manager.h"
#include "rendering/font/font.h"

static inline
Font *get_p_font_by__index_from__font_manager(
        Font_Manager *p_font_manager,
        Index__u32 index_of__font) {
#ifndef NDEBUG
    if (index_of__font >= MAX_QUANTITY_OF__FONT) {
        debug_error("get_p_font_by__index_from__font_manager, index out of bounds: %d/%d", index_of__font, MAX_QUANTITY_OF__FONT);
        return 0;
    }
#endif

    return &p_font_manager
        ->fonts[index_of__font];
}

void initialize_font_manager(
        Font_Manager *p_font_manager) {
    for (Index__u32 index_of__font = 0;
            index_of__font
            < MAX_QUANTITY_OF__FONT;
            index_of__font++) {
        Font *p_font = get_p_font_by__index_from__font_manager(
                p_font_manager, 
                index_of__font);
        initialize_font(p_font);
    }
}

Font *allocate_font_from__font_manager(
        Font_Manager *p_font_manager) {
    Font *p_font__available = 0;

    for (Index__u32 index_of__font = 0;
            index_of__font
            < MAX_QUANTITY_OF__FONT;
            index_of__font++) {
        Font *p_font = get_p_font_by__index_from__font_manager(
                p_font_manager, 
                index_of__font);
        if (is_font__allocated(p_font)) {
            continue;
        }

        p_font__available = p_font;
        break;
    }

    if (p_font__available) {
        set_font_as__allocated(p_font__available);
    } else {
        debug_error("allocate_font_from__font_manager, failed to allocate font.");
    }

    return p_font__available;
}

void release_font_from__font_manager(
        Font_Manager *p_font_manager,
        Font *p_font) {
#ifndef NDEBUG
    int index = p_font
        - p_font_manager->fonts;
    if (index >= MAX_QUANTITY_OF__FONT) {
        debug_error("release_font_from__font_manager, font was not allocated with this manager.");
        return;
    }
#endif

    initialize_font(p_font);
    set_font_as__deallocated(p_font);
}
