#ifndef STATION_RECORD_H
#define STATION_RECORD_H

#include <defines.h>

void initialize_station_record(
        Station_Record *p_station_record,
        f_Station_Handler__Use f_station_handler__use,
        Item_Kind the_first_kind_of__tool_required,
        Item_Kind the_second_kind_of__tool_required);

///
/// Prints to the game system log that the station is
/// not yet defined by any toolage.
///
bool f_station_handler__use__empty(
        Game *p_game,
        Entity *p_entity__user,
        Inventory *p_station__inventory);

///
/// Attempts crafting, nothing else.
/// Returns true if successful.
///
/// Wrap this in a helper for tool durability.
///
bool f_station_handler__use__default(
        Game *p_game,
        Entity *p_entity__user,
        Inventory *p_station__inventory);

static inline
void initialize_station_record_as__uninitialized(
        Station_Record *p_station_record) {
    initialize_station_record(
            p_station_record,
            f_station_handler__use__empty,
            Item_Kind__None,
            Item_Kind__None);
}

#endif
