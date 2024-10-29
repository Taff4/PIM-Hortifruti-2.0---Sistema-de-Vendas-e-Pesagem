#include <stdio.h>        // Biblioteca para operações de entrada e saída
#include <stdlib.h>       // Biblioteca para alocação de memória
#include <time.h>         // Biblioteca para manipular data e hora
#include "produtos.h"     // Inclui o cabeçalho com a estrutura Produto
#include "vendas.h"       // Inclui o cabeçalho com a estrutura Venda

#define LIMPA_BUFFER fflush(stdin); // Macro para limpar o buffer do teclado

// Função para registrar uma venda
void registrarVenda(Venda *v) {
    listarProdutos(); // Exibe os produtos para o usuário escolher
    printf("Digite o código do produto: ");
    scanf("%d", &v->codigo_produto); // Lê o código do produto vendido
    printf("Peso do produto (kg): ");
    scanf("%f", &v->peso); // Lê o peso do produto

    Produto p;
    FILE *arq = fopen("produtos.txt", "r");
    int encontrado = 0;
    // Busca o produto pelo código no arquivo de produtos
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        if (p.codigo == v->codigo_produto) {
            v->valor_total = v->peso * p.preco_por_kg; // Calcula o valor da venda
            encontrado = 1;
            break;
        }
    }
    fclose(arq);

    if (!encontrado) {
        printf("Produto não encontrado!\n");
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
        printf("Venda registrada com sucesso!\n"); // Mensagem de sucesso após registro
    }
}

// Função para gerar um relatório das vendas
void gerarRelatorio() {
    FILE *arq = fopen("vendas.txt", "r"); // Abre o arquivo para leitura
    if (arq == NULL) {
        printf("Nenhuma venda registrada.\n"); // Mensagem se o arquivo não existir
        return;
    }

    Venda v;
    int count = 0; // Contador para verificar se há vendas

    printf("\nRelatório de Vendas:\n");
    // Lê e exibe cada venda do arquivo
    while (fread(&v, sizeof(Venda), 1, arq) == 1) {
        printf("Código do Produto: %d, Peso: %.2f kg, Valor Total: %.2f, Data: %s\n", v.codigo_produto, v.peso, v.valor_total, v.data);
        count++;
    }

    if (count == 0) {
        printf("Nenhuma venda registrada.\n"); // Exibe se o arquivo estiver vazio
    }

    fclose(arq); // Fecha o arquivo após exibir as vendas
}
