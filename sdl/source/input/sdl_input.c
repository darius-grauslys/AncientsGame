#include "defines.h"
#include "defines_weak.h"
#include "input/input.h"
#include "platform.h"
#include "platform_defines.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <input/sdl_input.h>

enum Input_Binding_Kind {
    Input_Binding_Kind__None,
    Input_Binding_Kind__Keyboard,
    Input_Binding_Kind__Mouse,
};

typedef struct {
    Input_Code__u32 input_code__u32;
    Input_Flags__u32 input_flag__u32;

    enum Input_Binding_Kind the_kind_of__input_binding;
    union {
        SDL_Scancode sdl_scancode;
        u32 sdl_mouse_button;
    };
} Input_Binding;

Input_Binding __SDL_INPUT_BINDINGS[QUANTITY_OF__INPUTS];

void SLD_initialize_input_bindings() {
    __SDL_INPUT_BINDINGS[INPUT_CODE_NONE] = (Input_Binding){
        INPUT_CODE_NONE,
        INPUT_NONE,
        Input_Binding_Kind__None,
        SDL_NUM_SCANCODES
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_FORWARD] = (Input_Binding){
        INPUT_CODE_FORWARD,
        INPUT_FORWARD,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_W
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_LEFT] = (Input_Binding){
        INPUT_CODE_LEFT,
        INPUT_LEFT,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_A
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_RIGHT] = (Input_Binding){
        INPUT_CODE_RIGHT,
        INPUT_RIGHT,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_D
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_BACKWARD] = (Input_Binding){
        INPUT_CODE_BACKWARD,
        INPUT_BACKWARD,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_S
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_GAME_SETTINGS] = (Input_Binding){
        INPUT_CODE_GAME_SETTINGS,
        INPUT_GAME_SETTINGS,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_ESCAPE
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_LOCKON] = (Input_Binding){
        INPUT_CODE_LOCKON,
        INPUT_LOCKON,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_TAB
    };
    // TODO: have a sense of UI_Focus between gamespace and UI.
    //       allow for input.c to acknowledge the state.
    __SDL_INPUT_BINDINGS[INPUT_CODE_USE] = (Input_Binding){
        INPUT_CODE_USE,
        INPUT_USE,
        Input_Binding_Kind__Mouse,
        SDL_BUTTON(1)
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_USE_SECONDARY] = (Input_Binding){
        INPUT_CODE_USE_SECONDARY,
        INPUT_USE_SECONDARY,
        Input_Binding_Kind__Mouse,
        SDL_BUTTON(3)
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_EXAMINE] = (Input_Binding){
        INPUT_CODE_EXAMINE,
        INPUT_EXAMINE,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_F
    };
    // __SDL_INPUT_BINDINGS[INPUT_CODE_CONSUME] = (Input_Binding){
    //     INPUT_CODE_CONSUME,
    //     INPUT_CONSUME,
    //     Input_Binding_Kind__Keyboard,
    //     SDL_SCANCODE_S
    // };
    __SDL_INPUT_BINDINGS[INPUT_CODE_TURN_RIGHT] = (Input_Binding){
        INPUT_CODE_TURN_RIGHT,
        INPUT_TURN_RIGHT,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_Q
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_TURN_LEFT] = (Input_Binding){
        INPUT_CODE_TURN_LEFT,
        INPUT_TURN_LEFT,
        Input_Binding_Kind__Keyboard,
        SDL_SCANCODE_E
    };
    __SDL_INPUT_BINDINGS[INPUT_CODE_CLICK] = (Input_Binding){
        INPUT_CODE_CLICK,
        INPUT_CLICK,
        Input_Binding_Kind__Mouse,
        SDL_BUTTON(1)
    };
}

void PLATFORM_poll_input(Input *p_input) {
    const u8 *p_keys = SDL_GetKeyboardState(0);

    p_input->input_flags__pressed_old =
        p_input->input_flags__pressed;

    clear_input(p_input);

    u32 mouse_button_state = 
        SDL_GetMouseState(
                &p_input->cursor__3i32.x__i32, 
                &p_input->cursor__3i32.y__i32);

    for (Index__u8 index=0;
            index<QUANTITY_OF__INPUTS;
            index++) {
        Input_Binding *p_input_binding =
            &__SDL_INPUT_BINDINGS[index];
        switch(p_input_binding->the_kind_of__input_binding) {
            default:
                continue;
            case Input_Binding_Kind__Keyboard:
                if (p_keys[p_input_binding->sdl_scancode])
                    p_input->input_flags__pressed |=
                        p_input_binding->input_flag__u32
                        ;
            case Input_Binding_Kind__Mouse:
                if (mouse_button_state & 
                        p_input_binding->sdl_mouse_button)
                    p_input->input_flags__pressed |=
                        p_input_binding->input_flag__u32
                        ;
        }
    }

    p_input->input_flags__held =
        p_input->input_flags__pressed_old
        & p_input->input_flags__pressed
        ;
    
    p_input->input_flags__released =
        (!p_input->input_flags__pressed)
        & p_input->input_flags__pressed_old
        ;
}
