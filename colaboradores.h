#ifndef COLABORADORES_H
#define COLABORADORES_H

#define MAX_COLABORADORES 100

typedef struct {
    int id;            // ID do colaborador
    char nome[20];     // Nome do colaborador
} Colaborador;

extern Colaborador colaboradores[MAX_COLABORADORES];
extern int num_colaboradores;
extern char operador[20];

// Protótipos de funções
void carregarColaboradores();
void salvarColaboradores();
int login();
int autenticarAdministrador();
void cadastrarColaborador();
void listarColaboradores();
void excluirColaborador(); // Adicione a declaração da função de exclusão
Colaborador* buscarColaboradorPorId(int id);
Colaborador* buscarColaboradorPorNome(const char *nome);

#endif // COLABORADORES_H

