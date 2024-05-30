#include "world/world.h"
#include <entity/controllers/entity_handlers.h>
#include <game.h>

void m_dispose_entity__default(
        Entity *this_entity,
        Game *game) {
    release_entity_from__world(game, this_entity);
}
