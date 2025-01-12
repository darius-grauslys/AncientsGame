#include "ui/ui_tile_map_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform_defines.h"
#include "ui/ui_tile_map.h"

const UI_Tile_Map__Wrapper UI_TILE_MAP__WRAPPER__INVALID = {
    0,
    0,
    0,
    UI_Tile_Map_Size__None
};

static inline
UI_Tile_Map__Small *get_p_ui_tile_map_small_by__index_from__ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map_manager,
        Index__u32 index_of__ui_tile_map__small) {
    return &p_ui_tile_map_manager
        ->ui_tile_maps__small[
        index_of__ui_tile_map__small];
}
static inline
UI_Tile_Map__Medium *get_p_ui_tile_map_medium_by__index_from__ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map_manager,
        Index__u32 index_of__ui_tile_map__medium) {
    return &p_ui_tile_map_manager
        ->ui_tile_maps__medium[
        index_of__ui_tile_map__medium];
}
static inline
UI_Tile_Map__Large *get_p_ui_tile_map_large_by__index_from__ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map_manager,
        Index__u32 index_of__ui_tile_map__large) {
    return &p_ui_tile_map_manager
        ->ui_tile_maps__large[
        index_of__ui_tile_map__large];
}

void initialize_ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map__manager) {
    for (Index__u32 index_of__ui_tile_map__small = 0;
            index_of__ui_tile_map__small
            < UI_TILE_MAP__SMALL__MAX_QUANTITY_OF;
            index_of__ui_tile_map__small++) {
        UI_Tile_Map__Small *p_ui_tile_map__small =
            get_p_ui_tile_map_small_by__index_from__ui_tile_map_manager(
                    p_ui_tile_map__manager, 
                    index_of__ui_tile_map__small);
        initialize_ui_tile_map__small_as__deallocated(
                p_ui_tile_map__small);
    }
    for (Index__u32 index_of__ui_tile_map__medium = 0;
            index_of__ui_tile_map__medium
            < UI_TILE_MAP__MEDIUM__MAX_QUANTITY_OF;
            index_of__ui_tile_map__medium++) {
        UI_Tile_Map__Medium *p_ui_tile_map__medium =
            get_p_ui_tile_map_medium_by__index_from__ui_tile_map_manager(
                    p_ui_tile_map__manager, 
                    index_of__ui_tile_map__medium);
        initialize_ui_tile_map__medium_as__deallocated(
                p_ui_tile_map__medium);
    }
    for (Index__u32 index_of__ui_tile_map__large = 0;
            index_of__ui_tile_map__large
            < UI_TILE_MAP__LARGE__MAX_QUANTITY_OF;
            index_of__ui_tile_map__large++) {
        UI_Tile_Map__Large *p_ui_tile_map__large =
            get_p_ui_tile_map_large_by__index_from__ui_tile_map_manager(
                    p_ui_tile_map__manager, 
                    index_of__ui_tile_map__large);
        initialize_ui_tile_map__large_as__deallocated(
                p_ui_tile_map__large);
    }
}

UI_Tile_Map__Wrapper allocate_ui_tile_map_with__ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map_manager,
        UI_Tile_Map_Size catagory_size_of__ui_tile_map) {
    switch (catagory_size_of__ui_tile_map) {
        default:
            debug_error("allocate_ui_tile_map_with__ui_tile_map_manager, invalid size catagory.");
            return UI_TILE_MAP__WRAPPER__INVALID;
        case UI_Tile_Map_Size__Large:
            for (Index__u32 index_of__ui_tile_map__large = 0;
                    index_of__ui_tile_map__large
                    < UI_TILE_MAP__LARGE__MAX_QUANTITY_OF;
                    index_of__ui_tile_map__large++) {
                UI_Tile_Map__Large *p_ui_tile_map__large =
                    get_p_ui_tile_map_large_by__index_from__ui_tile_map_manager(
                            p_ui_tile_map_manager, 
                            index_of__ui_tile_map__large);
                if (is_ui_tile_map_flags__allocated(
                            p_ui_tile_map__large
                            ->ui_tile_map__flags)) {
                    continue;
                }

                set_ui_tile_map_flags_as__allocated(
                        &p_ui_tile_map__large
                        ->ui_tile_map__flags);

                return ui_tile_map__large_to__ui_tile_map_wrapper(
                        p_ui_tile_map__large);
            }
            return UI_TILE_MAP__WRAPPER__INVALID;
        case UI_Tile_Map_Size__Medium:
            for (Index__u32 index_of__ui_tile_map__medium = 0;
                    index_of__ui_tile_map__medium
                    < UI_TILE_MAP__LARGE__MAX_QUANTITY_OF;
                    index_of__ui_tile_map__medium++) {
                UI_Tile_Map__Medium *p_ui_tile_map__medium =
                    get_p_ui_tile_map_medium_by__index_from__ui_tile_map_manager(
                            p_ui_tile_map_manager, 
                            index_of__ui_tile_map__medium);
                if (is_ui_tile_map_flags__allocated(
                            p_ui_tile_map__medium
                            ->ui_tile_map__flags)) {
                    continue;
                }

                set_ui_tile_map_flags_as__allocated(
                        &p_ui_tile_map__medium
                        ->ui_tile_map__flags);

                return ui_tile_map__medium_to__ui_tile_map_wrapper(
                        p_ui_tile_map__medium);
            }
            return UI_TILE_MAP__WRAPPER__INVALID;
        case UI_Tile_Map_Size__Small:
            for (Index__u32 index_of__ui_tile_map__small = 0;
                    index_of__ui_tile_map__small
                    < UI_TILE_MAP__LARGE__MAX_QUANTITY_OF;
                    index_of__ui_tile_map__small++) {
                UI_Tile_Map__Small *p_ui_tile_map__small =
                    get_p_ui_tile_map_small_by__index_from__ui_tile_map_manager(
                            p_ui_tile_map_manager, 
                            index_of__ui_tile_map__small);
                if (is_ui_tile_map_flags__allocated(
                            p_ui_tile_map__small
                            ->ui_tile_map__flags)) {
                    continue;
                }

                set_ui_tile_map_flags_as__allocated(
                        &p_ui_tile_map__small
                        ->ui_tile_map__flags);

                return ui_tile_map__small_to__ui_tile_map_wrapper(
                        p_ui_tile_map__small);
            }
            return UI_TILE_MAP__WRAPPER__INVALID;
    }
}

void release_ui_tile_map_with__ui_tile_map_manager(
        UI_Tile_Map_Manager *p_ui_tile_map_manager,
        UI_Tile_Map__Wrapper ui_tile_map__wrapper) {
    if (!is_ui_tile_map__wrapper__valid(
                ui_tile_map__wrapper)) {
        debug_error("release_ui_tile_map_with__ui_tile_map_manager, ui_tile_map__wrapper is invalid.");
        return;
    }

    switch (get_catagory_size_of__ui_tile_map__wrapper(
                ui_tile_map__wrapper)) {
        default:
            debug_info("release_ui_tile_map_with__ui_tile_map_manager, unsupported catagory size.");
            break;
        case UI_Tile_Map_Size__Large:
            for (Index__u32 index_of__ui_tile_map__large = 0;
                    index_of__ui_tile_map__large
                    < UI_TILE_MAP__LARGE__MAX_QUANTITY_OF;
                    index_of__ui_tile_map__large++) {
                UI_Tile_Map__Large *p_ui_tile_map__large =
                    get_p_ui_tile_map_large_by__index_from__ui_tile_map_manager(
                            p_ui_tile_map_manager, 
                            index_of__ui_tile_map__large);
                if (!is_ui_tile_map_flags__allocated(
                            p_ui_tile_map__large
                            ->ui_tile_map__flags)) {
                    continue;
                }

                if (p_ui_tile_map__large
                        ->ui_tile_data__large
                        == ui_tile_map__wrapper
                        .p_ui_tile_data) {
                    initialize_ui_tile_map__large_as__deallocated(
                            p_ui_tile_map__large);
                    return;
                }
            }
            break;
        case UI_Tile_Map_Size__Medium:
            for (Index__u32 index_of__ui_tile_map__medium = 0;
                    index_of__ui_tile_map__medium
                    < UI_TILE_MAP__LARGE__MAX_QUANTITY_OF;
                    index_of__ui_tile_map__medium++) {
                UI_Tile_Map__Medium *p_ui_tile_map__medium =
                    get_p_ui_tile_map_medium_by__index_from__ui_tile_map_manager(
                            p_ui_tile_map_manager, 
                            index_of__ui_tile_map__medium);
                if (!is_ui_tile_map_flags__allocated(
                            p_ui_tile_map__medium
                            ->ui_tile_map__flags)) {
                    continue;
                }

                if (p_ui_tile_map__medium
                        ->ui_tile_data__medium
                        == ui_tile_map__wrapper
                        .p_ui_tile_data) {
                    initialize_ui_tile_map__medium_as__deallocated(
                            p_ui_tile_map__medium);
                    return;
                }
            }
            break;
        case UI_Tile_Map_Size__Small:
            for (Index__u32 index_of__ui_tile_map__small = 0;
                    index_of__ui_tile_map__small
                    < UI_TILE_MAP__LARGE__MAX_QUANTITY_OF;
                    index_of__ui_tile_map__small++) {
                UI_Tile_Map__Small *p_ui_tile_map__small =
                    get_p_ui_tile_map_small_by__index_from__ui_tile_map_manager(
                            p_ui_tile_map_manager, 
                            index_of__ui_tile_map__small);
                if (!is_ui_tile_map_flags__allocated(
                            p_ui_tile_map__small
                            ->ui_tile_map__flags)) {
                    continue;
                }

                if (p_ui_tile_map__small
                        ->ui_tile_data__small
                        == ui_tile_map__wrapper
                        .p_ui_tile_data) {
                    initialize_ui_tile_map__small_as__deallocated(
                            p_ui_tile_map__small);
                    return;
                }
            }
            break;
    }
    debug_error("release_ui_tile_map_with__ui_tile_map_manager, ui_tile_map__wrapper does not wrap fields managed from this manager. Was it even allocated from this manager?");
}
