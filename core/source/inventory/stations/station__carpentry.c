#include "defines_weak.h"
#include "inventory/station_manager.h"
#include "inventory/station_record.h"
#include <inventory/stations/station__carpentry.h>

void register_into_station_manager__carpentry_station(
        Station_Manager *p_station_manager) {
    register_station_into__station_manager(
            p_station_manager, 
            Station_Kind__Carpentry, 
            Item_Kind__Hammer__Iron, 
            Item_Kind__Chisel__Iron, 
            f_station_handler__use__default);
}
