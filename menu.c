#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

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
