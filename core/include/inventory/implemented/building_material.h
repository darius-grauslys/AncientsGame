#ifndef BUILDING_MATERIAL_H
#define BUILDING_MATERIAL_H

#include <defines.h>

void initialize_item_as__building_material(
        Item *p_item,
        Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Tile_Kind the_kind_of__ground__this_item_builds,
        Tile_Cover_Kind the_kind_of__tile_cover__this_item_builds);

static inline
Item get_building_material(
        enum Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Tile_Kind the_kind_of__ground__this_item_builds,
        Tile_Cover_Kind the_kind_of__tile_cover__this_item_builds) {
    Item building_material;
    initialize_item_as__building_material(
            &building_material, 
            the_kind_of__item,
            weight_of_each__item, 
            the_kind_of__ground__this_item_builds,
            the_kind_of__tile_cover__this_item_builds);
    return building_material;
}

#endif
