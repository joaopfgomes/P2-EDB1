#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estatisticas.h"

// Função auxiliar para contar a quantidade de sorteios de um número específico
void quantidadeSorteiosNumero(HashTable* tabela, int numero) {
    int count = 0;
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo* current = tabela->itens[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                if (current->concurso.bolas[j] == numero) {
                    count++;
                    break;
                }
            }
            current = current->next;
        }
    }
    printf("O número %d foi sorteado %d vezes.\n", numero, count);
}

// Função auxiliar para encontrar o número com a maior frequência
void encontrarNumerosFrequentes(HashTable* tabela, int* frequencias) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo* current = tabela->itens[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                frequencias[current->concurso.bolas[j]]++;
            }
            current = current->next;
        }
    }
}

// Função para exibir os dez números mais sorteados
void dezNumerosMaisSorteados(HashTable* tabela) {
    int frequencias[61] = {0}; // Frequência de números de 1 a 60
    encontrarNumerosFrequentes(tabela, frequencias);

    printf("Dez números mais sorteados:\n");
    for (int i = 0; i < 10; i++) {
        int maxFreq = -1, maxIdx = -1;
        for (int j = 1; j <= 60; j++) {
            if (frequencias[j] > maxFreq) {
                maxFreq = frequencias[j];
                maxIdx = j;
            }
        }
        if (maxIdx != -1) {
            printf("Número %d: %d vezes\n", maxIdx, maxFreq);
            frequencias[maxIdx] = -1; // Para não considerar o mesmo número novamente
        }
    }
}

// Função para exibir os dez números menos sorteados
void dezNumerosMenosSorteados(HashTable* tabela) {
    int frequencias[61] = {0}; // Frequência de números de 1 a 60
    encontrarNumerosFrequentes(tabela, frequencias);

    printf("Dez números menos sorteados:\n");
    for (int i = 0; i < 10; i++) {
        int minFreq = 1000000, minIdx = -1;
        for (int j = 1; j <= 60; j++) {
            if (frequencias[j] < minFreq && frequencias[j] > 0) {
                minFreq = frequencias[j];
                minIdx = j;
            }
        }
        if (minIdx != -1) {
            printf("Número %d: %d vezes\n", minIdx, minFreq);
            frequencias[minIdx] = 1000000; // Para não considerar o mesmo número novamente
        }
    }
}

// Função para exibir a quantidade de concursos em um ano específico
void quantidadeConcursosAno(HashTable* tabela, int ano) {
    int count = 0;
    char ano_str[5];
    snprintf(ano_str, sizeof(ano_str), "%d", ano);

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Nodo* current = tabela->itens[i];
        while (current != NULL) {
            if (strstr(current->concurso.data, ano_str) != NULL) {
                count++;
            }
            current = current->next;
        }
    }
    printf("Quantidade de concursos no ano %d: %d\n", ano, count);
}
