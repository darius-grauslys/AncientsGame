#include "world/world.h"
#include <entity/handlers/entity_handlers.h>
#include <game.h>

void m_entity_dispose_handler__default(
        Entity *p_this_entity,
        Game *p_game) {
        debug_info("release_entity_from__world: %p",
                p_this_entity);
}
