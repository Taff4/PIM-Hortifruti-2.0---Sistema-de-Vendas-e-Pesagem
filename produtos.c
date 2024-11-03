include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "produtos.h"

#define LIMPA_BUFFER fflush(stdin);

// Função que verifica se um produto já existe pelo código
int produtoExiste(int codigo) {
    // Abre o arquivo de produtos em modo leitura para verificar a existência de um código
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

// Função para cadastrar um produto
void cadastrarProduto(Produto *p) {
    system("cls");
    printf("+------------------------------------------------------------+\n");
    printf("|                   CADASTRO DE PRODUTO                      |\n");
    printf("+------------------------------------------------------------+\n");
    printf("| Digite o código do produto ou '0' para retornar ao menu: ");
    
    // Lê a entrada do código como uma string para verificar as condições
    char codigoStr[20];
    scanf("%s", codigoStr);

    // Verifica se o código é "0" para retornar ao menu
    if (strcmp(codigoStr, "0") == 0) {
        printf("Retornando ao menu...\n");
        return;
    }

    // Verifica se o código contém pelo menos um número e não é apenas letras
    int hasDigit = 0;
    int isValid = 1; // Flag para verificar se o código é válido

    for (int i = 0; codigoStr[i] != '\0'; i++) {
        if (isdigit(codigoStr[i])) {
            hasDigit = 1; // Encontrou um dígito
        } else if (!isalnum(codigoStr[i])) { // Alterado para verificar alfanuméricos
            isValid = 0; // Contém caracteres inválidos
            break;
        }
    }

    // Se não tiver dígitos ou for inválido, não permite o cadastro
    if (!hasDigit || !isValid) {
        printf("Erro: O código do produto deve conter pelo menos um número e não pode ser apenas letras.\n");
        return;
    }

    // Converte a string do código para inteiro
    p->codigo = atoi(codigoStr);

    // Verifica se o produto já existe
    if (produtoExiste(p->codigo)) {
        printf("Erro: Produto já cadastrado.\n");
        return;
    }

    LIMPA_BUFFER
    printf("| Nome do produto: ");
    scanf("%49[^\n]", p->nome);
    printf("+------------------------------------------------------------+\n");

    printf("| Preço por kg: ");
    scanf("%f", &p->preco_por_kg);
    printf("+------------------------------------------------------------+\n");

    LIMPA_BUFFER
    printf("| Categoria: ");
    scanf("%19[^\n]", p->categoria);
    printf("+------------------------------------------------------------+\n");

    printf("| Quantidade em estoque (kg): ");  // Entrada da quantidade em kg
    scanf("%d", &p->quantidade);
    printf("+------------------------------------------------------------+\n");

    // Abre o arquivo de produtos em modo de anexo para salvar o novo produto
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

// Função para listar produtos cadastrados
void listarProdutos() {
    system("cls");
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto p;
    printf("\n+--------------------------------------------------------------------------+\n");
    printf("| Código | Nome           | Preço    | Categoria       | Quantidade (kg)   \n");
    printf("+--------------------------------------------------------------------------+\n");

    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("| %-6d | %-14s | %-8.2f | %-12s    | %-14d \n", p.codigo, p.nome, p.preco_por_kg, p.categoria, p.quantidade);
    }
    printf("+--------------------------------------------------------------------------+\n");

    fclose(arq);
}
