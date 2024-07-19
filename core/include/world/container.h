#ifndef CONTAINER_H
#define CONTAINER_H

#include "defines_weak.h"
#include <defines.h>

///
/// Converts a regional tile vector
/// (1024x1024 chunk region) to a
/// uuid for an inventory.
///
/// TODO:   handle uuid collision.
///         In this case, normal collision resolution
///         is NOT sufficient. We cannot reassign
///         the container uuid, it must not collide.
///
///         So we will have to move whatever the
///         container uuid collided into.
///
///         Problem: how do we notify the inventory
///         owner that their inventory changed uui?
///
///         Proposal: Add a callback to Inventory
///         which will be invoked whenever it's
///         uuid get's moved. This will allow
///         the owner to modify it's serialized_field_ptr.
///
Identifier__u32 get_container__uuid(
        Tile_Vector__3i32 tile_vector__3i32);

#endif
