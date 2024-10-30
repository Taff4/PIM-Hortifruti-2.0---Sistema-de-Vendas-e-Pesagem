#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "produtos.h"

#define LIMPA_BUFFER fflush(stdin);

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

void cadastrarProduto(Produto *p) {
    printf("\n+--------------------------------------+\n");
    printf("|         CADASTRO DE PRODUTO          |\n");
    printf("+--------------------------------------+\n");

    printf("Digite o código do produto ou '0' para retornar ao menu: ");
    scanf("%d", &p->codigo);

    if (p->codigo == 0) {
        printf("Retornando ao menu...\n");
        return;
    }

    if (produtoExiste(p->codigo)) {
        printf("Erro: Produto já cadastrado.\n");
        return;
    }

    LIMPA_BUFFER
    printf("Nome do produto: ");
    scanf("%49[^\n]", p->nome);

    printf("Preço por kg: ");
    scanf("%f", &p->preco_por_kg);

    LIMPA_BUFFER
    printf("Categoria: ");
    scanf("%19[^\n]", p->categoria);

    FILE *arq = fopen("produtos.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fwrite(p, sizeof(Produto), 1, arq);
    fclose(arq);

    Beep(523, 300); // Som de sucesso
    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos() {
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto p;
    printf("\n+------------------------------------------------------+\n");
    printf("| Código | Nome           | Preço    | Categoria       \n");
    printf("+------------------------------------------------------+\n");
    
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("| %-6d | %-14s | %-8.2f | %-12s \n", p.codigo, p.nome, p.preco_por_kg, p.categoria);
    }
    printf("+------------------------------------------------------+\n");

    fclose(arq);
}
