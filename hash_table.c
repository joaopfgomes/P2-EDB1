#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// Função hash para mapear números de concurso para índices na tabela
unsigned int funcaoHash(int numero) {
    return numero % TAMANHO_TABELA;
}

// Cria e inicializa uma tabela de dispersão
HashTable* criarTabelaHash() {
    HashTable* tabela = (HashTable*)malloc(sizeof(HashTable));
    if (!tabela) {
        perror("Falha ao criar a tabela de dispersão");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->itens[i] = NULL;
    }
    return tabela;
}

// Insere um concurso na tabela de dispersão
void inserirConcurso(HashTable* tabela, Concurso concurso) {
    unsigned int index = funcaoHash(concurso.numero);
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (!novoNodo) {
        perror("Falha ao alocar memória para o novo nó");
        exit(EXIT_FAILURE);
    }
    novoNodo->concurso = concurso;
    novoNodo->next = tabela->itens[index];
    tabela->itens[index] = novoNodo;
}

// Busca um concurso na tabela de dispersão
Concurso* buscarConcurso(HashTable* tabela, int numero) {
    unsigned int index = funcaoHash(numero);
    Nodo* current = tabela->itens[index];
    while (current != NULL) {
        if (current->concurso.numero == numero) {
            return &current->concurso;
        }
        current = current->next;
    }
    return NULL;
}

// Remove um concurso da tabela de dispersão
void removerConcurso(HashTable* tabela, int numero) {
    unsigned int index = funcaoHash(numero);
    Nodo* current = tabela->itens[index];
    Nodo* prev = NULL;
    while (current != NULL) {
        if (current->concurso.numero == numero) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                tabela->itens[index] = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Lista todos os concursos na tabela de dispersão
void listarTodosConcursos(HashTable* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo* current = tabela->itens[i];
        while (current != NULL) {
            printf("Concurso %d: Data: %s, Números: %d %d %d %d %d %d\n",
                   current->concurso.numero,
                   current->concurso.data,
                   current->concurso.bolas[0],
                   current->concurso.bolas[1],
                   current->concurso.bolas[2],
                   current->concurso.bolas[3],
                   current->concurso.bolas[4],
                   current->concurso.bolas[5]);
            current = current->next;
        }
    }
}

// Carrega concursos de um arquivo CSV ou TSV
void carregarConcursosArquivo(HashTable* tabela, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Falha ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Concurso concurso;
        if (sscanf(linha, "%d,%10[^,],%d,%d,%d,%d,%d,%d",
                   &concurso.numero,
                   concurso.data,
                   &concurso.bolas[0],
                   &concurso.bolas[1],
                   &concurso.bolas[2],
                   &concurso.bolas[3],
                   &concurso.bolas[4],
                   &concurso.bolas[5]) == 8) {
            inserirConcurso(tabela, concurso);
        }
    }
    fclose(arquivo);
}

// Libera a memória alocada para a tabela de dispersão
void liberarTabelaHash(HashTable* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo* current = tabela->itens[i];
        while (current != NULL) {
            Nodo* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(tabela);
}
