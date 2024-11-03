#ifndef PRODUTOS_H
#define PRODUTOS_H

// Estrutura que define os atributos de um Produto
typedef struct {
    int codigo;               // Código único do produto
    char nome[50];           // Nome do produto
    float preco_por_kg;      // Preço por kg do produto
    char categoria[20];      // Categoria do produto
    int quantidade;           // Campo para a quantidade em estoque (alterado para int)
} Produto;

// Função para cadastrar um produto
void cadastrarProduto(Produto *p);

// Função para listar produtos cadastrados
void listarProdutos();

#endif // PRODUTOS_H

