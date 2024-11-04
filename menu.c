#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "colaboradores.h"
#include "produtos.h"
#include "vendas.h"

void exibirMenu(int acesso) {
    system("cls");
    printf("+------------------------------------+\n");
    printf("|        SISTEMA VIVA FRUIT          |\n");
    printf("+------------------------------------+\n");
    printf("| Operador(a): %-24s \n", operador);
    exibirDataHora();
    printf("+------------------------------------+\n");

    // Exibe as opções de menu com base no nível de acesso
    if (acesso == 2) {
        printf("| 1. Cadastrar Produto               |\n");
        printf("| 2. Lista de Produtos               |\n");
        printf("| 3. Registrar Venda                 |\n");
        printf("| 4. Gerar Relatório de Vendas       |\n");
        printf("| 5. Cadastrar Colaborador(a)        |\n");
        printf("| 6. Listar Colaboradores            |\n");
        printf("| 7. Excluir Produto Cadastrado      |\n"); // Nova opção para excluir produto
        printf("| 8. Sair                            |\n"); // Atualizando para 8 opções
    } else {
        printf("| 1. Cadastrar Produto               |\n");
        printf("| 2. Lista de Produtos               |\n");
        printf("| 3. Registrar Venda                 |\n");
        printf("| 4. Gerar Relatório de Vendas       |\n");
        printf("| 5. Sair                            |\n");
    }
    printf("+------------------------------------+\n");
}

char escolherOpcao(int acesso) {
    char entrada[10]; // Buffer para ler a entrada do usuário
    char opcao;

    while (1) { // Loop até receber uma opção válida
        printf("Escolha uma opção: ");
        fgets(entrada, sizeof(entrada), stdin); // Lê a linha inteira

        // Remove o newline se presente
        entrada[strcspn(entrada, "\n")] = 0;

        // Verifica se a entrada contém exatamente um caractere
        if (strlen(entrada) == 1) {
            opcao = entrada[0]; // Pega o primeiro caractere
            // Verifica se a opção está dentro do intervalo esperado
            if (acesso == 2 && (opcao < '1' || opcao > '8')) { // Alterando para 8
                exibirErro("Opção inválida! Tente novamente.");
            } else if (acesso == 1 && (opcao < '1' || opcao > '5')) {
                exibirErro("Opção inválida! Tente novamente.");
            } else {
                return opcao; // Retorna a opção válida
            }
        } else {
            exibirErro("Por favor, insira apenas um único caractere.");
        }

        // Reexibe o menu após uma opção inválida
        exibirMenu(acesso);
    }
}

void excluirProduto() {
    while (1) { // Loop até que o usuário escolha voltar ou exclua
        // Exibe a lista de produtos cadastrados
        listarProdutos(1); // Aqui chamamos a função listarProdutos para mostrar a lista.

        printf("Deseja voltar para o menu (aperte '0') ou excluir o produto (aperte '1')?\n");
        char opcao;
        scanf(" %c", &opcao);
        limparBuffer();

        if (opcao == '0') {
            return; // Volta para o menu
        } else if (opcao == '1') {
            int codigoProduto;
            printf("Digite o código do produto que deseja excluir: ");
            scanf("%d", &codigoProduto);
            limparBuffer();

            // Confirmação de exclusão
            printf("Você está prestes a excluir o produto com código: %d\n", codigoProduto);
            printf("Confirma a exclusão? (s/n): ");
            char confirmar;
            scanf(" %c", &confirmar);
            limparBuffer();

            if (confirmar == 's') {
                // Solicitar login e senha do administrador
                char login[20];
                char senha[20];

                printf("Digite o login do administrador: ");
                scanf("%s", login);
                printf("Digite a senha do administrador: ");
                scanf("%s", senha);

                // Verifica se as credenciais estão corretas
                if (strcmp(login, "adm") == 0 && strcmp(senha, "123") == 0) {
                    removerProduto(codigoProduto); // Chama a função para excluir o produto
                    printf("Produto excluído com sucesso!\n");
                } else {
                    printf("Login ou senha incorretos. Exclusão cancelada.\n");
                }
            } else {
                printf("Exclusão cancelada.\n");
            }
        } else {
            exibirErro("Opção inválida! Tente novamente.");
        }
    }
}
