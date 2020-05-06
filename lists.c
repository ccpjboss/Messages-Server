#include "lists.h"
#include <stdio.h>

void inicia_lista(Lista_t *const list)
{
  list->cabeca_m = NULL;
  list->cabeca_u = NULL;
}

void printUtilizadors(Utilizador_t *node)
{
  Utilizador_t *atual = node;
  while (atual != NULL)
  {
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }
}
void insereUser(Lista_t *list)
{
  Utilizador_t *new = (Utilizador_t *)malloc(sizeof(Utilizador_t));
  Utilizador_t *atual = list->cabeca_u;
  new->valor = 5;
  new->proximo = NULL;

  if ( list->cabeca_u == NULL)
  {
    list->cabeca_u = new;
    new->proximo = NULL;
  }
  else
  {
    while (atual->proximo != NULL)
    {
      atual = atual->proximo;
    }
    atual->proximo = new;
    new->proximo = NULL;
  }
}