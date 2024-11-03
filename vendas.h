#ifndef VENDAS_H
#define VENDAS_H

// Estrutura que define os atributos de uma Venda
typedef struct {
    int codigo_produto;
    float peso;
    float valor_total;
    char data[11];
    char colaborador[50]; // Nome do colaborador
    char nome_produto[50]; // Nome do produto
} Venda;

// Função para registrar uma venda
void registrarVenda(Venda *venda);

// Função para gerar o relatório de vendas
void gerarRelatorio();

#endif

