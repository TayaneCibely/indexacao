#ifndef IND_H
#define IND_H
#include <stdio.h>

typedef struct livro{
  char titulo[81];
  char autor[51];
  char isbn[21];
  int codigo;
} dado;

typedef struct indice {
  int chave;
  int indice;
} tipo_dado;

typedef struct no_avl{
  tipo_dado *dado;
  struct no_avl *esq, *dir;
  int altura;
} no_avl;

typedef no_avl * arvore;

arvore adicionar(tipo_dado *valor, arvore raiz);

typedef struct tabela{
  FILE *arquivo_dados;
  arvore indices;
} tabela;

int inicializarTabela(tabela *tab);
void finalizar(tabela *tab);
void adicionarLivro(tabela *tab, dado *livro);

void inicializar(arvore *raiz);
arvore adicionar(tipo_dado *valor, arvore raiz);

int altura(arvore raiz);
tipo_dado * maior_elemento(arvore raiz);
tipo_dado * menor_elemento(arvore raiz);
void pre_order(arvore raiz, tabela * tab);
void pos_order(arvore raiz, tabela * tab);
void in_order(arvore raiz, tabela * tab);
void ler_dados(dado *novo);
void tirar_enter(char *string);

void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
arvore carregar_arquivo(char *nome, arvore a);

#endif

