#include <entity/controllers/entity_handlers.h>
#include <game.h>

void m_dispose_entity__default(
        Entity *this_entity,
        Game *game) {
    release_entity(game, this_entity);
}
