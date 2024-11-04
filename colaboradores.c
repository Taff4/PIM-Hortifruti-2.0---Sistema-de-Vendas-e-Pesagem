#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colaboradores.h"

#define MAX_COLABORADORES 100

Colaborador colaboradores[MAX_COLABORADORES] = {
    {1, "Nicole"}, {2, "Rafael"}, {3, "Matheus"}, {4, "Guilherme"}, {5, "Nicolas"}, {6, "Khalil"}
};
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
    while (fscanf(arquivo, "%d %19s", &colaboradores[num_colaboradores].id, colaboradores[num_colaboradores].nome) != EOF && num_colaboradores < MAX_COLABORADORES) {
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
        fprintf(arquivo, "%d %s\n", colaboradores[i].id, colaboradores[i].nome);
    }
    fclose(arquivo);
}

int login() {
    char usuario[20], senha[10];
    int tentativas = 3;
    int autenticado = 0;

    while (tentativas > 0 && !autenticado) {
        printf("+--------------------------------+\n");
        printf("|       SISTEMA DE LOGIN         |\n");
        printf("+--------------------------------+\n");

        printf("| Usuário: ");
        fgets(usuario, sizeof(usuario), stdin);
        strtok(usuario, "\n");

        printf("| Senha: ");
        fgets(senha, sizeof(senha), stdin);
        strtok(senha, "\n");
        system("cls");

        if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
            strcpy(operador, "Administrador");
            autenticado = 1;
            return 2;
        }

        for (int i = 0; i < num_colaboradores; i++) {
            if (strcmp(usuario, colaboradores[i].nome) == 0 && strcmp(senha, "123") == 0) {
                strcpy(operador, usuario);
                autenticado = 1;
                return 1;
            }
        }

        tentativas--;
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
    strtok(usuario, "\n");
    if (strcmp(usuario, "0") == 0) return 0;

    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n");

    if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
        return 1;
    } else {
        printf("[ERRO] Usuário ou senha de administrador incorretos.\n");
        return 0;
    }
}

void cadastrarColaborador() {
    Colaborador novoColaborador;

    // Limpa a tela e exibe o cabeçalho
    system("cls");
    printf("+-----------------------------------------+\n");
    printf("|      CADASTRO DE NOVO COLABORADOR      |\n");
    printf("+-----------------------------------------+\n");

    printf("Digite o nome do novo colaborador(a) (ou '0' para cancelar): ");
    fgets(novoColaborador.nome, sizeof(novoColaborador.nome), stdin);
    strtok(novoColaborador.nome, "\n");
    if (strcmp(novoColaborador.nome, "0") == 0) return;

    // Verifica se o colaborador já existe
    for (int i = 0; i < num_colaboradores; i++) {
        if (strcmp(colaboradores[i].nome, novoColaborador.nome) == 0) {
            printf("Colaborador já cadastrado.\n");
            return;
        }
    }

    // Solicita a senha do colaborador
    printf("Digite a senha para o colaborador(a): ");
    char senha[10];
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n"); // Remove a nova linha
    // Aqui você pode armazenar a senha se quiser

    // Se não existir, cadastra o novo colaborador
    novoColaborador.id = num_colaboradores + 1; // Atribui ID
    colaboradores[num_colaboradores] = novoColaborador;
    num_colaboradores++;
    salvarColaboradores();
    printf("Novo colaborador(a) '%s' cadastrado com sucesso.\n", novoColaborador.nome);
}

void listarColaboradores() {
    system("cls"); // Limpa a tela ao listar colaboradores
    printf("+------------------------------------+\n");
    printf("|       LISTA DE COLABORADORES       |\n");
    printf("+------------------------------------+\n");
    for (int i = 0; i < num_colaboradores; i++) {
        printf("| ID: %-2d Nome: %-20s  |\n", colaboradores[i].id, colaboradores[i].nome);
    }
    printf("+------------------------------------+\n");

    printf("Opções:\n");
    printf("0 - Voltar ao menu\n");
    printf("1 - Excluir colaborador\n");

    char opcao;
    printf("Escolha uma opção: ");
    scanf(" %c", &opcao);
    limparBuffer(); // Limpa o buffer após scanf

    if (opcao == '0') {
        return; // Volta ao menu
    } else if (opcao == '1') {
        excluirColaborador();
    }
}

void excluirColaborador() {
    int id;
    printf("Digite o ID do colaborador que deseja excluir: ");
    scanf("%d", &id);
    limparBuffer(); // Limpa o buffer após scanf

    // Busca o colaborador
    Colaborador* colaboradorEncontrado = NULL;
    for (int i = 0; i < num_colaboradores; i++) {
        if (colaboradores[i].id == id) {
            colaboradorEncontrado = &colaboradores[i];
            break;
        }
    }

    if (colaboradorEncontrado == NULL) {
        printf("Colaborador com ID %d não encontrado.\n", id);
        return;
    }

    // Confirmação antes de excluir
    char confirmar;
    printf("Você realmente deseja excluir o colaborador '%s' (s/n)? ", colaboradorEncontrado->nome);
    scanf(" %c", &confirmar);
    limparBuffer(); // Limpa o buffer após scanf

    if (confirmar == 'n' || confirmar == 'N') {
        printf("Operação cancelada. Voltando ao menu...\n");
        return;
    } else if (confirmar != 's' && confirmar != 'S') {
        printf("Opção inválida. Cancelando operação.\n");
        return;
    }

    // Solicita login do administrador
    if (autenticarAdministrador() == 0) {
        printf("Operação cancelada. Voltando ao menu...\n");
        return;
    }

    // Move todos os colaboradores abaixo para cima
    for (int j = (colaboradorEncontrado - colaboradores); j < num_colaboradores - 1; j++) {
        colaboradores[j] = colaboradores[j + 1];
    }
    num_colaboradores--;
    salvarColaboradores();
    printf("Colaborador com ID %d excluído com sucesso.\n", id);
}

