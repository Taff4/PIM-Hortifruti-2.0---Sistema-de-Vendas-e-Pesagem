#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "produtos.h"
#include "vendas.h"
#include "colaboradores.h"  // Esta inclusão já traz operador[50]

#define LIMPA_BUFFER while (getchar() != '\n' && getchar() != EOF)

// Função para obter a data e hora atuais
void obterDataHora(char *buffer, int tamanho) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, tamanho, "%02d/%02d/%d %02d:%02d:%02d", 
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
             tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void registrarVenda(Venda *venda) {
    system("cls");
    Produto p;
    int primeira_venda = 1;
    char input[100];
    venda->codigo_venda = rand();
    
    void mostrarRegistrarVenda() {
        printf("+---------------------------------------------------------+\n");
        printf("|                          REGISTRAR VENDA                 \n");
        printf("+---------------------------------------------------------+\n");
    }

    Venda vendas_registradas[100];
    int total_vendas = 0;

    while (1) {
        listarProdutos();
        mostrarRegistrarVenda();
        if (primeira_venda) {
            printf("Para cancelar e voltar ao menu principal, digite '0'.\n");
        }
        
        printf("+-------------------------------------+\n");
        printf("| Digite o código do produto para registrar a venda: ");
        
        fgets(input, sizeof(input), stdin);

        if (sscanf(input, "%d", &venda->codigo_produto) != 1 || venda->codigo_produto < 0) {
            printf("Entrada inválida! Por favor, digite um número válido.\n");
            continue;
        }

        if (venda->codigo_produto == 0) {
            if (primeira_venda) {
                printf("Operação cancelada. Voltando ao menu principal...\n");
                return;
            } else {
                printf("Venda finalizada com sucesso. Voltando ao menu principal...\n");
                printf("\n+-------------------------+\n");
                printf("| Produtos Registrados    |\n");
                printf("+-------------------------+\n");
                printf("| Código | Produto | Peso    | Valor Total | Colaborador |\n");
                printf("+-------------------------+\n");
                for (int i = 0; i < total_vendas; i++) {
                    printf("| %-6d | %-7s |  %-7.2f |  %-11.2f | %-12s |\n", 
                           vendas_registradas[i].codigo_produto, 
                           vendas_registradas[i].nome_produto, 
                           vendas_registradas[i].peso, 
                           vendas_registradas[i].valor_total,
                           vendas_registradas[i].colaborador);
                }
                printf("+-------------------------+\n");
                return;
            }
        }

        FILE *arq_prod = fopen("produtos.txt", "r+b"); // Abre para leitura e escrita
        int encontrado = 0;
        while (fread(&p, sizeof(Produto), 1, arq_prod) == 1) {
            if (p.codigo == venda->codigo_produto) {
                printf("+-------------------------------------+\n");
                printf("| Produto: %s\n", p.nome);
                printf("+-------------------------------------+\n");
                printf("| Peso do produto (kg): ");
                
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%f", &venda->peso) != 1 || venda->peso <= 0) {
                    printf("Peso inválido! Digite um valor positivo.\n");
                    continue;
                }

                venda->valor_total = venda->peso * p.preco_por_kg;
                strcpy(venda->nome_produto, p.nome);
                strcpy(venda->colaborador, operador);
                encontrado = 1;

                // Atualiza a quantidade usando a função centralizada
                atualizarOuRemoverProduto(venda->codigo_produto, venda->peso);

                // Verifica se o estoque ainda é suficiente
                if (p.quantidade <= 0) {
                    printf("Não é possível registrar a venda, o produto %s está esgotado.\n", p.nome);
                    continue;  // Volta ao loop de vendas
                }

                break; // Saia do loop, pois o produto foi encontrado
            }
        }
        fclose(arq_prod);

        if (!encontrado) {
            printf("Produto não encontrado!\n");
            continue;
        }

        // Captura a data e hora atual
        obterDataHora(venda->data, sizeof(venda->data));

        FILE *arq_vendas = fopen("vendas.txt", "a");
        if (arq_vendas != NULL) {
            fwrite(venda, sizeof(Venda), 1, arq_vendas);
            fclose(arq_vendas);
            printf("Venda registrada com sucesso!\n");
            vendas_registradas[total_vendas++] = *venda;
            Beep(750, 300);
            primeira_venda = 0;
        }

        // Pergunta se deseja continuar registrando outra venda
        printf("Deseja registrar outra venda? (s/n): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'n' || input[0] == 'N') {
            printf("Venda finalizada. Voltando ao menu principal...\n");
            break;
        }
    }
}


void gerarRelatorio() {
    system("cls");
    FILE *arq = fopen("vendas.txt", "r");
    if (arq == NULL) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    Venda v;
    char data_hora[20];
    obterDataHora(data_hora, sizeof(data_hora));

    Venda vendas_registradas[100];
    int total_vendas = 0;

    while (fread(&v, sizeof(Venda), 1, arq) == 1) {
        vendas_registradas[total_vendas++] = v;
    }
    fclose(arq);

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("|                       Relatório de Vendas                                  |");
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| Data e Hora do Relatório: %-45s ", data_hora);
    printf("\n+----------------------------------------------------------------------------+\n");
    char colaborador_atual[50] = "";
    float total_colaborador = 0.0;

    for (int i = 0; i < total_vendas; i++) {
        v = vendas_registradas[i];

        if (strcmp(colaborador_atual, v.colaborador) != 0) {
            if (i > 0) {
                printf("\n+----------------------------------------------------------------------------+\n");
            }
            strcpy(colaborador_atual, v.colaborador);
            total_colaborador = 0.0;

            printf("| Colaborador: %-58s\n|", colaborador_atual);
            printf("\n+----------------------------------------------------------------------------+\n");
            printf("| Código | Produto      | Peso (kg)  | Valor Total (R$)  | Data e Hora         ");
            printf("\n+----------------------------------------------------------------------------+\n");
        }

        // Exibe o código do produto, nome, peso, valor total e data/hora da venda
        printf("| %-6d | %-12s | %-10.2f | %-17.2f | %-19s \n", 
               v.codigo_produto, v.nome_produto, v.peso, v.valor_total, v.data);
        total_colaborador += v.valor_total;
    }

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("|Total de vendas do colaborador: %-44s \n|R$ %-11.2f", colaborador_atual, total_colaborador);
    printf("\n+----------------------------------------------------------------------------+\n");
}
