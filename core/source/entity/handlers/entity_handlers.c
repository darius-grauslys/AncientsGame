#include "world/world.h"
#include <entity/handlers/entity_handlers.h>
#include <game.h>

void m_entity_dispose_handler__default(
        Entity *this_entity,
        Game *game) {
    release_entity_from__world(game, this_entity);
}
