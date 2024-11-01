#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produtos.h"
#include "vendas.h"

#define LIMPA_BUFFER fflush(stdin);

const char *colaboradores[] = {"Nicole", "Rafael", "Matheus", "Guilherme", "Nicolas", "Khalil"};
const int num_colaboradores = 6;
char operador[20];

// Função para exibir data e hora
void exibirDataHora() {
    time_t agora = time(NULL);
    struct tm *dataHora = localtime(&agora);
    printf("%02d/%02d/%d %02d:%02d:%02d\n", 
           dataHora->tm_mday, dataHora->tm_mon + 1, dataHora->tm_year + 1900, 
           dataHora->tm_hour, dataHora->tm_min, dataHora->tm_sec);
}

// Função para realizar login
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
        printf("Usuário ou senha incorretos. Tentativas restantes: %d\n", tentativas);
    }

    printf("Número de tentativas excedido. Encerrando o sistema.\n");
    return 0;
}

// Função para solicitar login do administrador para funções restritas
int loginAdministrador() {
    char usuario[20], senha[10];

    printf("Para acessar esta função, faça o login de administrador.\n");
    printf("Usuário: ");
    LIMPA_BUFFER
    scanf("%19s", usuario);
    printf("Senha: ");
    LIMPA_BUFFER
    scanf("%9s", senha);

    if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
        return 1;
    } else {
        printf("Acesso negado. Usuário ou senha incorretos.\n");
        return 0;
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    system("color 4f");

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
        printf("| Operador: %-24s |\n", operador);
        printf("| Data/Hora de acesso: ");
        exibirDataHora();
        printf("+------------------------------------+\n");
        printf("| 1. Cadastrar Produto               |\n");
        printf("| 2. Lista de Produtos               |\n");
        printf("| 3. Registrar Venda                 |\n");
        printf("| 4. Gerar Relatório de Vendas       |\n");
        printf("| 5. Sair                            |\n");
        printf("+------------------------------------+\n");
        printf("Escolha uma opção: ");
        LIMPA_BUFFER
        scanf("%c", &opcao);

        switch (opcao) {
            case '1':
                if (loginAdministrador()) {
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
                if (loginAdministrador()) {
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
        system("pause");
    } while (opcao != '5');

    return 0;
}
