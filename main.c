#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "estatisticas.h"

// Função para exibir o menu
void menu() {
    printf("1. Inserir Concurso\n");
    printf("2. Buscar Concurso\n");
    printf("3. Remover Concurso\n");
    printf("4. Visualizar Todos os Concursos\n");
    printf("5. Carregar Concursos de um Arquivo\n");
    printf("6. Exibir Estatísticas\n");
    printf("7. Sair\n");
}

int main() {
    HashTable* tabela = criarTabelaHash();
    int opcao, numero, bolas[6];
    char data[11];
    char arquivo[100];
    int ano;

    do {
        menu();
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                printf("Digite o número do concurso: ");
                scanf("%d", &numero);
                getchar();
                printf("Digite a data do sorteio (dd-mm-aaaa): ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0'; // Remove o newline
                printf("Digite os 6 números sorteados: ");
                scanf("%d %d %d %d %d %d", &bolas[0], &bolas[1], &bolas[2], &bolas[3], &bolas[4], &bolas[5]);
                Concurso concurso = {numero, "", {0}};
                strncpy(concurso.data, data, sizeof(concurso.data));
                memcpy(concurso.bolas, bolas, sizeof(concurso.bolas));
                inserirConcurso(tabela, concurso);
                break;

            case 2:
                printf("Digite o número do concurso para buscar: ");
                scanf("%d", &numero);
                Concurso* encontrado = buscarConcurso(tabela, numero);
                if (encontrado != NULL) {
                    printf("Concurso %d: Data: %s, Números: %d %d %d %d %d %d\n",
                           encontrado->numero,
                           encontrado->data,
                           encontrado->bolas[0],
                           encontrado->bolas[1],
                           encontrado->bolas[2],
                           encontrado->bolas[3],
                           encontrado->bolas[4],
                           encontrado->bolas[5]);
                } else {
                    printf("Concurso não encontrado.\n");
                }
                break;

            case 3:
                printf("Digite o número do concurso para remover: ");
                scanf("%d", &numero);
                removerConcurso(tabela, numero);
                printf("Concurso removido se existia.\n");
                break;

            case 4:
                listarTodosConcursos(tabela);
                break;

            case 5:
                printf("Digite o nome do arquivo para carregar: ");
                fgets(arquivo, sizeof(arquivo), stdin);
                arquivo[strcspn(arquivo, "\n")] = '\0'; // Remove o newline
                carregarConcursosArquivo(tabela, arquivo);
                break;

            case 6:
                printf("Escolha uma estatística a ser exibida:\n");
                printf("1. Quantidade de sorteios de um número\n");
                printf("2. Dez números mais sorteados\n");
                printf("3. Dez números menos sorteados\n");
                printf("4. Quantidade de concursos em um ano\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);
                getchar();  // Limpa o buffer

                switch (opcao) {
                    case 1:
                        printf("Digite o número para consultar a quantidade de sorteios: ");
                        scanf("%d", &numero);
                        quantidadeSorteiosNumero(tabela, numero);
                        break;

                    case 2:
                        dezNumerosMaisSorteados(tabela);
                        break;

                    case 3:
                        dezNumerosMenosSorteados(tabela);
                        break;

                    case 4:
                        printf("Digite o ano para consultar a quantidade de concursos: ");
                        scanf("%d", &ano);
                        quantidadeConcursosAno(tabela, ano);
                        break;

                    default:
                        printf("Opção inválida.\n");
                        break;
                }
                break;

            case 7:
                liberarTabelaHash(tabela);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
