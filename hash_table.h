#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

#define TAMANHO_TABELA 100

// Estrutura para armazenar um concurso
typedef struct {
    int numero;
    char data[11];
    int bolas[6];
} Concurso;

// Estrutura para um nó da lista ligada na tabela de dispersão
typedef struct Nodo {
    Concurso concurso;
    struct Nodo* next;
} Nodo;

// Estrutura para a tabela de dispersão
typedef struct {
    Nodo* itens[TAMANHO_TABELA];
} HashTable;

// Funções para a tabela de dispersão
HashTable* criarTabelaHash();
unsigned int funcaoHash(int numero);
void inserirConcurso(HashTable* tabela, Concurso concurso);
Concurso* buscarConcurso(HashTable* tabela, int numero);
void removerConcurso(HashTable* tabela, int numero);
void listarTodosConcursos(HashTable* tabela);
void carregarConcursosArquivo(HashTable* tabela, const char* nomeArquivo);
void liberarTabelaHash(HashTable* tabela);

#endif // HASH_TABLE_H
