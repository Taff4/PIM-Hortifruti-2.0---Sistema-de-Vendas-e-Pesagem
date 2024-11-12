#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct {
    int codigo;
    char nome[50];
    float preco_por_kg;
    char categoria[30];
    int quantidade; // Certifique-se de que esse campo existe
    char operador[50];
} Produto;


// Verifica se um produto já existe com base no código fornecido.
int produtoExiste(int codigo);

// Exibe uma mensagem de erro.
void exibirErro(const char *mensagem);

// Mostra o cabeçalho do cadastro de produtos.
void mostrarCabecalhoCadastro();

// Coleta os dados do produto do usuário.
int coletarDadosProduto(Produto *p); // Modificado para retornar int

// Cadastra um novo produto.
void cadastrarProduto(Produto *p);

// Lista todos os produtos cadastrados.
void listarProdutos();

// Carrega e exibe produtos de um arquivo.
void carregarProdutos();

// Busca um produto pelo código e retorna um ponteiro para ele.
Produto* buscarProduto(int codigo);

// Remove um produto pelo código.
void removerProduto(int codigo);

// Atualiza os dados de um produto existente.
void atualizarProduto(Produto *p);

void atualizarOuRemoverProduto(int codigo_produto, float quantidade_vendida);

#endif // PRODUTOS_H


