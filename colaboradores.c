#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colaboradores.h"

#define MAX_COLABORADORES 100

char colaboradores[MAX_COLABORADORES][20] = {"Nicole", "Rafael", "Matheus", "Guilherme", "Nicolas", "Khalil"};
int num_colaboradores = 6;
char operador[20];

void carregarColaboradores() {
    FILE *arquivo = fopen("colaboradores.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de colaboradores não encontrado. Criando arquivo padrão...\n");
        salvarColaboradores();
        return;
    }
    num_colaboradores = 0;
    while (fscanf(arquivo, "%19s", colaboradores[num_colaboradores]) != EOF && num_colaboradores < MAX_COLABORADORES) {
        num_colaboradores++;
    }
    fclose(arquivo);
}

void salvarColaboradores() {
    FILE *arquivo = fopen("colaboradores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar colaboradores.\n");
        return;
    }
    for (int i = 0; i < num_colaboradores; i++) {
        fprintf(arquivo, "%s\n", colaboradores[i]);
    }
    fclose(arquivo);
}

int login() {
    char usuario[20], senha[10];
    int tentativas = 3;
    int autenticado = 0;

    while (tentativas > 0 && !autenticado) {
        // Exibe o cabeçalho do menu de login em cada tentativa
        printf("+--------------------------------+\n");
        printf("|       SISTEMA DE LOGIN         |\n");
        printf("+--------------------------------+\n");

        printf("| Usuário: ");
        fgets(usuario, sizeof(usuario), stdin);
        strtok(usuario, "\n");  // Remove a nova linha

        printf("| Senha: ");
        fgets(senha, sizeof(senha), stdin);
        strtok(senha, "\n");  // Remove a nova linha
        system("cls"); // Limpa a tela para manter a estrutura organizada

        if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
            strcpy(operador, "Administrador");
            autenticado = 1;
            return 2;
        } 

        for (int i = 0; i < num_colaboradores; i++) {
            if (strcmp(usuario, colaboradores[i]) == 0 && strcmp(senha, "123") == 0) {
                strcpy(operador, usuario);
                autenticado = 1;
                return 1;
            }
        }

        tentativas--;

        // Exibe mensagem de erro abaixo do cabeçalho em caso de falha
        printf("\n[ERRO] Usuário ou senha incorretos. Tentativas restantes: %d\n\n", tentativas);
    }

    printf("Número de tentativas excedido. Encerrando o sistema.\n");
    return 0;
}

int autenticarAdministrador() {
    char usuario[20], senha[10];

    printf("Para acessar essa opção, você precisa de permissão de administrador.\n");
    printf("Digite '0' para voltar ao menu principal.\n");
    printf("Usuário: ");
    fgets(usuario, sizeof(usuario), stdin);
    strtok(usuario, "\n");  // Remove a nova linha
    if (strcmp(usuario, "0") == 0) return 0;

    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n");  // Remove a nova linha

    if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
        return 1;
    } else {
        printf("[ERRO] Usuário ou senha de administrador incorretos.\n");
        return 0;
    }
}

void cadastrarColaborador() {
    if (num_colaboradores >= MAX_COLABORADORES) {
        printf("Erro: Número máximo de colaboradores atingido.\n");
        return;
    }

    char novoUsuario[20];
    char novaSenha[10];

    printf("Digite o nome do novo colaborador(a) (ou '0' para cancelar): ");
    fgets(novoUsuario, sizeof(novoUsuario), stdin);
    strtok(novoUsuario, "\n");  // Remove a nova linha
    if (strcmp(novoUsuario, "0") == 0) return;

    printf("Digite a senha do novo colaborador(a): ");
    fgets(novaSenha, sizeof(novaSenha), stdin);
    strtok(novaSenha, "\n");  // Remove a nova linha

    strcpy(colaboradores[num_colaboradores], novoUsuario);
    num_colaboradores++;
    salvarColaboradores();
    printf("Novo colaborador(a) '%s' cadastrado com sucesso.\n", novoUsuario);
}

void listarColaboradores() {
    printf("+------------------------------------+\n");
    printf("|       LISTA DE COLABORADORES       |\n");
    printf("+------------------------------------+\n");
    for (int i = 0; i < num_colaboradores; i++) {
        printf("| %-32s |\n", colaboradores[i]);
    }
    printf("+------------------------------------+\n");
}
