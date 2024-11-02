#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produtos.h"
#include "vendas.h"

#define LIMPA_BUFFER fflush(stdin);

#define MAX_COLABORADORES 100
char colaboradores[MAX_COLABORADORES][20] = {"Nicole", "Rafael", "Matheus", "Guilherme", "Nicolas", "Khalil"};
int num_colaboradores = 6;
char operador[20];

// Protótipos de funções
void exibirDataHora();
void salvarColaboradores();
void carregarColaboradores();
int login();
int autenticarAdministrador();  // Declaração da função autenticarAdministrador
void cadastrarColaborador();
void listarColaboradores();

void exibirDataHora() {
    time_t agora = time(NULL);
    struct tm *dataHora = localtime(&agora);
    dataHora->tm_hour -= 3;
    mktime(dataHora);

    printf("| Data: %02d/%02d/%d               \n", 
           dataHora->tm_mday, dataHora->tm_mon + 1, dataHora->tm_year + 1900);
    printf("| Hora: %02d:%02d                 \n", 
           dataHora->tm_hour, dataHora->tm_min);
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
        LIMPA_BUFFER
        scanf("%19s", usuario);
        printf("Senha: ");
        LIMPA_BUFFER
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
    LIMPA_BUFFER
    scanf("%19s", usuario);
    if (strcmp(usuario, "0") == 0) return 0;

    printf("Senha: ");
    LIMPA_BUFFER
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
    LIMPA_BUFFER
    scanf("%19s", novoUsuario);
    if (strcmp(novoUsuario, "0") == 0) return;

    printf("Digite a senha do novo colaborador(a): ");
    LIMPA_BUFFER
    scanf("%9s", novaSenha);

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

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    system("color 4f");

    carregarColaboradores();

    int acesso = login();
    if (acesso == 0) {
        return 0;
    }

    Produto produto;
    Venda venda;
    char opcao;

    do {
        system("cls");
        printf("+------------------------------------+\n");
        printf("|        SISTEMA VIVA FRUIT          |\n");
        printf("+------------------------------------+\n");
        printf("| Operador(a): %-24s \n", operador);
        exibirDataHora();
        printf("+------------------------------------+\n");

        if (acesso == 2) {
            printf("| 1. Cadastrar Produto               |\n");
            printf("| 2. Lista de Produtos               |\n");
            printf("| 3. Registrar Venda                 |\n");
            printf("| 4. Gerar Relatório de Vendas       |\n");
            printf("| 5. Cadastrar Colaborador(a)        |\n");
            printf("| 6. Listar Colaboradores            |\n");
            printf("| 7. Sair                            |\n");
        } else {
            printf("| 1. Cadastrar Produto               |\n");
            printf("| 2. Lista de Produtos               |\n");
            printf("| 3. Registrar Venda                 |\n");
            printf("| 4. Gerar Relatório de Vendas       |\n");
            printf("| 5. Sair                            |\n");
        }
        printf("+------------------------------------+\n");

        printf("Escolha uma opção: ");
        LIMPA_BUFFER
        scanf("%c", &opcao);

        if (acesso == 2) {
            switch (opcao) {
                case '1':
                    cadastrarProduto(&produto);
                    break;
                case '2':
                    listarProdutos();
                    break;
                case '3':
                    registrarVenda(&venda);
                    break;
                case '4':
                    gerarRelatorio();
                    break;
                case '5':
                    cadastrarColaborador();
                    break;
                case '6':
                    listarColaboradores();
                    break;
                case '7':
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                    break;
            }
        } else {
            switch (opcao) {
                case '1':
                    if (autenticarAdministrador()) {
                        cadastrarProduto(&produto);
                    }
                    break;
                case '2':
                    listarProdutos();
                    break;
                case '3':
                    registrarVenda(&venda);
                    break;
                case '4':
                    if (autenticarAdministrador()) {
                        gerarRelatorio();
                    }
                    break;
                case '5':
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                    break;
            }
        }
        system("pause");
    } while ((acesso == 2 && opcao != '7') || (acesso == 1 && opcao != '5'));

    return 0;
}
