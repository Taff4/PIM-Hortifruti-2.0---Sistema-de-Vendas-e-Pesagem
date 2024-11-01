#ifndef VENDAS_H
#define VENDAS_H

// Estrutura que define os atributos de uma Venda
typedef struct {
    int codigo_produto;
    float peso;
    float valor_total;
    char data[11];
} Venda;

// Função para registrar uma venda
void registrarVenda();

// Função para gerar o relatório de vendas
void gerarRelatorio();

#endif

