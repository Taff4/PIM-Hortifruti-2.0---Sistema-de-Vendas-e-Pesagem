#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"

#define LIMPA_BUFFER while (getchar() != '\n' && getchar() != EOF)

// Função para verificar se o produto já existe no sistema
int produtoExiste(int codigo) {
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) return 0;

    Produto p;
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        if (p.codigo == codigo) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

// Função para cadastrar um novo produto
void cadastrarProduto() {
    Produto p;
    printf("+------------------------------------------+\n");
    printf("|           CADASTRO DE PRODUTOS           |\n");
    printf("+------------------------------------------+\n");

    printf("Digite o código do produto: ");
    scanf("%d", &p.codigo);
    
    if (produtoExiste(p.codigo)) {
        printf("Erro: Produto já cadastrado.\n");
        return;
    }

    printf("Nome do produto: ");
    LIMPA_BUFFER
    scanf("%49[^\n]", p.nome);
    printf("Preço por kg: ");
    scanf("%f", &p.preco_por_kg);
    printf("Categoria: ");
    LIMPA_BUFFER
    scanf("%19[^\n]", p.categoria);

    FILE *arq = fopen("produtos.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fwrite(&p, sizeof(Produto), 1, arq);
    fclose(arq);
    printf("Produto cadastrado com sucesso!\n");
}

// Função aprimorada para listar todos os produtos
void listarProdutos() {
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto p;
    printf("\n+---------------------------------------------------------------------+\n");
    printf("|                          LISTA DE PRODUTOS                          |\n");
    printf("+---------------------------------------------------------------------+\n");
    printf("| Código | Nome                     | Preço/kg   | Categoria          |\n");
    printf("+---------------------------------------------------------------------+\n");

    int contador = 0;
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("| %-6d | %-24s | R$ %-8.2f | %-17s |\n", p.codigo, p.nome, p.preco_por_kg, p.categoria);
        contador++;
    }

    if (contador == 0) {
        printf("|                     Nenhum produto cadastrado!                      |\n");
    }

    printf("+---------------------------------------------------------------------+\n");
    printf("Total de produtos cadastrados: %d\n\n", contador);

    fclose(arq);
}
