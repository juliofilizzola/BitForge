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


int update_global_config(const char *key, const char *value) {
    char path[512];
    get_config_path(path, sizeof(path));

    FILE *file = fopen(path, "r+");
    if (!file) {
        perror("Error opening global config file");
        return 1;
    }

    char buffer[1024];
    int key_found = 0;
    FILE *temp = tmpfile();
    if (!temp) {
        perror("Error creating temporary file");
        fclose(file);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, key, strlen(key)) == 0 && buffer[strlen(key)] == ' ') {
            fprintf(temp, "%s = %s\n", key, value);
            key_found = 1;
        } else {
            fputs(buffer, temp);
        }
    }

    if (!key_found) {
        fprintf(temp, "%s = %s\n", key, value);
    }

    rewind(file);
    rewind(temp);

    while (fgets(buffer, sizeof(buffer), temp)) {
        fputs(buffer, file);
    }

    fclose(file);
    fclose(temp);

    return 0;
}

int get_global_config_value(const char *key, char *value) {
    char path[512];
    get_config_path(path, sizeof(path));

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening global config file");
        return 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, key, strlen(key)) == 0 && buffer[strlen(key)] == ' ') {
            sscanf(buffer + strlen(key) + 1, "%s", value);
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
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


int deleted_global_config() {
    char path[512];
    get_config_path(path, sizeof(path));
    if (remove(path) == 0) {
        printf("Configuração global deletada com sucesso.\n");
        return 0;
    }
    perror("Erro ao deletar configuração global");
    return 1;
}
