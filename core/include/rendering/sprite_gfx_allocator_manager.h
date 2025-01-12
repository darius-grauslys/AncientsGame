#ifndef SPRITE_GFX_ALLOCATOR_MANAGER_H
#define SPRITE_GFX_ALLOCATOR_MANAGER_H

#include "defines.h"

void initialize_sprite_gfx_allocator_manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager);

bool allocate_sprite__entity(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        Entity_Kind the_kind_of__entity);

bool allocate_sprite__particle(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        Particle_Kind the_kind_of__particle);

bool allocate_sprite__ui(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        UI_Sprite_Kind the_kind_of__ui);

bool allocate_sprite__item(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Sprite_Wrapper *p_sprite_wrapper,
        Item_Kind the_kind_of__item);

void register_sprite_gfx_allocator_for__entity(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Entity_Kind the_kind_of__entity,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator);

void register_sprite_gfx_allocator_for__particle(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Particle_Kind the_kind_of__particle,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator);

void register_sprite_gfx_allocator_for__ui(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        UI_Sprite_Kind the_kind_of__ui,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator);

void register_sprite_gfx_allocator_for__item(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocator_manager,
        Item_Kind the_kind_of__item,
        f_Sprite_Gfx_Allocator f_sprite_gfx_allocator);

void register_sprite_gfx_allocators_in__sprite_gfx_allocator_manager(
        Sprite_Gfx_Allocation_Manager *p_sprite_gfx_allocation_manager);

#endif
