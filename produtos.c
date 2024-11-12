#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "produtos.h"
#define LIMPA_BUFFER while(getchar() != '\n')
#define TEMPO_ERRO 3000

// Função para atualizar ou remover produto do estoque
void atualizarOuRemoverProduto(int codigo_produto, float peso_vendido) {
    FILE *arq_prod = fopen("produtos.txt", "r+b");  // Abre o arquivo de produtos para leitura e escrita binária
    if (!arq_prod) {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }

    Produto p;
    int encontrado = 0;

    // Lê os produtos e atualiza o estoque
    while (fread(&p, sizeof(Produto), 1, arq_prod) == 1) {
        if (p.codigo == codigo_produto) {
            if (p.quantidade >= peso_vendido) {  // Verifica se há estoque suficiente para a venda
                p.quantidade -= peso_vendido;  // Diminui a quantidade com base no peso vendido
                if (p.quantidade == 0) {
                    printf("Atenção: O estoque do produto %s está zerado.\n", p.nome);
                }
                fseek(arq_prod, -sizeof(Produto), SEEK_CUR);  // Vai para a posição do produto no arquivo
                fwrite(&p, sizeof(Produto), 1, arq_prod);  // Reescreve o produto atualizado
                encontrado = 1;
                printf("Produto %s atualizado. ", p.nome);
                break;  // Sai do loop após a atualização do produto
            } else {
                printf("Estoque insuficiente para o produto %s. Quantidade disponível: %.2f kg\n", p.nome, p.quantidade);
                break;
            }
        }
    }

    fclose(arq_prod);

    if (!encontrado) {
        printf("Produto não encontrado para atualização.\n");
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

// Função para coletar dados do produto
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
            printf("Erro: Código inválido. Digite um código positivo.\n");
            codigo = -1;
        } else if (produtoExiste(codigo)) {
            printf("Erro: Produto já cadastrado. Tente um código diferente.\n");
            codigo = -1;
            mostrarCabecalhoCadastro(); // Exibe o cabeçalho novamente
        }
    }
    p->codigo = codigo;

    printf("\n+------------------------------------------------------------+\n");
    printf("\n| Nome do produto: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0; // Remove newline

    while (preco < 0) {
        printf("| Preço por kg: ");
        char precoStr[20];
        fgets(precoStr, sizeof(precoStr), stdin);
        sscanf(precoStr, "%f", &preco);
        if (preco < 0) {
            printf("Erro: Entrada inválida. Digite um número positivo para o preço.\n");
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
            printf("Erro: Entrada inválida. Digite uma quantidade válida.\n");
            mostrarCabecalhoCadastro(); // Exibe o cabeçalho novamente em caso de erro
        }
    }
    p->quantidade = quantidade;
    printf("\n+------------------------------------------------------------+\n");
    return 1; // Retorna 1 para indicar que a coleta de dados foi bem-sucedida
}

// Função para cadastrar ou alterar produtos
void cadastrarProduto(Produto *p) {
    int continuar = 1;
    char opcao;

    while (continuar) {
        system("cls");
        mostrarCabecalhoCadastro();

        printf("\nDigite a opção desejada:\n");
        printf("| 1) Cadastrar um novo produto\n");
        printf("| 2) Adicionar quantidade para um produto cadastrado\n");
        printf("| 3) Alterar preço de um produto\n");
        printf("| 0) Voltar ao menu\n");
        printf("| Escolha: ");
        scanf(" %c", &opcao);
        LIMPA_BUFFER;

        if (opcao == '0') {
            return;  // Volta ao menu
        } else if (opcao == '1') {
            // Cadastrar novo produto
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
            if (!arq) {
                printf("Erro ao abrir o arquivo para cadastro.\n");
                return;
            }

            fwrite(p, sizeof(Produto), 1, arq); // Salva os dados no arquivo
            fclose(arq);

            printf("Produto cadastrado com sucesso!\n");

            // Mostrar conteúdo do arquivo após o cadastro
            printf("\nConteúdo do arquivo atualizado:\n");
            verificarConteudoArquivo();

        } else if (opcao == '2') {
            // Adicionar quantidade
            int codigo;
            printf("Digite o código do produto para adicionar quantidade: ");
            scanf("%d", &codigo);
            LIMPA_BUFFER;

            FILE *arq = fopen("produtos.txt", "r+b");
            if (!arq) {
                printf("Erro ao abrir o arquivo de produtos!\n");
                return;
            }

            Produto p;
            int encontrado = 0;

            while (fread(&p, sizeof(Produto), 1, arq) == 1) {
                if (p.codigo == codigo) {
                    printf("Produto encontrado: %s\n", p.nome);
                    printf("Digite a quantidade a ser adicionada: ");
                    int quantidade_adicional;
                    scanf("%d", &quantidade_adicional);

                    if (quantidade_adicional <= 0) {
                        printf("Quantidade inválida. Valor deve ser maior que 0.\n");
                        fclose(arq);
                        continue;
                    }

                    p.quantidade += quantidade_adicional;  // Adiciona quantidade
                    fseek(arq, -sizeof(Produto), SEEK_CUR);  // Volta para a posição do produto
                    fwrite(&p, sizeof(Produto), 1, arq);  // Atualiza o produto no arquivo

                    printf("Quantidade de %s atualizada para %d\n", p.nome, p.quantidade);
                    encontrado = 1;
                    break;
                }
            }
            fclose(arq);

            if (!encontrado) {
                printf("Produto com código %d não encontrado.\n", codigo);
            }
        } else if (opcao == '3') {
            // Alterar preço
            int codigo;
            printf("Digite o código do produto para alterar o preço: ");
            scanf("%d", &codigo);
            LIMPA_BUFFER;

            FILE *arq = fopen("produtos.txt", "r+b");
            if (!arq) {
                printf("Erro ao abrir o arquivo de produtos!\n");
                return;
            }

            Produto p;
            int encontrado = 0;

            while (fread(&p, sizeof(Produto), 1, arq) == 1) {
                if (p.codigo == codigo) {
                    printf("Produto encontrado: %s\n", p.nome);
                    printf("Digite o novo preço por kg: ");
                    scanf("%f", &p.preco_por_kg);

                    if (p.preco_por_kg <= 0) {
                        printf("Preço inválido. Valor deve ser maior que 0.\n");
                        fclose(arq);
                        continue;
                    }

                    fseek(arq, -sizeof(Produto), SEEK_CUR);  // Volta para a posição do produto
                    fwrite(&p, sizeof(Produto), 1, arq);  // Atualiza o produto no arquivo

                    printf("Preço do produto %s alterado para %.2f\n", p.nome, p.preco_por_kg);
                    encontrado = 1;
                    break;
                }
            }
            fclose(arq);

            if (!encontrado) {
                printf("Produto com código %d não encontrado.\n", codigo);
            }
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

        printf("Deseja continuar? (s/n): ");
        char continuar_opcao;
        scanf(" %c", &continuar_opcao);
        LIMPA_BUFFER;
        continuar = tolower(continuar_opcao) == 's';
    }
}

// Função para mostrar o cabeçalho da lista de produtos
void mostrarCabecalhoListaProdutos() {
    printf("+--------------------------------------------------------------------------+\n");
    printf("|                          LISTA DE PRODUTOS                               |\n");
    printf("+--------------------------------------------------------------------------+\n");
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


