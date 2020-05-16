#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdbool.h> 
#include <stdlib.h>
#include "lists.h"


void login(int clientfd );
void menu_admin(int clientfd);
void menu_utilizador(int clientfd,char* email_user);

#endif