#ifndef PRODUTOS_H
#define PRODUTOS_H

// Estrutura que define os atributos de um Produto
typedef struct {
    int codigo;
    char nome[50];
    float preco_por_kg;
    char categoria[20];
} Produto;

// Função para cadastrar um produto
void cadastrarProduto();

// Função para listar produtos cadastrados
void listarProdutos();

#endif
