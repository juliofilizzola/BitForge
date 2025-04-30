//
// Created by julio-filizzola on 24/04/25.
//

#ifndef CONFIG_H
#define CONFIG_H

int create_global_config();
int config_exists();
char* get_config_value(const char *section, const char *key);

#endif
