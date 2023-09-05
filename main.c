#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ind.h"

int main(int argc, char *argv[]) {
    tabela tab;
    int opcao;
    inicializarTabela(&tab);

    if (argc == 2) {
        manipular_arquivos(&tab, argv[1], "saida.out");
    }

    while (1) {
        printf("Escolha uma opção:\n");
        printf("1. Altura\n");
        printf("2. Adicionar Livro\n");
        printf("3. Maior Elemento\n");
        printf("4. Menor Elemento\n");
        printf("5. Pre-Order\n");
        printf("6. In-Order\n");
        printf("7. Pos-Order\n");
        printf("8. Salvar Arquivo\n");
        printf("9. Carregar Arquivo\n");
        printf("99. Finalizar\n");
        printf("Opção: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("%d\n", altura(tab.indices));
                break;
            case 2:
                dado novo;
                ler_dados(&novo);
                adicionarLivro(&tab, &novo);
                break;
            case 3:
                printf("%d\n", maior_elemento(tab.indices)->chave);
                break;
            case 4:
                printf("%d\n", menor_elemento(tab.indices)->chave);
                break;
            case 5:
                pre_order(tab.indices, &tab);
                printf("\n");
                break;
            case 6:
                in_order(tab.indices, &tab);
                printf("\n");
                break;
            case 7:
                pos_order(tab.indices, &tab);
                printf("\n");
                break;
            case 8:
                salvar_arquivo("dados.dat", tab.indices);
                break;
            case 9:
                tab.indices = carregar_arquivo("indices.dat", tab.indices);
                break;
            case 99:
                finalizar(&tab);
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
    return 0;
}

