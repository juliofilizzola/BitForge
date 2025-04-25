//
// Created by julio-filizzola on 17/04/25.
//

#include "include/commands/init.h"
#include "include/config/config.h"
#include "include/commands/init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int init_dirs()
{
    int status = mkdir(".bitForge", 0755);
    if (status != 0)
    {

        perror("Error creating directory .bitForge");
        return 1;
    }

    status = mkdir(".bitForge/objects", 0755);
    status |= mkdir(".bitForge/refs", 0755);


    if (status != 0)
    {
        perror("Error creating directory objects or refs");
        return 1;
    }

    return 0;
}

int init_files()
{
    FILE *file = fopen(".bitForge/HEAD", "w");
    if (!file)
    {
        perror("Error creating .bitForge/HEAD file");
        return 1;
    }
    fprintf(file, "ref: refs/heads/main\n");
    fclose(file);

    file = fopen(".bitForge/config", "w");
    if (!file)
    {
        perror("Error creating .bitForge/config file");
        return 1;
    }
    fprintf(file, "[core]\n\trepositoryformatversion = 0\n");
    fclose(file);

    return 0;

}

int init_bit_forge()
{
    init_dirs();
    init_files();
    printf("Repositório BitForge inicializado com sucesso!\n");
    return 0;
}
