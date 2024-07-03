#ifndef SPRITE_H
#define SPRITE_H

#include "defines_weak.h"
#include "platform.h"
#include "rendering/handlers/nds_gfx_handler__player.h"
#include "rendering/texture.h"
#include <defines.h>

void initialize_sprite_gfx_allocator__lookup_table_for__entities(
        F_Sprite_Gfx_Allocator__Lookup_Table_For__Entities 
            sprite_gfx_allocator__lookup_table);

void initialize_sprite_gfx_allocator__lookup_table_for__particles(
        F_Sprite_Gfx_Allocator__Lookup_Table_For__Particles 
            sprite_gfx_allocator__lookup_table);

void f_sprite_gfx_allocator__handler__default(
        PLATFORM_Sprite *p_PLATFORM_sprite, 
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification);

static inline
void initialize_sprite_allocation_specification(
        Sprite_Allocation_Specification 
            *p_sprite_allocation_specification,
        Texture_Flags texture_flags,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window) {
    p_sprite_allocation_specification
        ->the_kind_of__sprite_allocation =
        Sprite_Allocation_Kind__None;
    
    initialize_texture_allocation_specification(
            &p_sprite_allocation_specification
                ->texture_allocation_specification, 
            texture_flags, 
            p_PLATFORM_graphics_window);
}

static inline
void initialize_sprite_allocation_specification_for__entity(
        Sprite_Allocation_Specification 
            *p_sprite_allocation_specification, 
        Texture_Flags texture_flags,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        enum Entity_Kind the_kind_of__entity) {
    p_sprite_allocation_specification
        ->the_kind_of__sprite_allocation =
        Sprite_Allocation_Kind__Entity;
    p_sprite_allocation_specification
        ->the_kind_of__entity_this__sprite_is =
        the_kind_of__entity;

    initialize_texture_allocation_specification(
            &p_sprite_allocation_specification
                ->texture_allocation_specification, 
            texture_flags, 
            p_PLATFORM_graphics_window);
}

static inline
void initialize_sprite_allocation_specification_for__item(
        Sprite_Allocation_Specification 
            *p_sprite_allocation_specification, 
        Texture_Flags texture_flags,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        enum Item_Kind the_kind_of__item) {
    p_sprite_allocation_specification
        ->the_kind_of__sprite_allocation =
        Sprite_Allocation_Kind__Item;
    p_sprite_allocation_specification
        ->the_kind_of__item_this__sprite_is =
        the_kind_of__item;

    initialize_texture_allocation_specification(
            &p_sprite_allocation_specification
                ->texture_allocation_specification, 
            texture_flags, 
            p_PLATFORM_graphics_window);
}

static inline
void initialize_sprite_allocation_specification_for__particle(
        Sprite_Allocation_Specification 
            *p_sprite_allocation_specification, 
        Texture_Flags texture_flags,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        enum Entity_Kind the_kind_of__entity) {
#warning TODO: impl for particles
    //TODO: impl for particles
    p_sprite_allocation_specification
        ->the_kind_of__sprite_allocation =
        Sprite_Allocation_Kind__None;

    initialize_texture_allocation_specification(
            &p_sprite_allocation_specification
                ->texture_allocation_specification, 
            texture_flags, 
            p_PLATFORM_graphics_window);
}

static inline 
void initialize_sprite_wrapper(
        Sprite_Wrapper *sprite_wrapper,
        Texture_Flags texture_flags_for__sprite) {
    sprite_wrapper->p_sprite = 0;
    sprite_wrapper->direction =
        DIRECTION__EAST;
    sprite_wrapper->
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Idle;

    sprite_wrapper->
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Idle;
    
    sprite_wrapper->
        frame__initial = 0;
    sprite_wrapper->
        frame = 0;
    sprite_wrapper->
        frame__final = 1;
}

static inline 
void initialize_sprite_wrapper_with__sprite_allocation(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Wrapper *sprite_wrapper,
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    initialize_sprite_wrapper(
            sprite_wrapper, 
            TEXTURE_FLAGS__NONE);

    sprite_wrapper->p_sprite =
        PLATFORM_allocate_sprite(
                p_PLATFORM_gfx_context,
                p_sprite_allocation_specification);
}

static inline 
void initialize_sprite_wrapper_for__entity_with__sprite_allocation(
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        Entity *entity) {
    Sprite_Allocation_Specification 
        sprite_allocation_specification;

    initialize_sprite_allocation_specification_for__entity(
            &sprite_allocation_specification,
            TEXTURE_FLAGS__NONE,
            p_PLATFORM_graphics_window,
            entity->the_kind_of_entity__this_entity_is);

    initialize_sprite_wrapper_with__sprite_allocation(
            PLATFORM_get_p_gfx_context_from__graphics_window(
                p_PLATFORM_graphics_window),
            &entity->sprite_wrapper, 
            &sprite_allocation_specification);
}

static inline
bool is_sprite_flags__allocated(Sprite_Flags sprite_flags) {
    return (bool)(sprite_flags
            & SPRITE_FLAG__BIT_IS_ALLOCATED);
}

static inline
void set_sprite_flags_as__allocated(Sprite_Flags *p_sprite_flags) {
    *p_sprite_flags |= SPRITE_FLAG__BIT_IS_ALLOCATED;
}

static inline
void set_sprite_flags_as__deallocated(Sprite_Flags *p_sprite_flags) {
    *p_sprite_flags &= ~SPRITE_FLAG__BIT_IS_ALLOCATED;
}

#endif
