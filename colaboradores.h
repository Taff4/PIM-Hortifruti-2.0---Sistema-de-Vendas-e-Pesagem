// colaboradores.h
#ifndef COLABORADORES_H
#define COLABORADORES_H

#define MAX_COLABORADORES 100

extern char colaboradores[MAX_COLABORADORES][20];
extern int num_colaboradores;
extern char operador[20];

// Protótipos de funções
void carregarColaboradores();
void salvarColaboradores();
int login();
int autenticarAdministrador();
void cadastrarColaborador();
void listarColaboradores();

#endif // COLABORADORES_H

