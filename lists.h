#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED
#include <stdbool.h> 
#include <stdlib.h>

typedef struct Utilizador
{
    char email [256];
    char password [20];
    bool admin;
    int codigo_user;
    struct Utilizador *proximo;
}Utilizador_t;

struct Date
{
    int dia;
    int mes;
    int ano;
};

typedef struct Mensagem
{
  struct Date data;
  int codigo_user_r; //codigo_user remetente
  int codigo_user_d; //codigo_user destinatario
  int msgid; //ID da mensagem
  char text[256]; 
  bool lida;
  struct Mensagem *proximo;
}Mensagem_t;

typedef struct Lista
{
    struct Mensagem *cabeca_m;
    struct Utilizador *cabeca_u;
}Lista_t;

void inicia_lista(Lista_t *const list);
void printUtilizadors(Utilizador_t *const node);
void insereUser(int socket_fd, Lista_t *list);
bool verificaDupUser(Lista_t *list, char *email);

#endif