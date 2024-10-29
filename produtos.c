#include <stdio.h>        // Biblioteca para entrada e sa�da
#include <stdlib.h>       // Biblioteca para aloca��o de mem�ria
#include "produtos.h"     // Inclui o cabe�alho de produtos

#define LIMPA_BUFFER fflush(stdin); // Macro para limpar o buffer do teclado

// Fun��o para cadastrar um produto e salv�-lo em um arquivo
void cadastrarProduto(Produto *p) {
    printf("Digite o c�digo do produto: ");
    scanf("%d", &p->codigo);
    printf("Nome do produto: ");
    LIMPA_BUFFER
    scanf("%49[^\n]", p->nome); // L� o nome do produto
    printf("Pre�o por kg: ");
    scanf("%f", &p->preco_por_kg); // L� o pre�o por kg
    printf("Categoria: ");
    LIMPA_BUFFER
    scanf("%19[^\n]", p->categoria); // L� a categoria do produto

    // Abre o arquivo para adicionar o produto
    FILE *arq = fopen("produtos.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n"); // Exibe mensagem de erro se n�o abrir o arquivo
        return;
    }
    fwrite(p, sizeof(Produto), 1, arq); // Grava o produto no arquivo
    fclose(arq); // Fecha o arquivo ap�s salvar
    printf("Produto cadastrado com sucesso!\n");
}

// Fun��o para listar todos os produtos cadastrados no arquivo
void listarProdutos() {
    FILE *arq = fopen("produtos.txt", "r"); // Abre o arquivo para leitura
    if (arq == NULL) {
        printf("Nenhum produto cadastrado.\n"); // Mensagem se o arquivo n�o existir
        return;
    }

    Produto p;
    int count = 0; // Contador para verificar se existem produtos

    printf("\nLista de Produtos:\n");
    // L� e exibe cada produto armazenado no arquivo
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("C�digo: %d, Nome: %s, Pre�o/kg: %.2f, Categoria: %s\n", p.codigo, p.nome, p.preco_por_kg, p.categoria);
        count++;
    }

    if (count == 0) {
        printf("Nenhum produto cadastrado.\n"); // Exibe se o arquivo estiver vazio
    }

    fclose(arq); // Fecha o arquivo ap�s exibir todos os produtos
}

