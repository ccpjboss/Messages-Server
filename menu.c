#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include "lists.h"


void login(int clientfd){
    char msg_send1 [] = "Insira o seu email: ";
    char msg_send2 [] = "Insira a palavra passe: ";
    char buff[256];
    char buff2[20];
    char username[256];
    char password[20];

    write(clientfd,msg_send1,sizeof(msg_send1));
    bzero(buff,256);
    read(clientfd,buff,sizeof(buff));
    buff[strcspn(buff,"\n")] = 0;
    strcpy(username,buff);

    write(clientfd,msg_send2,sizeof(msg_send2));
    bzero(buff2,20);
    read(clientfd,buff2,sizeof(buff2));
    buff2[strcspn(buff2,"\n")] = 0;
    strcpy(password,buff2);
    printf("1");
    if(!strcmp(username, "Admin") && !strcmp(password, "admin")){
        printf("2");
        menu_admin(clientfd);
    }

    /*Verificar se o utilizador existe
    caso exista -> menu utilizador*/
    
}

void menu_admin(int clientfd){
    char buff[20];
    char op[20];

    char msg1[]="*****Menu Administrador*****\n";
    char msg2[]="1-Registar Novo Utilizador\n";
    char msg3[]="2-Apagar Utilizador Existente\n";
    char msg4[]="Indique a opção pretendida:";
    
    write(clientfd,msg1,sizeof(msg1));
    write(clientfd,msg2,sizeof(msg2));
    write(clientfd,msg3,sizeof(msg3));
    write(clientfd,msg4,sizeof(msg4));
     bzero(buff,20);
    read(clientfd,buff,sizeof(buff));
    buff[strcspn(buff,"\n")] = 0;
   
    strcpy(op,buff);
    int i = atoi(op);
   
    switch (i)
    {
        case 1: ;
            Lista_t *Lista = (Lista_t *) malloc(sizeof(Lista_t));
            inicia_lista(Lista);
            insereUser(clientfd,Lista);
            printUtilizadors(Lista->cabeca_u);
            break;
        case 2:
            //Apaga Utilizador
            break;
        default:
            char msg5[]="Opção Inválida\n";
            write(clientfd,msg5,sizeof(msg5));
            break;
    }

}

void menu_utilizador(int clientfd){
    char buff[20];
    char op[20]; 

    char msg1[]="*****Menu Utilizador*****\n";
    char msg2[]="1-Verificar se existem mensagens enviadas por outros utilizadores\n";
    char msg3[]="2-Ler mensagens\n";
    char msg4[]="3-Enviar mensagem\n";
    char msg5[]="4-Apagar mensagens lidas\n";
    char msg6[]="Indique a opção pretendida:";

    write(clientfd,msg1,sizeof(msg1));
    write(clientfd,msg2,sizeof(msg2));
    write(clientfd,msg3,sizeof(msg3));
    write(clientfd,msg4,sizeof(msg4));
    write(clientfd,msg5,sizeof(msg5));
    write(clientfd,msg6,sizeof(msg6));
     bzero(buff,20);
    read(clientfd,buff,sizeof(buff));
    buff[strcspn(buff,"\n")] = 0;

    strcpy(op,buff);
    int i = atoi(op);
    
    switch (i)
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
            char msg7[]="Opção Inválida\n";
            write(clientfd,msg7,sizeof(msg7));
            break;
    }
}
