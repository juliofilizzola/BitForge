//
// Created by julio-filizzola on 17/04/25.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/commands/init.h"


int init_bit_forge() {
    int status;
    status = mkdir(".bitForge", 0755);
    if (status != 0) {
        perror("Error creating directory .bitForge");
        return 1;
    }

    status = mkdir(".bitForge/objects", 0755);
    status |= mkdir(".bitForge/refs", 0755);

    if (status != 0) {
        perror("Error creating directory objects or refs");
        return 1;
    }

    FILE *head = fopen(".git/HEAD", "w");
    if (!head) {
        perror("Erro ao criar arquivo .git/HEAD");
        return 1;
    }

    fputs("ref: refs/heads/master\n", head);
    fclose(head);

    printf("Repositório BitForge inicializado com sucesso!\n");
    return 0;
}
