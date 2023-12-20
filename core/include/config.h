#ifndef CONFIG_H
#define CONFIG_H

#include <defines.h>

typedef struct Config_t {

} Config;

void load_from_file_for_config(Config* config, const char* path);

#endif
