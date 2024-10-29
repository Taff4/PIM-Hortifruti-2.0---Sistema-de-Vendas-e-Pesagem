#ifndef VENDAS_H
#define VENDAS_H

typedef struct {
    int codigo_produto;
    float peso;
    float valor_total;
    char data[11];
} Venda;

void registrarVenda(Venda *v);
void gerarRelatorio();

#endif

