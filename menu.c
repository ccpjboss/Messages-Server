#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include "lists.h"
#include <stdbool.h> 


void login(int clientfd, Lista_t *Lista){   
    char msg[]="\n";
    char msg1[]="******Menu Login*****\n";
    char msg2[] = "Insira o seu email: ";
    char msg3[] = "Insira a palavra passe: ";
    char buff[256];
    char buff2[20];
    char email[256];
    char password[20];

    write(clientfd,msg,sizeof(msg));
    write(clientfd,msg1,sizeof(msg1));

    while(1){
        write(clientfd,msg2,sizeof(msg2));
        bzero(buff,256);
        read(clientfd,buff,sizeof(buff));
        buff[strcspn(buff,"\r\n")] = 0;
        strcpy(email,buff);

        write(clientfd,msg3,sizeof(msg3));
        bzero(buff2,20);
        read(clientfd,buff2,sizeof(buff2));
        buff2[strcspn(buff2,"\r\n")] = 0;
        strcpy(password,buff2);

        if(!strcmp(email, "Admin") && !strcmp(password, "admin")){
            menu_admin(clientfd,Lista);
        }

        else if(validLogin(Lista, email, password)){
            menu_utilizador(clientfd,Lista);
        }
        char msg4[]= "Erro no login! Verifique o email e a palavra passe\n";
        write(clientfd,msg4,sizeof(msg4));
    }
}

void menu_admin(int clientfd,Lista_t *Lista)
{
    char buff[20];
    char op[20];
    int i;

    char msg[]="\n";
    char msg1[]="*****Menu Administrador*****\n";
    char msg2[]="1-Registar Novo Utilizador\n";
    char msg3[]="2-Apagar Utilizador Existente\n";
    char msg4[]="3-Sair\n";
    char msg5[]="Indique a opção pretendida:";
    
    write(clientfd,msg,sizeof(msg));
    write(clientfd,msg1,sizeof(msg1));
    write(clientfd,msg2,sizeof(msg2));
    write(clientfd,msg3,sizeof(msg3));
    write(clientfd,msg4,sizeof(msg4));
    
    while(1){
        write(clientfd,msg5,sizeof(msg5));
        bzero(buff,20);
        read(clientfd,buff,sizeof(buff));
        buff[strcspn(buff,"\r\n")] = 0;
        strcpy(op,buff);
        i = atoi(op);
        
        if(i==1 || i==2 || i==3){
            break;
        }
        else{
            char msg6[]="Opção inválida\n";
            write(clientfd,msg6,sizeof(msg6));
        }
    }
   
    switch (i)
    {
        case 1: ;
            char msg[]="\n";
            write(clientfd,msg,sizeof(msg));

            insereUser(clientfd,Lista);
            printUtilizadors(Lista->cabeca_u);
            
            menu_admin(clientfd,Lista);
            
            break;
        case 2:
            //Apaga Utilizador
            break;
        case 3:
            login(clientfd,Lista);
            break;
        default:

            break;
    }
}

void menu_utilizador(int clientfd, Lista_t *Lista)
{
    char buff[20];
    char op[20]; 
    int i;

    char msg[]="\n";
    char msg1[]="*****Menu Utilizador*****\n";
    char msg2[]="1-Caixa de entrada\n";
    char msg3[]="2-Ler mensagens\n";
    char msg4[]="3-Enviar mensagem\n";
    char msg5[]="4-Apagar mensagens lidas\n";
    char msg6[]="5-Sair\n";
    char msg7[]="Indique a opção pretendida:";

    write(clientfd,msg,sizeof(msg));
    write(clientfd,msg1,sizeof(msg1));
    write(clientfd,msg2,sizeof(msg2));
    write(clientfd,msg3,sizeof(msg3));
    write(clientfd,msg4,sizeof(msg4));
    write(clientfd,msg5,sizeof(msg5));
    write(clientfd,msg6,sizeof(msg6));
    
    while(1){
        write(clientfd,msg7,sizeof(msg7));
        bzero(buff,20);
        read(clientfd,buff,sizeof(buff));
        buff[strcspn(buff,"\r\n")] = 0;
        strcpy(op,buff);
        i = atoi(op);
        
        if(i==1 || i==2 || i==3 || i==4 || i==5){
            break;
        }
        else{
            char msg8[]="Opção inválida\n";
            write(clientfd,msg8,sizeof(msg8));
        }
    }

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
    case 5:
        login(clientfd,Lista);
        break;

    default:
    
        break;
    }
}
