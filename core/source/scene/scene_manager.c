#include <scene/scene.h>
#include <scene/scene_manager.h>

void initialize_scene_manager(
        Scene_Manager *p_scene_manager) {
    p_scene_manager->p_active_scene = 0;
    for (Quantity__u8 scene_index=0;
            scene_index<SCENE_MAX_QUANTITY_OF;
            scene_index++) {
        initialize_scene(
                get_scene_ptr_from__scene_manager(
                    p_scene_manager, 
                    scene_index)
                );
    }
}
