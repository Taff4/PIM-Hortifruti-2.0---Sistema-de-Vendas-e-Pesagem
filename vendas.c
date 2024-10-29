#include <stdio.h>        // Biblioteca para opera��es de entrada e sa�da
#include <stdlib.h>       // Biblioteca para aloca��o de mem�ria
#include <time.h>         // Biblioteca para manipular data e hora
#include "produtos.h"     // Inclui o cabe�alho com a estrutura Produto
#include "vendas.h"       // Inclui o cabe�alho com a estrutura Venda

#define LIMPA_BUFFER fflush(stdin); // Macro para limpar o buffer do teclado

// Fun��o para registrar uma venda
void registrarVenda(Venda *v) {
    listarProdutos(); // Exibe os produtos para o usu�rio escolher
    printf("Digite o c�digo do produto: ");
    scanf("%d", &v->codigo_produto); // L� o c�digo do produto vendido
    printf("Peso do produto (kg): ");
    scanf("%f", &v->peso); // L� o peso do produto

    Produto p;
    FILE *arq = fopen("produtos.txt", "r");
    int encontrado = 0;
    // Busca o produto pelo c�digo no arquivo de produtos
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        if (p.codigo == v->codigo_produto) {
            v->valor_total = v->peso * p.preco_por_kg; // Calcula o valor da venda
            encontrado = 1;
            break;
        }
    }
    fclose(arq);

    if (!encontrado) {
        printf("Produto n�o encontrado!\n");
        return;
    }

    // Registra a data atual da venda
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(v->data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Salva a venda no arquivo
    arq = fopen("vendas.txt", "a");
    if (arq != NULL) {
        fwrite(v, sizeof(Venda), 1, arq);
        fclose(arq);
        printf("Venda registrada com sucesso!\n");
    }
}

// Fun��o para gerar um relat�rio das vendas
void gerarRelatorio() {
    FILE *arq = fopen("vendas.txt", "r"); // Abre o arquivo para leitura
    if (arq == NULL) {
        printf("Nenhuma venda registrada.\n"); // Mensagem se o arquivo n�o existir
        return;
    }

    Venda v;
    int count = 0; // Contador para verificar se h� vendas

    printf("\nRelat�rio de Vendas:\n");
    // L� e exibe cada venda do arquivo
    while (fread(&v, sizeof(Venda), 1, arq) == 1) {
        printf("C�digo do Produto: %d, Peso: %.2f kg, Valor Total: %.2f, Data: %s\n", v.codigo_produto, v.peso, v.valor_total, v.data);
        count++;
    }

    if (count == 0) {
        printf("Nenhuma venda registrada.\n"); // Exibe se o arquivo estiver vazio
    }

    fclose(arq); // Fecha o arquivo ap�s exibir as vendas
}

