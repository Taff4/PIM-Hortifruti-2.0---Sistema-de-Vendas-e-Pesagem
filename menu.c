#include <stdio.h>
#include <stdlib.h>
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
        printf("| 7. Sair                            |\n");
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
    char opcao;
    int opcaoValida = 0; // Flag para verificar se a opção é válida

    do {
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao); // Espaço antes de %c para ignorar enter anterior
        limparBuffer(); // Limpa o buffer para evitar problemas com entradas subsequentes
        
        // Verifica se a opção está dentro do intervalo esperado
        if (acesso == 2 && (opcao < '1' || opcao > '7')) {
            exibirErro("Opção inválida! Tente novamente.");
        } else if (acesso == 1 && (opcao < '1' || opcao > '5')) {
            exibirErro("Opção inválida! Tente novamente.");
        } else {
            opcaoValida = 1; // Marca a opção como válida
        }
    } while (!opcaoValida); // Continua pedindo até receber uma opção válida

    return opcao;
}

