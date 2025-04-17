//
// Created by julio-filizzola on 17/04/25.
//

#include "../include/cli/main.h"
#include "../include/commands/init.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
        printf("Uso: bitforge <comando> [args]\n");
        printf("Comandos disponíveis:\n");
        printf("  init       Inicializa um novo repositório\n");
        printf("  add        Adiciona arquivos ao repositório\n");
        printf("  commit     Cria um commit\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) {
        return init_bit_forge();
    }

}
