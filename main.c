#include <stdio.h>        // Biblioteca para operações de entrada e saída
#include <locale.h>       // Biblioteca para configurar o idioma
#include <stdlib.h>       // Biblioteca para alocação de memória e controle do programa
#include <time.h>         // Biblioteca para manipulação de data e hora
#include "produtos.h"     // Inclui o cabeçalho com funções e estrutura de produtos
#include "vendas.h"       // Inclui o cabeçalho com funções e estrutura de vendas

#define LIMPA_BUFFER fflush(stdin); // Macro para limpar o buffer do teclado

int main(void) {
    setlocale(LC_ALL, "Portuguese"); // Configura o idioma para português
    Produto produto;                 // Cria uma variável para armazenar dados de um produto
    Venda venda;                     // Cria uma variável para armazenar dados de uma venda
    char opcao;                      // Variável para armazenar a opção do menu escolhida pelo usuário
	system("color4f");
	
    do {
        system("cls"); // Limpa a tela a cada vez que o menu é exibido
        printf("\nBem-vindo ao sistema Viva Fruit\n");
        printf("1. Cadastrar Produto\n2. Listar Produtos\n3. Registrar Venda\n4. Gerar Relatório de Vendas\n5. Sair\nEscolha uma opção: ");
        LIMPA_BUFFER
        scanf("%c", &opcao);

        switch(opcao) {
            case '1':
                cadastrarProduto(&produto); // Chama a função para cadastrar um novo produto
                break;
            case '2':
                listarProdutos(); // Chama a função para listar todos os produtos cadastrados
                break;
            case '3':
                registrarVenda(&venda); // Chama a função para registrar uma nova venda
                break;
            case '4':
                gerarRelatorio(); // Chama a função para gerar um relatório de vendas
                break;
            case '5':
                printf("Saindo do sistema...\n"); // Sai do programa
                break;
            default:
                printf("Opção inválida!\n"); // Exibe mensagem de erro se a opção for inválida
                break;
        }
    } while(opcao != '5'); // O menu é exibido novamente até que o usuário escolha sair

    return 0; // Indica que o programa terminou sem erros
}

