#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "produtos.h"
#include "vendas.h"
#include "colaboradores.h"
#include "menu.h"

// Função para exibir mensagens de erro
void exibirErro(const char *mensagem) {
    printf("Erro: %s\n", mensagem);
    Beep(500, 500);
    Sleep(1000);
    system("cls");
}

void exibirDataHora() {
    time_t agora = time(NULL);
    struct tm *dataHora = localtime(&agora);
    dataHora->tm_hour -= 3; // Ajusta para o horário de Brasília
    mktime(dataHora);

    printf("| Data: %02d/%02d/%d               \n", 
           dataHora->tm_mday, dataHora->tm_mon + 1, dataHora->tm_year + 1900);
    printf("| Hora: %02d:%02d                 \n", 
           dataHora->tm_hour, dataHora->tm_min);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
        exibirMenu(acesso);
        opcao = escolherOpcao(acesso);

        // Processa a opção selecionada
        if (acesso == 2) {
            switch (opcao) {
                case '1':
                    cadastrarProduto(&produto);
                    break;
                case '2':
                    listarProdutos();
                    break;
                case '3':
                    strcpy(venda.colaborador, operador);
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
                    excluirProduto(); // Chama a função de exclusão de produto
                    break;
                case '8':
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    exibirErro("Opção inválida! Tente novamente."); // Para garantir que o programa não feche se uma opção inválida for escolhida
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
                    strcpy(venda.colaborador, operador);
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
                    exibirErro("Opção inválida! Tente novamente."); // Para garantir que o programa não feche se uma opção inválida for escolhida
                    break;
            }
        }

        system("pause");

    } while ((acesso == 2 && opcao != '8') || (acesso == 1 && opcao != '5')); // Verificando a saída correta

    return 0;
}




