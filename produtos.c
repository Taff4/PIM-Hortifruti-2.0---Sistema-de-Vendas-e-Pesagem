#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "produtos.h"
#define LIMPA_BUFFER while(getchar() != '\n')
#define TEMPO_ERRO 3000


// Outras funções de produtos já existentes...

void atualizarOuRemoverProduto(int codigo_produto, float peso_vendido) {
    FILE *arq_prod = fopen("produtos.txt", "r+b");
    FILE *temp_arq = fopen("temp_produtos.txt", "w+b");
    Produto p;
    int encontrado = 0;

    if (!arq_prod || !temp_arq) {
        printf("Erro ao abrir os arquivos de produtos!\n");
        if (arq_prod) fclose(arq_prod);
        if (temp_arq) fclose(temp_arq);
        return;
    }

    // Lê os produtos do arquivo original e escreve no arquivo temporário
    while (fread(&p, sizeof(Produto), 1, arq_prod) == 1) {
        if (p.codigo == codigo_produto) {
            p.quantidade -= peso_vendido;  // Reduz a quantidade com base no peso vendido
            encontrado = 1;
            if (p.quantidade > 0) {
                fwrite(&p, sizeof(Produto), 1, temp_arq);  // Mantém o produto atualizado no novo arquivo
            } else {
                printf("Produto %s esgotado e removido do estoque.\n", p.nome);
                // Não grava o produto no arquivo temporário, efetivamente removendo-o
            }
        } else {
            fwrite(&p, sizeof(Produto), 1, temp_arq);  // Copia os outros produtos
        }
    }

    fclose(arq_prod);
    fclose(temp_arq);

    // Substitui o arquivo original pelo temporário
    if (remove("produtos.txt") != 0) {
        perror("Erro ao remover o arquivo original");
    }
    if (rename("temp_produtos.txt", "produtos.txt") != 0) {
        perror("Erro ao renomear o arquivo temporário");
    }

    if (!encontrado) {
        printf("Produto não encontrado para atualização.\n");
    } else {
        printf("Quantidade do produto atualizada com sucesso.\n");
    }
}


// Função para verificar se um produto já existe pelo código
int produtoExiste(int codigo) {
    FILE *arq = fopen("produtos.txt", "rb");
    if (arq == NULL) return 0;

    Produto p;
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        if (p.codigo == codigo) {
            fclose(arq);
            return 1; // Produto existe
        }
    }
    fclose(arq);
    return 0; // Produto não existe
}

void verificarConteudoArquivo() {
    FILE *arq = fopen("produtos.txt", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para verificação.\n");
        return;
    }

    Produto p;
    printf("Conteúdo do arquivo:\n");
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("Código: %d, Nome: %s, Preço: %.2f, Categoria: %s, Quantidade: %d\n",
               p.codigo, p.nome, p.preco_por_kg, p.categoria, p.quantidade);
    }
    fclose(arq);
}

// Função para verificar se um produto já existe pelo nome
int nomeProdutoExiste(const char *nome) {
    FILE *arq = fopen("produtos.txt", "rb");
    if (arq == NULL) return 0;

    Produto p;
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        if (strcmp(p.nome, nome) == 0) {
            fclose(arq);
            return 1; // Produto com o mesmo nome existe
        }
    }
    fclose(arq);
    return 0; // Produto com o mesmo nome não existe
}

// Função para mostrar o cabeçalho do cadastro
void mostrarCabecalhoCadastro() {
    printf("+------------------------------------------------------------+\n");
    printf("|                   CADASTRO DE PRODUTO                      |\n");
    printf("+------------------------------------------------------------+\n");
}
// Função para mostrar o cabeçalho da lista de produtos
void mostrarCabecalhoListaProdutos() {
    printf("+--------------------------------------------------------------------------+\n");
    printf("|                          LISTA DE PRODUTOS                               |\n");
    printf("+--------------------------------------------------------------------------+\n");
}



int coletarDadosProduto(Produto *p) {
    int codigo = -1;
    float preco = -1;
    int quantidade = -1;

    mostrarCabecalhoCadastro(); // Exibe o cabeçalho

    while (codigo < 0) {
        printf("\nDigite o código do produto (ou '0' para retornar ao menu): ");
        char codigoStr[20];
        fgets(codigoStr, sizeof(codigoStr), stdin);
        codigoStr[strcspn(codigoStr, "\n")] = 0; // Remove newline

        if (strcmp(codigoStr, "0") == 0) return 0; // Retorna 0 para sinalizar que o usuário quer sair

        if (sscanf(codigoStr, "%d", &codigo) != 1 || codigo <= 0) {
            exibirErro("Erro: Código inválido. Digite um código positivo.");
            codigo = -1;
        } else if (produtoExiste(codigo)) {
            exibirErro("Erro: Produto já cadastrado. Tente um código diferente.");
            codigo = -1;
            mostrarCabecalhoCadastro(); // Exibe o cabeçalho novamente
        }
    }
    p->codigo = codigo;

    printf("\n+------------------------------------------------------------+\n");
    printf("\n| Nome do produto: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0; // Remove newline

    // Verifica se o nome do produto já existe
    if (nomeProdutoExiste(p->nome)) {
        exibirErro("Erro: Produto com o mesmo nome já cadastrado. Tente um nome diferente.");
        mostrarCabecalhoCadastro(); // Exibe o cabeçalho novamente em caso de erro
        return -1; // Retorna -1 para sinalizar que o cadastro não foi bem-sucedido
    }

    while (preco < 0) {
        printf("| Preço por kg: ");
        char precoStr[20];
        fgets(precoStr, sizeof(precoStr), stdin);
        sscanf(precoStr, "%f", &preco);
        if (preco < 0) {
            exibirErro("Erro: Entrada inválida. Digite um número positivo para o preço.");
            mostrarCabecalhoCadastro(); // Exibe o cabeçalho novamente em caso de erro
        }
    }
    p->preco_por_kg = preco;

    printf("| Categoria: ");
    fgets(p->categoria, sizeof(p->categoria), stdin);
    p->categoria[strcspn(p->categoria, "\n")] = 0; // Remove newline

    while (quantidade < 0) {
        printf("| Quantidade em estoque (kg): ");
        char quantidadeStr[20];
        fgets(quantidadeStr, sizeof(quantidadeStr), stdin);
        sscanf(quantidadeStr, "%d", &quantidade);
        if (quantidade < 0) {
            exibirErro("Erro: Entrada inválida. Digite uma quantidade válida.");
            mostrarCabecalhoCadastro(); // Exibe o cabeçalho novamente em caso de erro
        }
    }
    p->quantidade = quantidade;
    printf("\n+------------------------------------------------------------+\n");
    return 1; // Retorna 1 para indicar que a coleta de dados foi bem-sucedida
}

// Função para cadastrar um produto
void cadastrarProduto(Produto *p) {
    int continuar = 1;

    while (continuar) {
        system("cls");

        int resultadoColeta = coletarDadosProduto(p);
        if (resultadoColeta == 0) {
            return; // Se o usuário escolher voltar ao menu
        } else if (resultadoColeta == -1) {
            continue; // Se a coleta de dados falhar
        }

        printf("\n+------------------------------------------------------------+\n");
        printf("| CONFIRMAÇÃO DE DADOS                                       |\n");
        printf("+------------------------------------------------------------+\n");
        printf("| Código: %d\n", p->codigo);
        printf("| Nome: %s\n", p->nome);
        printf("| Preço por kg: %.2f\n", p->preco_por_kg);
        printf("| Categoria: %s\n", p->categoria);
        printf("| Quantidade em estoque (kg): %d\n", p->quantidade);
        printf("+------------------------------------------------------------+\n");

        char confirmacao;
        printf("Deseja salvar as informações? (s/n): ");
        scanf(" %c", &confirmacao);
        LIMPA_BUFFER;

        if (tolower(confirmacao) != 's') {
            printf("Cadastro cancelado.\n");
            continue;
        }

        FILE *arq = fopen("produtos.txt", "ab");
        if (arq == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return;
        }

        // Grava o produto
        if (fwrite(p, sizeof(Produto), 1, arq) != 1) {
            printf("Erro ao salvar o produto!\n");
        } else {
            Beep(523, 300);
            printf("Produto cadastrado com sucesso!\n");
        }
        fclose(arq);

        printf("Deseja cadastrar mais um produto? (s/n): ");
        scanf(" %c", &confirmacao);
        LIMPA_BUFFER;
        continuar = (tolower(confirmacao) == 's') ? 1 : 0;
    }
}

// Função para listar produtos
void listarProdutos(int menu) {
    system("cls");
    mostrarCabecalhoListaProdutos();
    FILE *arq = fopen("produtos.txt", "rb");
    if (arq == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto p;
    printf("\n+--------------------------------------------------------------------------+\n");
    printf("| Código | Nome           | Preço    | Categoria    | Quantidade (kg)   \n");
    printf("+--------------------------------------------------------------------------+\n");

    int produtosEncontrados = 0; // Contador de produtos encontrados

    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("| %-6d | %-14s | %-8.2f | %-12s | %-14d \n", p.codigo, p.nome, p.preco_por_kg, p.categoria, p.quantidade);
        produtosEncontrados++;
    }

    if (produtosEncontrados == 0) {
        printf("Nenhum produto cadastrado.\n");
    }

    printf("+--------------------------------------------------------------------------+\n");
    fclose(arq);
    printf("Pressione a tecla enter para continuar...\n");
    getchar(); // Espera pela entrada do usuário
}

// Função para carregar produtos de um arquivo
void carregarProdutos() {
    FILE *arq = fopen("produtos.txt", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    Produto p;
    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        printf("Produto carregado: Código: %d, Nome: %s, Preço: %.2f, Categoria: %s, Quantidade: %d\n",
               p.codigo, p.nome, p.preco_por_kg, p.categoria, p.quantidade);
    }
    fclose(arq);
}

// Função para buscar um produto pelo código
Produto* buscarProduto(int codigo) {
    FILE *arq = fopen("produtos.txt", "rb");
    if (arq == NULL) return NULL;

    Produto *p = malloc(sizeof(Produto));
    while (fread(p, sizeof(Produto), 1, arq) == 1) {
        if (p->codigo == codigo) {
            fclose(arq);
            return p; // Produto encontrado
        }
    }
    fclose(arq);
    free(p);
    return NULL; // Produto não encontrado
}

// Função para remover um produto
void removerProduto(int codigo) {
    FILE *arq = fopen("produtos.txt", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "wb");
    if (temp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arq);
        return;
    }

    Produto p;
    int encontrado = 0;

    while (fread(&p, sizeof(Produto), 1, arq) == 1) {
        if (p.codigo != codigo) {
            fwrite(&p, sizeof(Produto), 1, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq);
    fclose(temp);
    remove("produtos.txt");
    rename("temp.txt", "produtos.txt");

    if (encontrado) {
        printf("Produto removido com sucesso.\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

// Função para atualizar um produto
void atualizarProduto(Produto *p) {
    FILE *arq = fopen("produtos.txt", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Produto temp;
    int encontrado = 0;

    while (fread(&temp, sizeof(Produto), 1, arq) == 1) {
        if (temp.codigo == p->codigo) {
            fseek(arq, -sizeof(Produto), SEEK_CUR);
            fwrite(p, sizeof(Produto), 1, arq);
            encontrado = 1;
            break;
        }
    }

    fclose(arq);

    if (encontrado) {
        printf("Produto atualizado com sucesso.\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

