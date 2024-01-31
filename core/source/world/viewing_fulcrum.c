#include <world/viewing_fulcrum.h>
#include <collisions/hitbox_aabb.h>

///
/// Technically we could just inline
/// this init function, but its been put
/// here mainly so that the test suite
/// auto-generation script can pick it up.
///
void init_viewing_fulcrum(Viewing_Fulcrum *viewing_fulcrum) {
    init_hitbox(&viewing_fulcrum->fulcrum,
            VIEWING_FULCRUM__WIDTH,
            VIEWING_FULCRUM__LENGTH,
            0, 0, 0);
}
