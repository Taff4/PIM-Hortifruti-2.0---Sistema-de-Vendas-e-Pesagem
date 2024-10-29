#include <stdio.h>        // Biblioteca para entrada e saída
#include <stdlib.h>       // Biblioteca para alocação de memória
#include "produtos.h"     // Inclui o cabeçalho de produtos

#define LIMPA_BUFFER fflush(stdin); // Macro para limpar o buffer do teclado

// Função para cadastrar um produto e salvá-lo em um arquivo
void cadastrarProduto(Produto *p) {
    printf("Digite o código do produto: ");
    scanf("%d", &p->codigo);
    printf("Nome do produto: ");
    LIMPA_BUFFER
    scanf("%49[^\n]", p->nome); // Lê o nome do produto
    printf("Preço por kg: ");
    scanf("%f", &p->preco_por_kg); // Lê o preço por kg
    printf("Categoria: ");
    LIMPA_BUFFER
    scanf("%19[^\n]", p->categoria); // Lê a categoria do produto

    // Abre o arquivo para adicionar o produto
    FILE *arq = fopen("produtos.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n"); // Exibe mensagem de erro se não abrir o arquivo
        return;
    }
    fwrite(p, sizeof(Produto), 1, arq); // Grava o produto no arquivo
    fclose(arq); // Fecha o arquivo após salvar
    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar todos os produtos cadastrados no arquivo
void listarProdutos() {
    FILE *arq = fopen("produtos.txt", "r"); // Abre o arquivo para leitura
    if (arq == NULL) {
        printf("Nenhum produto cadastrado.\n"); // Mensagem se o arquivo não existir
        return;
    }

    Produto p;
    int count = 0; // Contador para verificar se existem produtos

    printf("\nLista de Produtos:\n");
    // Lê e exibe cada produto armazenado no arquivo
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("Código: %d, Nome: %s, Preço/kg: %.2f, Categoria: %s\n", p.codigo, p.nome, p.preco_por_kg, p.categoria);
        count++;
    }

    if (count == 0) {
        printf("Nenhum produto cadastrado.\n"); // Exibe se o arquivo estiver vazio
    }

    fclose(arq); // Fecha o arquivo após exibir todos os produtos
}

