#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h> // Necessário para a comparação de strings com strcmp
#include "produtos.h"
#include "vendas.h"

#define LIMPA_BUFFER fflush(stdin);

// Função para realizar o login
int login() {
    char usuario[10], senha[10];
    int tentativas = 3; // Limite de tentativas

    while (tentativas > 0) {
        printf("----- Login no Sistema -----\n");
        printf("Usuário: ");
        LIMPA_BUFFER
        scanf("%9s", usuario);

        printf("Senha: ");
        LIMPA_BUFFER
        scanf("%9s", senha);

        // Verifica o login e a senha
        if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
            printf("Login bem-sucedido!\n");
            return 1; // Login com sucesso
        } else {
            tentativas--;
            printf("Usuário ou senha incorretos. Tentativas restantes: %d\n", tentativas);
        }
    }
    printf("Número de tentativas excedido. Encerrando o sistema.\n");
    return 0; // Falha no login
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    system("color 4f");

    // Executa o login antes do menu principal
    if (!login()) {
        return 0; // Encerra o programa se o login falhar
    }

    Produto produto;
    Venda venda;
    char opcao;

    do {
        system("cls");
        printf("+------------------------------------+\n");
        printf("|        SISTEMA VIVA FRUIT          |\n");
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

        switch(opcao) {
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
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
        system("pause");
    } while(opcao != '5');

    return 0;
}

