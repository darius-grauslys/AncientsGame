#include "defines.h"
#include <rendering/texture.h>

///
/// Returns the length in pixels of the texture's width.
///
Quantity__u16 get_length_of__texture_flag__width(
        Texture_Flags texture_flags) {
    switch (get_texture_flags__width(texture_flags)) {
        default:
        case TEXTURE_FLAG__LENGTH_x8:
            return 8;
        case TEXTURE_FLAG__LENGTH_x16:
            return 16;
        case TEXTURE_FLAG__LENGTH_x32:
            return 32;
        case TEXTURE_FLAG__LENGTH_x64:
            return 64;
        case TEXTURE_FLAG__LENGTH_x128:
            return 128;
        case TEXTURE_FLAG__LENGTH_x256:
            return 256;
        case TEXTURE_FLAG__LENGTH_x512:
            return 512;
    }
}

///
/// Returns the length in pixels of the texture's height.
///
Quantity__u16 get_length_of__texture_flag__height(
        Texture_Flags texture_flags) {
    switch (get_texture_flags__height(texture_flags)) {
        default:
        case TEXTURE_FLAG__LENGTH_x8:
            return 8;
        case TEXTURE_FLAG__LENGTH_x16:
            return 16;
        case TEXTURE_FLAG__LENGTH_x32:
            return 32;
        case TEXTURE_FLAG__LENGTH_x64:
            return 64;
        case TEXTURE_FLAG__LENGTH_x128:
            return 128;
        case TEXTURE_FLAG__LENGTH_x256:
            return 256;
        case TEXTURE_FLAG__LENGTH_x512:
            return 512;
    }
}
