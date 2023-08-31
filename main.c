#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ind.h"

int main(int argc, char *argv[]){

    tabela tab;
    int opcao;
    inicializarTabela(&tab);

    while(1){
     	scanf("%d", &opcao);

        switch(opcao){
            case 1:
            printf("d\n", altura(tab.indices));
            break;
            case 2:
            adicionarLivro(&tab, ler_dados());
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
        }
    }
    return 0;
}
