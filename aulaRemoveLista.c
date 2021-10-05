#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
  int valor;
  struct no *prox;

} no, inicio, fim;

typedef struct noAux
{
  struct no *anterior;
  struct no *atual;

} noAux;

void createList(struct no **inicio, struct no **fim);
void insertOnRight(struct no **inicio, struct no **fim, int valor);
void insertOnLeft(struct no **inicio, struct no **fim, int valor);
void insertOnMidle(struct no **inicio, struct no **fim, int valor, int insere);
void deleteOnRight(struct no **inicio, struct no **fim);
void deleteOnLeft(struct no **inicio, struct no **fim);
void deleteOnMidle(struct no **inicio, struct no **fim, int valor);
void showList(struct no **inicio);
no * searchPreviousValue(struct no **inicio, int valor);
no * searchActualValue(struct no **inicio, int valor);

int menu();

int main() {

  no *inicio;
  no *fim;
  noAux *aux;
  no *atual;
  int valor, opcao, add, insere;

  opcao = menu();

  while(opcao != 0){

    switch (opcao) {
      case 1:
        createList(&inicio,&fim);
      break;
      
      case 2:
        printf("Inserindo na direita\n");
        printf("Digite um valor:\n");
        scanf("%d",&valor);

        insertOnRight(&inicio,&fim,valor);
        break;
        
      case 3:
        printf("Inserindo na esquerda\n");
        printf("Digite um valor:\n");
        scanf("%d",&valor);

        insertOnLeft(&inicio,&fim,valor);
        break;
        
      case 4:
        deleteOnRight(&inicio,&fim);
        break;
        
      case 5:
        deleteOnLeft(&inicio,&fim);
        break;
        
      case 6:
        showList(&inicio);
        break;

      case 7:
        printf("\n\n");
        printf("-----------------------------------------------------------------------------\n");
        showList(&inicio);
        printf("-----------------------------------------------------------------------------");
        printf("\nDeseja inserir após qual valor acima?\n");
        printf("\n>");
        scanf("%d",&insere);

        printf("\nQual valor deseja inserir?\n\n");
        scanf("%d",&valor);

        insertOnMidle(&inicio,&fim, valor, insere);
        break;

      case 8:
        printf("\n\n");
        printf("-----------------------------------------------------------------------------\n");
        showList(&inicio);
        printf("-----------------------------------------------------------------------------");
        printf("\nDeseja deletar qual valor acima?\n");
        printf("\n>");
        scanf("%d",&valor);

        deleteOnMidle(&inicio, &fim, valor);
        break;

      case 9:
        printf("\n\n");
        printf("-----------------------------------------------------------------------------\n");
        showList(&inicio);
        printf("-----------------------------------------------------------------------------");
        printf("\nDeseja buscar qual valor acima?\n");
        printf("\n>");
        scanf("%d",&valor);

        atual = searchActualValue(&inicio, valor);
        // atual = aux->atual;
        if(atual->valor == NULL) {
          printf("\n\nValor nao encontrado\n\n");
        } else {
          printf("\n\nValor %i encontrado\n\n", atual->valor);
        }
        break;

      default:
        printf("\n\nOpcao nao encontrada\n\n"); 
        break;
    }
    opcao = menu();
  }
}

int menu() {
  int op;
    printf("Menu\n");
    printf("\n1- Criar uma lista\n");
    printf("2- Inserir a direita\n");
    printf("3- Inserir a esquerda\n");
    printf("4- Excluir a direita\n");
    printf("5- Excluir a esquerda\n");
    printf("6- Imprimir lista\n");
    printf("7- Inserir onde quiser\n");
    printf("8- Deletar onde quiser\n");
    printf("9- Buscar valor\n");
    printf("0- Sair\n\n");
    scanf("%d",&op);
    return op;
}

void createList(struct no **inicio, struct no **fim) {
  *inicio = NULL;
  *fim = NULL;
  return 0;
}


void insertOnRight(struct no **inicio, struct no **fim, int valor) {

  struct no *p;
  p = (struct no *) malloc(sizeof(struct no));

  if(p){

    p->valor = valor;
    p->prox = NULL;
  }
  if(*inicio == NULL) {
    *inicio = p;
  }else {
    (*fim)->prox = p;
  }
  *fim = p;
}

void insertOnLeft(struct no **inicio, struct no **fim, int valor) {

  struct no *p;
  p=(struct no*)malloc(sizeof(struct no));

  if(p){

    p->valor=valor;
    p->prox=NULL;

    if(*inicio==NULL) {
      *inicio=p;
    }
    else {
      p->prox = *inicio;
    }
    *inicio=p;
  }
}

void insertOnMidle(struct no **inicio, struct no **fim, int valor, int insere) {
  struct no *p;
  struct no *m;
  struct no *atual;
  p=(struct no*)malloc(sizeof(struct no));

  m = *inicio;
  atual = searchActualValue(&m, insere);

  if(p) {
    p->valor=valor;
    p->prox=atual->prox;
    atual->prox = p;
  }

}

void deleteOnRight(struct no **inicio, struct no **fim) {
  no *aux, *p;

  if(*inicio == NULL){
    printf("\n\nLista vazia\n\n\n");
  } else {
    if((*inicio)->prox == NULL) {
      free(*inicio);
      *fim = NULL;
      *inicio=NULL;
    } else {
      p = *inicio;
      while(p->prox)  {
        aux = p;
        p = p->prox;
      }
      aux->prox = NULL;
      *fim = aux;
      free(p);
    }
  }
}

void deleteOnLeft(struct no **inicio, struct no **fim) {
  no *aux;

  aux = *inicio;

  if(*inicio == NULL) {
    printf("\n\nLista vazia\n\n\n");
  } else {
    *inicio = (*inicio)->prox;
    if(*inicio == NULL) 
      *fim = NULL;
    free(aux);
  }
}

void deleteOnMidle(struct no **inicio, struct no **fim, int valor) {
  struct no *aux;
  struct no *f;
  struct no *atual;
  struct no *anterior;
  // struct noAux *m;

  if(*inicio == NULL) {
    printf("\n\nLista vazia\n\n\n");
  } else {

    aux = *inicio;
    f = *fim;
    // m = searchActualValue(&aux, valor);

    atual = searchActualValue(&aux, valor);

    if(*inicio == atual) {
      *inicio = (*inicio)->prox;
      if(*inicio == NULL) 
        *fim = NULL;
      free(aux);
    } else {
      anterior = searchPreviousValue(&aux, valor);
      anterior->prox = atual->prox;
      free(atual);
    }
  }
}

no * searchActualValue(struct no **inicio, int valor) {
  if(*inicio == NULL) {
    printf("\n\nLista vazia\n\n\n");
  } else {
    struct no *p;
    // struct noAux *m;
    p=(struct no*)malloc(sizeof(struct no));
    
    if(p){
      // struct no *anterior;
      struct no *aux;

      // anterior = *inicio;
      // aux = anterior->prox;
      aux = *inicio;

      while(aux->valor != NULL) {

        if(aux->valor == valor) {
          // m->anterior = anterior;
          // m->atual = aux;
          return aux;
        }
        aux = aux->prox;
        // anterior = anterior->prox;
      }
    }
  }
}

no * searchPreviousValue(struct no **inicio, int valor) {
  if(*inicio == NULL) {
    printf("\n\nLista vazia\n\n\n");
  } else {
    struct no *p;
    // struct noAux *m;
    p=(struct no*)malloc(sizeof(struct no));
    
    if(p){
      struct no *anterior;
      struct no *aux;

      anterior = *inicio;
      aux = anterior->prox;

      while(aux->valor != NULL) {

        if(aux->valor == valor) {
          // m->anterior = anterior;
          // m->atual = aux;
          return anterior;
        }
        aux = aux->prox;
        anterior = anterior->prox;
      }
    }
  }
}

void showList(struct no **inicio) {
  struct no *proximo;
  proximo = *inicio;
  while(proximo != NULL){
    printf("Endereco do no: %i = valor do no %i -> proximo endereco %i\n", proximo, proximo->valor, proximo->prox);
    proximo = proximo->prox;
  }
}
