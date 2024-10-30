#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct {
    int codigo;
    char nome[50];
    float preco_por_kg;
    char categoria[20];
} Produto;

void cadastrarProduto();
void listarProdutos();

#endif
