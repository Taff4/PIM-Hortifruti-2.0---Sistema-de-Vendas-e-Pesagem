#include <stdio.h>        // Biblioteca para opera��es de entrada e sa�da
#include <locale.h>       // Biblioteca para configurar o idioma
#include <stdlib.h>       // Biblioteca para aloca��o de mem�ria e controle do programa
#include <time.h>         // Biblioteca para manipula��o de data e hora
#include "produtos.h"     // Inclui o cabe�alho com fun��es e estrutura de produtos
#include "vendas.h"       // Inclui o cabe�alho com fun��es e estrutura de vendas

#define LIMPA_BUFFER fflush(stdin); // Macro para limpar o buffer do teclado

int main(void) {
    setlocale(LC_ALL, "Portuguese"); // Configura o idioma para portugu�s
    Produto produto;                 // Cria uma vari�vel para armazenar dados de um produto
    Venda venda;                     // Cria uma vari�vel para armazenar dados de uma venda
    char opcao;                      // Vari�vel para armazenar a op��o do menu escolhida pelo usu�rio
	system("color4f");
	
    do {
        system("cls"); // Limpa a tela a cada vez que o menu � exibido
        printf("\nBem-vindo ao sistema Viva Fruit\n");
        printf("1. Cadastrar Produto\n2. Listar Produtos\n3. Registrar Venda\n4. Gerar Relat�rio de Vendas\n5. Sair\nEscolha uma op��o: ");
        LIMPA_BUFFER
        scanf("%c", &opcao);

        switch(opcao) {
            case '1':
                cadastrarProduto(&produto); // Chama a fun��o para cadastrar um novo produto
                break;
            case '2':
                listarProdutos(); // Chama a fun��o para listar todos os produtos cadastrados
                break;
            case '3':
                registrarVenda(&venda); // Chama a fun��o para registrar uma nova venda
                break;
            case '4':
                gerarRelatorio(); // Chama a fun��o para gerar um relat�rio de vendas
                break;
            case '5':
                printf("Saindo do sistema...\n"); // Sai do programa
                break;
            default:
                printf("Op��o inv�lida!\n"); // Exibe mensagem de erro se a op��o for inv�lida
                break;
        }
    } while(opcao != '5'); // O menu � exibido novamente at� que o usu�rio escolha sair

    return 0; // Indica que o programa terminou sem erros
}

