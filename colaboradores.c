// colaboradores.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colaboradores.h"

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
    int i;

    while (tentativas > 0) {
        system("cls");
        printf("+--------------------------------+\n");
        printf("|       SISTEMA DE LOGIN         |\n");
        printf("+--------------------------------+\n");
        printf("Usuário: ");
        fflush(stdin);
        scanf("%19s", usuario);
        printf("Senha: ");
        fflush(stdin);
        scanf("%9s", senha);

        if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
            strcpy(operador, "Administrador");
            return 2;
        } else {
            for (i = 0; i < num_colaboradores; i++) {
                if (strcmp(usuario, colaboradores[i]) == 0 && strcmp(senha, "123") == 0) {
                    strcpy(operador, usuario);
                    return 1;
                }
            }
        }
        
        tentativas--;
        printf("\n[ERRO] Usuário ou senha incorretos. Tentativas restantes: %d\n", tentativas);
        system("pause");
    }

    printf("Número de tentativas excedido. Encerrando o sistema.\n");
    return 0;
}

int autenticarAdministrador() {
    char usuario[20], senha[10];

    printf("Para acessar essa opção, você precisa de permissão de administrador.\n");
    printf("Digite '0' para voltar ao menu principal.\n");
    printf("Usuário: ");
    fflush(stdin);
    scanf("%19s", usuario);
    if (strcmp(usuario, "0") == 0) return 0;

    printf("Senha: ");
    fflush(stdin);
    scanf("%9s", senha);

    if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
        return 1;
    } else {
        printf("[ERRO] Usuário ou senha de administrador incorretos.\n");
        return 0;
    }
}

void cadastrarColaborador() {
    char novoUsuario[20];
    char novaSenha[10];

    printf("Digite o nome do novo colaborador(a) (ou '0' para cancelar): ");
    fflush(stdin);
    scanf("%19s", novoUsuario);
    if (strcmp(novoUsuario, "0") == 0) return;

    printf("Digite a senha do novo colaborador(a): ");
    fflush(stdin);
    scanf("%9s", novaSenha);

    strcpy(colaboradores[num_colaboradores], novoUsuario);
    num_colaboradores++;
    salvarColaboradores();
    printf("Novo colaborador(a) '%s' cadastrado com sucesso.\n", novoUsuario);
}

void listarColaboradores() {
    system("cls");
    printf("+------------------------------------+\n");
    printf("|       LISTA DE COLABORADORES       |\n");
    printf("+------------------------------------+\n");
    for (int i = 0; i < num_colaboradores; i++) {
        printf("| %-32s |\n", colaboradores[i]);
    }
    printf("+------------------------------------+\n");
}

