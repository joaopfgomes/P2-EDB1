#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include "hash_table.h"

// Calcula e exibe a quantidade de sorteios de um número específico.
void quantidadeSorteiosNumero(HashTable* tabela, int numero);

// Exibe os dez números mais sorteados.
void dezNumerosMaisSorteados(HashTable* tabela);

// Exibe os dez números menos sorteados.
void dezNumerosMenosSorteados(HashTable* tabela);

// Exibe a quantidade de concursos em um ano específico.
void quantidadeConcursosAno(HashTable* tabela, int ano);

#endif // ESTATISTICAS_H
