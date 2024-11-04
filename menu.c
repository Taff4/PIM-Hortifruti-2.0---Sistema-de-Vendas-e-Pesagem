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

    // Exibe as op��es de menu com base no n�vel de acesso
    if (acesso == 2) {
        printf("| 1. Cadastrar Produto               |\n");
        printf("| 2. Lista de Produtos               |\n");
        printf("| 3. Registrar Venda                 |\n");
        printf("| 4. Gerar Relat�rio de Vendas       |\n");
        printf("| 5. Cadastrar Colaborador(a)        |\n");
        printf("| 6. Listar Colaboradores            |\n");
        printf("| 7. Sair                            |\n");
    } else {
        printf("| 1. Cadastrar Produto               |\n");
        printf("| 2. Lista de Produtos               |\n");
        printf("| 3. Registrar Venda                 |\n");
        printf("| 4. Gerar Relat�rio de Vendas       |\n");
        printf("| 5. Sair                            |\n");
    }
    printf("+------------------------------------+\n");
}

char escolherOpcao(int acesso) {
    char opcao;
    int opcaoValida = 0; // Flag para verificar se a op��o � v�lida

    do {
        printf("Escolha uma op��o: ");
        scanf(" %c", &opcao); // Espa�o antes de %c para ignorar enter anterior
        limparBuffer(); // Limpa o buffer para evitar problemas com entradas subsequentes
        
        // Verifica se a op��o est� dentro do intervalo esperado
        if (acesso == 2 && (opcao < '1' || opcao > '7')) {
            exibirErro("Op��o inv�lida! Tente novamente.");
        } else if (acesso == 1 && (opcao < '1' || opcao > '5')) {
            exibirErro("Op��o inv�lida! Tente novamente.");
        } else {
            opcaoValida = 1; // Marca a op��o como v�lida
        }
    } while (!opcaoValida); // Continua pedindo at� receber uma op��o v�lida

    return opcao;
}

