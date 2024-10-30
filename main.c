#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "produtos.h"
#include "vendas.h"

#define LIMPA_BUFFER fflush(stdin);

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    system("color 4f");

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

