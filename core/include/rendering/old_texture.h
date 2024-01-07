#ifndef TEXTURE_H
#define TEXTURE_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include <defines.h>

/// 
/// Returns nullptr (0) if fails.
///
Texture* get_new_texture(unsigned int w, unsigned int h);
void release_texture(Texture* texture);

void set_data_of_texture(Texture* texture, unsigned char* data);
void set_subdata_of_texture(Texture* texture, unsigned int x, unsigned int y, 
        unsigned int w, unsigned int h, unsigned char* data);
void get_data_from_texture(Texture* texture, unsigned int length_of_data, 
        unsigned char* data);
void get_subdata_from_texture(Texture* texture,unsigned int x, unsigned int y, 
        unsigned int w, unsigned int h, unsigned int length_of_data, 
        unsigned char* data);
unsigned int get_id_from_texture(Texture* texture);
unsigned int get_width_from_texture(Texture* texture);
unsigned int get_height_from_texture(Texture* texture);

#endif
