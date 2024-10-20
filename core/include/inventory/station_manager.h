#ifndef STATION_MANAGER_H
#define STATION_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_station_manager(
        Station_Manager *p_station_manager);

void register_station_into__station_manager(
        Station_Manager *p_station_manager,
        Station_Kind the_kind_of__station,
        Item_Kind the_first_kind_of__tool_required,
        Item_Kind the_second_kind_of__tool_required,
        f_Station_Handler__Use f_use_station__handler);

void register_core_stations_into__station_manager(
        Station_Manager *p_station_manager);

void register_mapping_of__tool_pairing_to__station_record_in__station_manager(
        Station_Manager *p_station_manager,
        Item_Kind the_first_kind_of__tool_required,
        Item_Kind the_second_kind_of__tool_required,
        Station_Kind the_kind_of__station_that_is__mapped);

Station_Kind get_the_kind_of__station_that__these_tools_create(
        Station_Manager *p_station_manager,
        Item_Kind the_first_kind_of__tool,
        Item_Kind the_second_kind_of__tool);

#endif
