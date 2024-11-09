 #ifndef VENDAS_H
#define VENDAS_H

// Estrutura que define os atributos de uma Venda
typedef struct {
    int codigo_venda;       // Identificador único da venda
    int codigo_produto;     // Código do produto vendido
    float peso;             // Peso do produto vendido em kg
    float valor_total;      // Valor total da venda (peso * preço por kg)
    char data[20];          // Data da venda (formato dd/mm/yyyy hh:mm:ss)
    char colaborador[50];   // Nome do colaborador que realizou a venda
    char nome_produto[50];  // Nome do produto vendido
} Venda;

// Função para registrar uma nova venda
void registrarVenda(Venda *venda);

// Função para gerar o relatório de vendas, agrupado por colaborador
void gerarRelatorio();

// Função para atualizar uma venda existente
void atualizarVenda(int codigo_venda);

#endif
