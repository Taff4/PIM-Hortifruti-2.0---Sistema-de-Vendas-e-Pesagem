#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produtos.h"
#include "vendas.h"
#include "colaboradores.h"

#define LIMPA_BUFFER fflush(stdin);

void exibirDataHora() {
    time_t agora = time(NULL);
    struct tm *dataHora = localtime(&agora);
    dataHora->tm_hour -= 3;
    mktime(dataHora);

    printf("| Data: %02d/%02d/%d               \n", 
           dataHora->tm_mday, dataHora->tm_mon + 1, dataHora->tm_year + 1900);
    printf("| Hora: %02d:%02d                 \n", 
           dataHora->tm_hour, dataHora->tm_min);
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    system("color 4f");

    carregarColaboradores();

    int acesso = login();
    if (acesso == 0) {
        return 0;
    }

    Produto produto;
    Venda venda;
    char opcao;

    do {
        system("cls");
        printf("+------------------------------------+\n");
        printf("|        SISTEMA VIVA FRUIT          |\n");
        printf("+------------------------------------+\n");
        printf("| Operador(a): %-24s \n", operador);
        exibirDataHora();
        printf("+------------------------------------+\n");

        if (acesso == 2) {
            printf("| 1. Cadastrar Produto               |\n");
            printf("| 2. Lista de Produtos               |\n");
            printf("| 3. Registrar Venda                 |\n");
            printf("| 4. Gerar Relatório de Vendas       |\n");
            printf("| 5. Cadastrar Colaborador(a)        |\n");
            printf("| 6. Listar Colaboradores            |\n");
            printf("| 7. Sair                            |\n");
        } else {
            printf("| 1. Cadastrar Produto               |\n");
            printf("| 2. Lista de Produtos               |\n");
            printf("| 3. Registrar Venda                 |\n");
            printf("| 4. Gerar Relatório de Vendas       |\n");
            printf("| 5. Sair                            |\n");
        }
        printf("+------------------------------------+\n");

        printf("Escolha uma opção: ");
        LIMPA_BUFFER
        scanf("%c", &opcao);

        if (acesso == 2) {
            switch (opcao) {
                case '1':
                    cadastrarProduto(&produto);
                    break;
                case '2':
                    listarProdutos();
                    break;
                case '3':
                    strcpy(venda.colaborador, operador); // Copia o operador logado para o campo `colaborador` da venda
                    registrarVenda(&venda);
                    break;
                case '4':
                    gerarRelatorio();
                    break;
                case '5':
                    cadastrarColaborador();
                    break;
                case '6':
                    listarColaboradores();
                    break;
                case '7':
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                    break;
            }
        } else {
            switch (opcao) {
                case '1':
                    if (autenticarAdministrador()) {
                        cadastrarProduto(&produto);
                    }
                    break;
                case '2':
                    listarProdutos();
                    break;
                case '3':
                    strcpy(venda.colaborador, operador); // Copia o operador logado para o campo `colaborador` da venda
                    registrarVenda(&venda);
                    break;
                case '4':
                    if (autenticarAdministrador()) {
                        gerarRelatorio();
                    }
                    break;
                case '5':
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                    break;
            }
        }
        system("pause");
    } while ((acesso == 2 && opcao != '7') || (acesso == 1 && opcao != '5'));
    
    return 0;
}
