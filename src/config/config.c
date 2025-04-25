//
// Created by julio-filizzola on 24/04/25.
//
#include "../../include/config/config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


#define CONFIG_FILE ".bitForge/config"

static void get_config_path(char *path, size_t size)
{
    const char *home = getenv("HOME");
    if (!home)
    {
        fprintf(stderr, "Error: HOME environment variable not set.\n");
        exit(1);
    }
    snprintf(path, size, "%s/%s", home, CONFIG_FILE);
}

int config_exists()
{
    char path[512];
    get_config_path(path, sizeof(path));
    return access(path, F_OK) == 0;
}

int create_global_config() {
    char path[512];
    get_config_path(path, sizeof(path));
    FILE *file = fopen(path, "w");
    if (!file) {
        perror("Error creating global config file");
        return 1;
    }
    fprintf(file,
        "[user]\n"
        "\tname = Default User\n"
        "\temail = seu@email.com"
    );
    fclose(file);
    return 0;
}
