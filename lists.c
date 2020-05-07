#include "lists.h"
#include <stdio.h>
#include <string.h>

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
    printf("%s \t %s \n", atual->email, atual->password);
    atual = atual->proximo;
  }
}
void insereUser(int socket_fd, Lista_t *list)
{
  Utilizador_t *new = (Utilizador_t *)malloc(sizeof(Utilizador_t));
  Utilizador_t *atual = list->cabeca_u;

  char msg_send1 [] = "Insira o seu email: ";
  char msg_send2 [] = "Insira a palavra passe: ";
  char buff[256];
  char buff2[20];

  write(socket_fd,msg_send1,sizeof(msg_send1));
  bzero(buff,256);
  read(socket_fd,buff,sizeof(buff));
  buff[strcspn(buff,"\n")] = 0;
  strcpy(new->email,buff);

  write(socket_fd,msg_send2,sizeof(msg_send2));
  bzero(buff2,20);
  read(socket_fd,buff2,sizeof(buff2));
  buff2[strcspn(buff2,"\n")] = 0;
  strcpy(new->password,buff2);

  new->admin = false;
  new->codigo_user = 1; //TODO: Think about user code
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