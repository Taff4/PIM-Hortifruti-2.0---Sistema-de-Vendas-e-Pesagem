#include <stdio.h>        // Biblioteca para operações de entrada e saída
#include <locale.h>       // Biblioteca para configurar o idioma
#include <stdlib.h>       // Biblioteca para alocação de memória e controle do programa
#include <time.h>         // Biblioteca para manipulação de data e hora
#include "produtos.h"     // Inclui o cabeçalho com funções e estrutura de produtos
#include "vendas.h"       // Inclui o cabeçalho com funções e estrutura de vendas

#define LIMPA_BUFFER fflush(stdin); // Macro para limpar o buffer do teclado

int main(void) {
    setlocale(LC_ALL, "Portuguese"); // Configura o idioma para português
    system("color 4f");              // Define a cor do console (fundo vermelho com texto branco)
    Produto produto;                 // Variável para armazenar dados de um produto
    Venda venda;                     // Variável para armazenar dados de uma venda
    char opcao;                      // Variável para armazenar a opção do menu escolhida pelo usuário

    do {
        system("cls"); // Limpa a tela para uma nova exibição do menu
        printf("+------------------------------------+\n");
        printf("|        SISTEMA VIVA FRUIT          |\n");
        printf("+------------------------------------+\n");
        printf("| 1. Cadastrar Produto               |\n");
        printf("| 2. Listar Produtos                 |\n");
        printf("| 3. Registrar Venda                 |\n");
        printf("| 4. Gerar Relatório de Vendas       |\n");
        printf("| 5. Sair                            |\n");
        printf("+------------------------------------+\n");
        printf("Escolha uma opção: ");
        LIMPA_BUFFER
        scanf("%c", &opcao);

        switch(opcao) {
            case '1':
                cadastrarProduto(&produto); // Função para cadastrar um novo produto
                break;
            case '2':
                listarProdutos(); // Função para listar todos os produtos cadastrados
                break;
            case '3':
                registrarVenda(&venda); // Função para registrar uma nova venda
                break;
            case '4':
                gerarRelatorio(); // Função para gerar um relatório de vendas
                break;
            case '5':
                printf("Saindo do sistema...\n"); // Sai do programa
                break;
            default:
                printf("Opção inválida! Tente novamente.\n"); // Exibe mensagem de erro se a opção for inválida
                break;
        }
        system("pause"); // Pausa antes de retornar ao menu
    } while(opcao != '5'); // Repete o menu até que o usuário escolha sair

    return 0; // Indica que o programa terminou sem erros
}
