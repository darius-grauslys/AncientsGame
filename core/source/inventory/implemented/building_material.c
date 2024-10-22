#include <inventory/implemented/building_material.h>
#include <inventory/item.h>

void initialize_item_as__building_material(
        Item *p_item,
        Item_Kind the_kind_of__item,
        i32F20 weight_of_each__item,
        Tile_Kind the_kind_of__ground__this_item_builds,
        Tile_Cover_Kind the_kind_of__tile_cover__this_item_builds) {
    initialize_item(
            p_item,
            the_kind_of__item,
            ITEM_USAGE_FLAGS__NONE,
            ITEM_FILTER_FLAGS__NONE,
            weight_of_each__item,
            0, 0, 0);

    p_item->the_kind_of__ground__this_item_builds =
        the_kind_of__ground__this_item_builds;
    p_item->the_kind_of__tile_cover__this_item_builds =
        the_kind_of__tile_cover__this_item_builds;
}
