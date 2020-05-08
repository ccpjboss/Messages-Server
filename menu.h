#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdbool.h> 
#include <stdlib.h>
#include "lists.h"


void login(int clientfd, Lista_t *Lista);
void menu_admin(int clientfd,Lista_t *Lista);
void menu_utilizador(int clientfd,Lista_t *Lista);

#endif