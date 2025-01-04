#include "rendering/sprite_gfx_allocator_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/implemented/skeleton/entity__skeleton.h"
#include "game.h"
#include "platform.h"

#include "entity/implemented/player/entity__player.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/texture_strings.h"

static inline
f_Sprite_Gfx_Allocator *get_pf_sprite_gfx_allocator_for__entity_by__index_in__manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Entity_Kind the_kind_of__entity) {
    if (Entity_Kind__Unknown <= (u32)the_kind_of__entity) {
        debug_error("get_f_sprite_gfx_allocator_for__entity_by__index_in__manager, the_kind_of__entity is out of bounds.");
        return 0;
    }
    switch (the_kind_of__entity) {
        default:
            break;
        case Entity_Kind__Particle:
            debug_error("get_f_sprite_gfx_allocator_for__entity_by__index_in__manager, cannot allocate particle, use allocate_sprite__particle instead.");
            return 0;
    }

    return &p_sprite_gfx_allocator_manager
        ->F_sprite_gfx_allocators_for__entities[
            the_kind_of__entity];
}

static inline
f_Sprite_Gfx_Allocator *get_pf_sprite_gfx_allocator_for__particle_by__index_in__manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Particle_Kind the_kind_of__particle) {
    if (Particle_Kind__Unknown <= (u32)the_kind_of__particle) {
        debug_error("get_f_sprite_gfx_allocator_for__particle_by__index_in__manager, the_kind_of__particle is out of bounds.");
        return 0;
    }

    return &p_sprite_gfx_allocator_manager
        ->F_sprite_gfx_allocators_for__particles[
            the_kind_of__particle];
}

static inline
f_Sprite_Gfx_Allocator *get_pf_sprite_gfx_allocator_for__ui_by__index_in__manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        UI_Sprite_Kind the_kind_of__ui) {
    if (UI_Sprite_Kind__Unknown <= (u32)the_kind_of__ui) {
        debug_error("get_f_sprite_gfx_allocator_for__ui_by__index_in__manager, the_kind_of__ui is out of bounds.");
        return 0;
    }

    return &p_sprite_gfx_allocator_manager
        ->F_sprite_gfx_allocators_for__ui[
            the_kind_of__ui];
}

static inline
f_Sprite_Gfx_Allocator *get_pf_sprite_gfx_allocator_for__item_by__index_in__manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Item_Kind the_kind_of__item) {
    if (Item_Kind__Unknown <= (u32)the_kind_of__item) {
        debug_error("get_f_sprite_gfx_allocator_for__item_by__index_in__manager, the_kind_of__item is out of bounds.");
        return 0;
    }

    return &p_sprite_gfx_allocator_manager
        ->F_sprite_gfx_allocators_for__items[
            the_kind_of__item];
}

void initialize_sprite_gfx_allocator_manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager) {
    memset(
            p_sprite_gfx_allocator_manager
            ->F_sprite_gfx_allocators_for__entities,
            0,
            sizeof(p_sprite_gfx_allocator_manager
                ->F_sprite_gfx_allocators_for__entities));
    memset(
            p_sprite_gfx_allocator_manager
            ->F_sprite_gfx_allocators_for__particles,
            0,
            sizeof(p_sprite_gfx_allocator_manager
                ->F_sprite_gfx_allocators_for__particles));
    memset(
            p_sprite_gfx_allocator_manager
            ->F_sprite_gfx_allocators_for__ui,
            0,
            sizeof(p_sprite_gfx_allocator_manager
                ->F_sprite_gfx_allocators_for__ui));
    memset(
            p_sprite_gfx_allocator_manager
            ->F_sprite_gfx_allocators_for__items,
            0,
            sizeof(p_sprite_gfx_allocator_manager
                ->F_sprite_gfx_allocators_for__items));
}

bool allocate_sprite__entity(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        Entity_Kind the_kind_of__entity) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__entity_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__entity);

    if (!pf_sprite_gfx_allocator || !*pf_sprite_gfx_allocator)
        return false;
    
    return
        (*pf_sprite_gfx_allocator)(
                p_game,
                p_PLATFORM_gfx_window,
                p_sprite_wrapper,
                the_kind_of__entity);
}

bool allocate_sprite__particle(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        Particle_Kind the_kind_of__particle) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__particle_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__particle);

    if (!pf_sprite_gfx_allocator || !*pf_sprite_gfx_allocator)
        return false;
    
    return
        (*pf_sprite_gfx_allocator)(
                p_game,
                p_PLATFORM_gfx_window,
                p_sprite_wrapper,
                the_kind_of__particle);
}

bool allocate_sprite__ui(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        UI_Sprite_Kind the_kind_of__ui) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__ui_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__ui);

    if (!pf_sprite_gfx_allocator || !*pf_sprite_gfx_allocator)
        return false;
    
    return
        (*pf_sprite_gfx_allocator)(
                p_game,
                p_PLATFORM_gfx_window,
                p_sprite_wrapper,
                the_kind_of__ui);
}

bool allocate_sprite__item(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        Item_Kind the_kind_of__item) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__item_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__item);

    if (!pf_sprite_gfx_allocator || !*pf_sprite_gfx_allocator)
        return false;
    
    return
        (*pf_sprite_gfx_allocator)(
                p_game,
                p_PLATFORM_gfx_window,
                p_sprite_wrapper,
                the_kind_of__item);
}

void register_sprite_gfx_allocator_for__entity(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Entity_Kind the_kind_of__entity,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__entity_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__entity);

    if (!pf_sprite_gfx_allocator) {
        debug_error("register_sprite_gfx_allocator_for__entity, failed to register.");
        return;
    }

    if (!*pf_sprite_gfx_allocator) {
        debug_warning("register_sprite_gfx_allocator_for__entity, entry overridden: %d",
                the_kind_of__entity);
    }

    *pf_sprite_gfx_allocator = 
        f_sprite_gfx_allocator;
}

void register_sprite_gfx_allocator_for__particle(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Particle_Kind the_kind_of__particle,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__particle_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__particle);

    if (!pf_sprite_gfx_allocator) {
        debug_error("register_sprite_gfx_allocator_for__particle, failed to register.");
        return;
    }

    if (!*pf_sprite_gfx_allocator) {
        debug_warning("register_sprite_gfx_allocator_for__particle, entry overridden: %d",
                the_kind_of__particle);
    }

    *pf_sprite_gfx_allocator = 
        f_sprite_gfx_allocator;
}

void register_sprite_gfx_allocator_for__ui(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        UI_Sprite_Kind the_kind_of__ui,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__ui_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__ui);

    if (!pf_sprite_gfx_allocator) {
        debug_error("register_sprite_gfx_allocator_for__ui, failed to register.");
        return;
    }

    if (!*pf_sprite_gfx_allocator) {
        debug_warning("register_sprite_gfx_allocator_for__ui, entry overridden: %d",
                the_kind_of__ui);
    }

    *pf_sprite_gfx_allocator = 
        f_sprite_gfx_allocator;
}

void register_sprite_gfx_allocator_for__item(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Item_Kind the_kind_of__item,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator) {
    f_Sprite_Gfx_Allocator *pf_sprite_gfx_allocator =
        get_pf_sprite_gfx_allocator_for__item_by__index_in__manager(
                p_sprite_gfx_allocator_manager, 
                the_kind_of__item);

    if (!pf_sprite_gfx_allocator) {
        debug_error("register_sprite_gfx_allocator_for__item, failed to register.");
        return;
    }

    if (!*pf_sprite_gfx_allocator) {
        debug_warning("register_sprite_gfx_allocator_for__item, entry overridden: %d",
                the_kind_of__item);
    }

    *pf_sprite_gfx_allocator = 
        f_sprite_gfx_allocator;
}

bool f_sprite_gfx_allocator__item(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Wrapper *p_sprite_wrapper,
        u32 enum_value) {
    Aliased_Texture_Manager *p_aliased_texture_manager =
        get_p_aliased_texture_manager_from__game(p_game);
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    PLATFORM_Texture *p_PLATFORM_texture_for__items =
        get_p_PLATFORM_texture_by__alias(
                p_aliased_texture_manager, 
                name_of__texture__items__c_str);

    if (!p_PLATFORM_texture_for__items)
        return 0;
    
    p_sprite_wrapper->p_sprite =
        PLATFORM_allocate_sprite__TMP(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_gfx_window,
            p_PLATFORM_texture_for__items, 
            TEXTURE_FLAG__SIZE_8x8);

    p_sprite_wrapper->frame__current = enum_value - 1;
    return p_sprite_wrapper->p_sprite;
}

void register_sprite_gfx_allocators_in__sprite_gfx_allocator_manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocation_manager) {
    register_sprite_gfx_allocator_for__entity(
            p_sprite_gfx_allocation_manager, 
            Entity_Kind__Player, 
            f_sprite_gfx_allocator__player);   
    register_sprite_gfx_allocator_for__entity(
            p_sprite_gfx_allocation_manager, 
            Entity_Kind__Skeleton, 
            f_sprite_gfx_allocator__skeleton);   

    for (Index__u32 index_of__item = 0;
            index_of__item < Item_Kind__Unknown;
            index_of__item++) {
        p_sprite_gfx_allocation_manager
            ->F_sprite_gfx_allocators_for__items[index_of__item] =
            f_sprite_gfx_allocator__item;
    }
}
