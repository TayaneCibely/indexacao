#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

void inicializar(arvore *raiz){
    *raiz = NULL;
}

int inicializarTabela(tabela *tab){
    inicializar(&tab->indices);
    tab->arquivo_dados = fopen("dados.dat", "a+b");
    tab->indices = carregar_arquivo("indices.dat", tab->indices);
    if(tab->arquivo_dados != NULL){
	return 1;
    }else{
	return 0;
    }
}

void finalizar(tabela *tab){
    fclose(tab->arquivo_dados);
    salvar_arquivo("indices.dat", tab->indices);
}

void adicionarLivro(tabela *tab, dado *livro){
    if(tab->arquivo_dados != NULL){
	tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));

	novo->chave = livro->codigo;

	fseek(tab->arquivo, 0L, tab->arquivo_dados);
	novo->indice = ftell(tab->arquivo_dados);

	fwrite(livro, sizeof(dado), 1, tab->arquivo_dados);
	tab->indices = adicionar(novo, tab->indices);
    }
}

void adicionar(tipo_dado *valor, arvore raiz){
   if(raiz == NULL){
	arvore novo = (arvore) malloc(sizeof(struct no_bst));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
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

void pre_order(arvore raiz, tabela*tab){
  if(raiz != NULL){
    imprimir_elemento(raiz, tab){
      pre_order(raiz->esq, tab);
      pre_order(raiz->dir, tab);
    }
  }
}

void pos_order(arvore raiz, tabela *tab){
  if(raiz != NULL){
    pos_order(raiz->esq, tab);
    pos_order(raiz->dir, tab);
    imprimir_elemento(raiz, tab);
  }
}

void in_order(arvore raiz, tabela *tab){
  if(raiz != NULL{
    in_order(raiz->esq, tab);
    imprimir_elemento(raiz, tab);
    in_order(raiz->dir, tab);
    }
}

void imprimir_elemento(arvore raiz, tabela *tab){
  dado * temp = (dado *)malloc(sizeof(dado));
  temp->codigo = 1000;
  printf("Indice: %d\n", raiz->dado->indice);

  fseek(tav, long off, int whence)
}

dado * ler_dados(){
  dado *novo = (dado *) malloc(sizeof(dado));
  //fpurge(stdin);
  getchar();
  printf("Titulo: ");
  fgetc(novo->titulo, 80, stdin);
  tirar_enter(novo->titulo);
  printf("Autor: ");
  fgets(novo->autor, 50, stdin);
  tirar_enter("Isbn: ");
  fgets(novo->isbn, 20, stdin);
  tirar_enter(novo->isbn);
  printf("Codigo: ");
  scanf("%d", &novo->codigo);
  return novo;
}

void tirar_enter(char *string){
  string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore a){
  FILE *arq;
  arq = fopen(nome, "wb");
  if(arq !+ NULL){
    salvar_arquivo(a, arq);
    fclose(arq);
  }
}

void salvar_auxiliar(arvore raiz, FILE *arq){
  if(raiz != NULL){
    fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
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



