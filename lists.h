#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED
#include <stdbool.h> 

struct Utilizador
{
    char email [256];
    char password [20];
    bool admin;
    int codigo_user;
    struct Utilizador *proximo;
};

struct Date
{
    int dia;
    int mes;
    int ano;
};

struct Mensagem
{
  struct Date data;
  int codigo_user;
  char text[256]; 
  bool lida;
  struct Mensagem *proximo;
};

struct Lista
{
    struct Mensagem *cabeca_m;
    struct Utilizador *cabeca_u;
};

struct Lista inicia(struct Lista a );






#endif