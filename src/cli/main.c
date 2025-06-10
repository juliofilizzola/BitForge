//
// Created by julio-filizzola on 17/04/25.
//

#include "../../include/cli/main.h"
#include "../../include/commands/init.h"
#include "../../include/config/config.h"
// TODO: validar como funciona no windows e no ubuntu

#include <stdio.h>
#include <string.h>

const char *CMD_INIT = "init";
const char *CMD_CONFIG = "config";
const char *SUBCMD_GLOBAL = "global";
const char *CMD_HELP = "help";
const char *CMD_LOG = "log";

enum ReturnCode
{
    SUCCESS = 0,
    ERROR_INVALID_ARGS = 1,
    ERROR_CONFIG_EXISTS = 2
};

void print_error(const char *message)
{
    fprintf(stderr, "Erro: %s\n", message);
}

void print_usage()
{
    printf("Uso: bitforge <comando> [args]\n");
    printf("Comandos disponíveis:\n");
    printf("  init ->      Inicializa um novo repositório\n");
    printf("  add  ->     Adiciona arquivos ao repositório\n");
    printf("  commit  ->   Cria um commit\n");
    printf("  push  ->     Envia alterações para o repositório remoto\n");
    printf("  config  ->   Criar configuração do git\n");
}

int main(int argc, char* argv[] ){


if (argc < 2) {

      print_usage();
        return ERROR_INVALID_ARGS;
    }

    const char* command= argv[1];

    if (strcmp(command, CMD_INIT) == 0) {

      return init_bit_forge();
    }

    if (strcmp(command, CMD_HELP) == 0) {

      print_usage();
        return SUCCESS;
    }

    if (strcmp(command, CMD_CONFIG) == 0) {

      printf("argc = %d\n", argc);
        if (argc < 3) {

              print_error("Uso: bitforge config <global>");
            return ERROR_INVALID_ARGS;
        }

        if (strcmp(argv[2], SUBCMD_GLOBAL) == 0) {

              if (config_exists()) {

                      print_error("Configuração global já existe.");
                return ERROR_CONFIG_EXISTS;
            }
            return create_global_config();
        }
    }

    print_error("Comando desconhecido");
    return ERROR_INVALID_ARGS;
}
