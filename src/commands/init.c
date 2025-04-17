//
// Created by julio-filizzola on 17/04/25.
//
#include "include/commands/init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int init_bit_forge()
{
    int status;
    status = mkdir(".bitForge", 0755);
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

    FILE *head = fopen(".git/HEAD", "w");
    if (!head)
    {
        perror("Erro ao criar arquivo .git/HEAD");
        return 1;
    }

    fputs("ref: refs/heads/main\n", head);
    fclose(head);

    FILE *config = fopen(".git/config", "w");
    if (!config)
    {
        perror("Erro ao criar .git/config");
        return 1;
    }
    fprintf(config, "[core]\n"
                    "\trepositoryformatversion = 0\n"
                    "\tfilemode = true\n"
                    "\tbare = false\n"
                    "[user]\n"
                    "\tname = Default User\n"
                    "\temail = user@example.com\n");
    fclose(config);

    printf("Repositório BitForge inicializado com sucesso!\n");
    return 0;
}
