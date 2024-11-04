#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "produtos.h"

#define LIMPA_BUFFER while(getchar() != '\n')
#define TEMPO_ERRO 3000

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

// Função para coletar dados do produto
int coletarDadosProduto(Produto *p) {
    int codigo = -1;
    float preco = -1;
    int quantidade = -1;

    mostrarCabecalhoCadastro(); // Garantindo que o cabeçalho apareça sempre no início

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
    p->nome[strcspn(p->nome, "\n")] = 0;

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
    p->categoria[strcspn(p->categoria, "\n")] = 0;

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
            // Se o usuário escolher voltar ao menu, interrompe o loop e sai da função
            return;
        } else if (resultadoColeta == -1) {
            // Se a coleta de dados falhar (produto duplicado), reinicia o processo
            continue;
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

// Função para listar produtos cadastrados
void listarProdutos() {
    system("cls");
    mostrarCabecalhoListaProdutos(); // Exibe o cabeçalho da lista de produtos
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

    // Adicionar opção de excluir produto
    printf("Para excluir um produto, digite 0 e pressione Enter.\nPara continuar a operação, digite 1: ");
    char opcao;
    scanf(" %c", &opcao);
    
    if (opcao == '0') {
        int codigo;
        printf("Digite o código do produto a ser excluído: ");
        scanf("%d", &codigo);
        LIMPA_BUFFER;

        // Verifica login antes de remover o produto
        char usuario[20], senha[20];
        printf("Digite o login: ");
        fgets(usuario, sizeof(usuario), stdin);
        usuario[strcspn(usuario, "\n")] = 0; // Remove newline
        printf("Digite a senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = 0; // Remove newline

        if (strcmp(usuario, "adm") == 0 && strcmp(senha, "123") == 0) {
            char confirmacao;
            printf("Tem certeza que deseja excluir o produto com código %d? (s/n): ", codigo);
            scanf(" %c", &confirmacao);
            LIMPA_BUFFER;

            if (tolower(confirmacao) == 's') {
                removerProduto(codigo);
            } else {
                printf("Operação de exclusão cancelada.\n");
            }
        } else {
            printf("Login ou senha incorretos. A exclusão foi cancelada.\n");
        }
    } else if (opcao == '1') {
        printf("Voltando ao menu principal...\n");
    } else {
        printf("Opção inválida. Voltando ao menu principal...\n");
    }

    printf("Pressione qualquer tecla para continuar...\n");
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


