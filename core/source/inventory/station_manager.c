#include "defines.h"
#include "defines_weak.h"
#include "inventory/station_record.h"
#include "inventory/stations/station__carpentry.h"
#include <inventory/station_manager.h>

static inline
Station_Record *get_p_station_record_by__index_from__station_manager(
        Station_Manager *p_station_manager,
        Index__u32 index_of__station) {
#ifndef NDEBUG
    if (index_of__station < 0
            || index_of__station > Station_Kind__Unknown) {
        debug_error("get_p_station_record_by__index_from__station_manager, index_of__station illegal: %d", index_of__station);
        return 0;
    }
#endif
    return &p_station_manager->stations[index_of__station];
}

static inline 
Signed_Index__i32 get_index_of__station_mapping_from__station_manager(
        Item_Kind the_first_kind_of__tool,
        Item_Kind the_second_kind_of__tool) {
#ifndef NDEBUG
    if (the_first_kind_of__tool < Item_Kind__TOOLS
            || the_first_kind_of__tool >= (Item_Kind__TOOLS
                + ITEM_TOOL_MAX_QUANTITY_OF)) {
        debug_error("get_index_of__station_mapping_from__station_manager, illegal first tool: %d", the_first_kind_of__tool);
        return -1;
    }
    if (the_second_kind_of__tool < Item_Kind__TOOLS
            || the_second_kind_of__tool >= (Item_Kind__TOOLS
                + ITEM_TOOL_MAX_QUANTITY_OF)) {
        debug_error("get_index_of__station_mapping_from__station_manager, illegal second tool: %d", the_second_kind_of__tool);
        return -1;
    }
#endif
    return (the_first_kind_of__tool - Item_Kind__TOOLS)
        * (the_second_kind_of__tool - Item_Kind__TOOLS);
}

void initialize_station_manager(
        Station_Manager *p_station_manager) {
    for (Index__u32 index_of__station = 0;
            index_of__station < Station_Kind__Unknown;
            index_of__station++) {
        Station_Record *p_station_record =
            get_p_station_record_by__index_from__station_manager(
                    p_station_manager, 
                    index_of__station);
        initialize_station_record_as__uninitialized(
                p_station_record);
    }
}

void register_station_into__station_manager(
        Station_Manager *p_station_manager,
        Station_Kind the_kind_of__station,
        Item_Kind the_first_kind_of__tool_required,
        Item_Kind the_second_kind_of__tool_required,
        f_Station_Handler__Use f_station_handler__use) {
    Station_Record *p_station =
        get_p_station_record_by__index_from__station_manager(
                p_station_manager, 
                the_kind_of__station);

    initialize_station_record(
            p_station, 
            f_station_handler__use, 
            the_first_kind_of__tool_required, 
            the_second_kind_of__tool_required);
}

void register_core_stations_into__station_manager(
        Station_Manager *p_station_manager) {
    register_into_station_manager__carpentry_station(
            p_station_manager);
}

void register_mapping_of__tool_pairing_to__station_record_in__station_manager(
        Station_Manager *p_station_manager,
        Item_Kind the_first_kind_of__tool_required,
        Item_Kind the_second_kind_of__tool_required,
        Station_Kind the_kind_of__station_that_is__mapped) {
    p_station_manager->map_of__tools_to__station
        [get_index_of__station_mapping_from__station_manager(
                the_first_kind_of__tool_required, 
                the_second_kind_of__tool_required)] =
        the_kind_of__station_that_is__mapped;
}

Station_Kind get_the_kind_of__station_that__these_tools_create(
        Station_Manager *p_station_manager,
        Item_Kind the_first_kind_of__tool,
        Item_Kind the_second_kind_of__tool) {
    return p_station_manager->map_of__tools_to__station
        [get_index_of__station_mapping_from__station_manager(
                the_first_kind_of__tool, 
                the_second_kind_of__tool)];
}
