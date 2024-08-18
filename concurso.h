#ifndef CONCURSO_H
#define CONCURSO_H

typedef struct {
    int numero;
    char data[11];
    int numeros[6];
} Concurso;

Concurso criarConcurso(int numero, char* data, int* numeros);
void imprimirConcurso(Concurso concurso);

#endif
