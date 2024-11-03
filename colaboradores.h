// colaboradores.h
#ifndef COLABORADORES_H
#define COLABORADORES_H

#define MAX_COLABORADORES 100

extern char colaboradores[MAX_COLABORADORES][20];
extern int num_colaboradores;
extern char operador[20];

// Prot�tipos de fun��es
void carregarColaboradores();
void salvarColaboradores();
int login();
int autenticarAdministrador();
void cadastrarColaborador();
void listarColaboradores();

#endif // COLABORADORES_H

