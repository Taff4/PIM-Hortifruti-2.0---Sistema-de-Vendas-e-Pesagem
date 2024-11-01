#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "produtos.h"
#include "vendas.h"

#define LIMPA_BUFFER while (getchar() != '\n' && getchar() != EOF)

// Função para registrar uma nova venda
void registrarVenda() {
	system("cls");
    Venda v;
    Produto p;

    listarProdutos();
    printf("+-------------------------------------+\n");
    printf("| Digite o código do produto: ");
    scanf("%d", &v.codigo_produto);

    FILE *arq_prod = fopen("produtos.txt", "r");
    int encontrado = 0;
    while (fread(&p, sizeof(Produto), 1, arq_prod) == 1) {
        if (p.codigo == v.codigo_produto) {
        	printf("+-------------------------------------+\n");
            printf("| Produto: %s\n", p.nome);
            printf("+-------------------------------------+\n");
            printf("| Peso do produto (kg): ");
            scanf("%f", &v.peso);
            printf("+-------------------------------------+\n");
            v.valor_total = v.peso * p.preco_por_kg;
            encontrado = 1;
            break;
        }
    }
    fclose(arq_prod);

    if (!encontrado) {
        printf("Produto não encontrado!\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(v.data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    FILE *arq_vendas = fopen("vendas.txt", "a");
    if (arq_vendas != NULL) {
        fwrite(&v, sizeof(Venda), 1, arq_vendas);
        fclose(arq_vendas);
        printf("Venda registrada com sucesso!\n");
    }
}

// Função para gerar relatório das vendas
void gerarRelatorio() {
	system("cls");
    FILE *arq = fopen("vendas.txt", "r");
    if (arq == NULL) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    Venda v;
    printf("\n+--------------------------------------------------+\n");
    printf("|                Relatório de Vendas               |\n");
    printf("+--------------------------------------------------+\n");
    printf("| Código | Peso    | Valor Total | Data            |\n");
    printf("+--------------------------------------------------+\n");

    while (fread(&v, sizeof(Venda), 1, arq) == 1) {
        printf("| %-6d | %-7.2f | %-11.2f | %-15s |\n", v.codigo_produto, v.peso, v.valor_total, v.data);
    }
    printf("+--------------------------------------------------+\n");

    fclose(arq);
}
