#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ind.h"

// Declaração da função de busca para evitar erro de compilação
tipo_dado *buscar_registro_interno(int chave, arvore raiz);

void inicializar(arvore *raiz) {
    *raiz = NULL;
}

int inicializarTabela(tabela *tab) {
    inicializar(&tab->indices);
    tab->arquivo_dados = fopen("dados.dat", "a+b");
    
    if (tab->arquivo_dados != NULL) {
        tab->indices = carregar_arquivo("indices.dat", tab->indices);
        return 1;
    } else {
        return 0;
    }
}

tipo_dado *maior_elemento(arvore raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }

    return raiz->dado;
}

tipo_dado *menor_elemento(arvore raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }

    return raiz->dado;
}

void finalizar(tabela *tab) {
    if (tab->arquivo_dados != NULL) {
        fclose(tab->arquivo_dados);
    }
    
    salvar_arquivo("indices.dat", tab->indices);
}

dado *ler_dados_do_arquivo(FILE *arquivo) {
    dado *novo = (dado *)malloc(sizeof(dado));
    
    if (novo != NULL) {
        if (fread(novo, sizeof(dado), 1, arquivo) != 1) {
            free(novo);
            novo = NULL;
        }
    }
    
    return novo;
}

tipo_dado *buscar_registro(tabela *tab, int chave) {
    return buscar_registro_interno(chave, tab->indices);
}

void adicionarLivro(tabela *tab, dado *livro) {
    if (tab->arquivo_dados != NULL) {
        long posicao_anterior = ftell(tab->arquivo_dados);
        fseek(tab->arquivo_dados, 0L, SEEK_END);
        fwrite(livro, sizeof(dado), 1, tab->arquivo_dados);
        long posicao = posicao_anterior;
        tipo_dado *novo = (tipo_dado *)malloc(sizeof(tipo_dado));
        novo->chave = livro->codigo;
        novo->indice = posicao;
        novo->altura = 1;
        tab->indices = adicionar(novo, tab->indices);
    }
}

void manipular_arquivos(tabela *tab, const char *arquivo_in, const char *arquivo_out) {
    FILE *entrada = fopen(arquivo_in, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    FILE *saida = fopen(arquivo_out, "w");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(entrada);
        return;
    }

    tipo_dado *buscar_registro_interno(int chave, arvore raiz) {
        if (raiz == NULL) {
            return NULL;
        }

        if (chave == raiz->dado->chave) {
            return raiz->dado;
        } else if (chave < raiz->dado->chave) {
            return buscar_registro_interno(chave, raiz->esq);
        } else {
            return buscar_registro_interno(chave, raiz->dir);
        }
    }

    tipo_dado *buscar_registro(tabela *tab, int chave) {
        return buscar_registro_interno(chave, tab->indices);
    }

    int opcao;
    while (fscanf(entrada, "%d", &opcao) != EOF) {
        switch (opcao) {
            case 1: 
                {
                    dado *livro = ler_dados_do_arquivo(entrada);
                    adicionarLivro(tab, livro);
                    free(livro);
                }
                break;
            case 2: 
                {
                    int chave;
                    fscanf(entrada, "%d", &chave);
                    tipo_dado *encontrado = buscar_registro(chave, tab->indices);

                    if (encontrado != NULL) {
                        dado registro;
                        fseek(tab->arquivo_dados, encontrado->indice, SEEK_SET);
                        fread(&registro, sizeof(dado), 1, tab->arquivo_dados);

                        fprintf(saida, "Registro encontrado:\n");
                        fprintf(saida, "Titulo: %s\n", registro.titulo);
                        fprintf(saida, "Autor: %s\n", registro.autor);
                        fprintf(saida, "ISBN: %s\n", registro.isbn);
                        fprintf(saida, "Codigo: %d\n", registro.codigo);
                    } else {
                        fprintf(saida, "Registro nao encontrado.\n");
                    }
                }
                break;
        }
    }

    fclose(entrada);
    fclose(saida);
}

arvore adicionar(tipo_dado *valor, arvore raiz){
    if(raiz == NULL){
        arvore novo = (arvore) malloc(sizeof(struct no_avl));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    if(valor->chave > raiz->dado->chave){
        raiz->dir = adicionar(valor, raiz->dir);
    }else{
        raiz->esq = adicionar(valor, raiz->esq);
    }
    return raiz;
}

int altura(arvore raiz){
   if(raiz == NULL){
	return 0;
   }
   return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b){
  if(a > b){
    return a;
  }else{
    return b;
  }
}

void pre_order(arvore raiz, tabela* tab) {
    if (raiz != NULL) {
        imprimir_elemento(raiz, tab);
        pre_order(raiz->esq, tab);
        pre_order(raiz->dir, tab);
    }
}

void pos_order(arvore raiz, tabela *tab) {
    if (raiz != NULL) {
        pos_order(raiz->esq, tab);
        pos_order(raiz->dir, tab);
        imprimir_elemento(raiz, tab);
    }
}

void in_order(arvore raiz, tabela *tab) {
    if (raiz != NULL) {
        in_order(raiz->esq, tab);
        imprimir_elemento(raiz, tab);
        in_order(raiz->dir, tab);
    }
}

void imprimir_elemento(arvore raiz, tabela *tab) {
    dado *temp = (dado *)malloc(sizeof(dado));
    temp->codigo = 1000;
    printf("Indice: %d\n", raiz->dado->indice);

    fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);

    fread(temp, sizeof(dado), 1, tab->arquivo_dados);

    printf("Titulo: %s\n", temp->titulo);
    printf("Autor: %s\n", temp->autor);
    printf("ISBN: %s\n", temp->isbn);
    printf("Codigo: %d\n", temp->codigo);

    free(temp);
}

void ler_dados(dado *novo) {
    getchar(); // Consumir o caractere de nova linha pendente

    printf("Titulo: ");
    fgets(novo->titulo, sizeof(novo->titulo), stdin);
    tirar_enter(novo->titulo);

    printf("Autor: ");
    fgets(novo->autor, sizeof(novo->autor), stdin);
    tirar_enter(novo->autor);

    printf("Isbn: ");
    fgets(novo->isbn, sizeof(novo->isbn), stdin);
    tirar_enter(novo->isbn);

    printf("Codigo: ");
    scanf("%d", &novo->codigo);
    getchar(); // Consumir o caractere de nova linha pendente após ler o código
}

dado *ler_dados() {
    dado *novo = (dado *)malloc(sizeof(dado));

    getchar(); // Consumir o caractere de nova linha pendente

    printf("Titulo: ");
    fgets(novo->titulo, sizeof(novo->titulo), stdin);
    tirar_enter(novo->titulo);

    getchar(); // Pausa para permitir a visualização

    printf("Autor: ");
    fgets(novo->autor, sizeof(novo->autor), stdin);
    tirar_enter(novo->autor);

    getchar();

    printf("Isbn: ");
    fgets(novo->isbn, sizeof(novo->isbn), stdin);
    tirar_enter(novo->isbn);

    getchar();

    printf("Codigo: ");
    scanf("%d", &novo->codigo);

    return novo;
}

void tirar_enter(char *string){
  string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore a) {
    FILE *arq = fopen(nome, "wb");
    
    if (arq != NULL) {
        salvar_auxiliar(a, arq);
        fclose(arq);
    } else {
        printf("Erro ao abrir o arquivo '%s' para escrita.\n", nome);
    }
}

void salvar_auxiliar(arvore raiz, FILE *arq) {
    if (raiz != NULL) {
        if (raiz->dado != NULL) {
            fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
        }
        salvar_auxiliar(raiz->esq, arq);
        salvar_auxiliar(raiz->dir, arq);
    }
}

arvore carregar_arquivo(char *nome, arvore a){
  FILE *arq;
  arq = fopen(nome, "rb");
  tipo_dado * temp;
  if(arq != NULL){
    temp = (tipo_dado *) malloc(sizeof(tipo_dado));
    while(fread(temp, sizeof(tipo_dado), 1, arq)){
      a = adicionar(temp, a);
      temp = (tipo_dado *) malloc(sizeof(tipo_dado));
    }
    fclose(arq);
  }
  return a;
}

