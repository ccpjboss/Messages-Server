#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

void login();
void menu_admin();
void menu_utilizador();

void login(){
    char username;
    char password;
    
    while (1)
    {
      printf("Username : ");
      scanf("%s",username); 

      if(username = ""){
          printf("Não insira campos vazios");
      }
      else
      {
          break;
      }
      
    }

    while (1)
    {
      printf("Password: ");
      scanf("%s",password); 

      if(password = ""){
          printf("Não insira campos vazios");
      }
      else
      {
          break;
      }
      
    }
    
    if(!strcmp(username, "Admin") && !strcmp(password, "admin")){
        //menu admin
    }

    /*Verificar se o utilizador existe
    caso exista -> menu utilizador*/
    
}

void menu_admin(){
    int op;
    printf("*****Menu Administrador*****");
    printf("1-Registar Novo Utilizador");
    printf("2-Apagar Utilizador Existente");
    printf("Indique a opção pretendida:");
    scanf("%d",op);

    
    switch (op)
    {
        case 1:
            //Cria novo utilizador
            break;
        case 2:
            //Apaga Utilizador
            break;
        default:
            printf("Opção Inválida");
            break;
    }

}

void menu_utilizador(){
    int op;
    printf("*****Menu Utilizador*****");
    printf("1-Verificar se existem mensagens enviadas por outros utilizadores");
    printf("2-Ler mensagens");
    printf("3-Enviar mensagem");
    printf("4-Apagar mensagens lidas");
    printf("Indique a opção pretendida:");
    scanf("%d",op);

    
    switch (op)
    {
        case 1:
            /* code */
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;

        default:
            printf("Opção Inválida");
            break;
    }
}
