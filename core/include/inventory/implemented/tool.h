#ifndef TOOL_H
#define TOOL_H

#include "defines_weak.h"

/// 
/// use_tool assumes that the specified tile
/// can be harvested.
///
/// p_tile__other refers to an adjacent tile
/// which is also appart of the ore. This is
/// for Large ore deposits.
///
void use_tool__harvest_ore(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile,
        Tile *p_tile__other);

void use_tool__harvest_tree(
        Game *p_game,
        Entity *p_entity_user,
        Tile *p_tile);

#endif
