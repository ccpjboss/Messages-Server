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
    char msg1[]="\n******Menu Login*****\n";
    char msg2[] = "Insira o seu email: ";
    char msg3[] = "Insira a palavra passe: ";
    char buff[256];
    char buff2[20];
    char email[256];
    char password[20];

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
            menu_utilizador(clientfd,Lista,email);
        }
        char msg4[]= "Erro no login! Verifique o email e a palavra passe.\n";
        write(clientfd,msg4,sizeof(msg4));
    }
}

void menu_admin(int clientfd,Lista_t *Lista)
{
    char buff[20];
    char op[20];
    int i;

    char msg1[]="\n*****Menu Administrador*****\n";
    char msg2[]="1-Registar Novo Utilizador\n";
    char msg3[]="2-Apagar Utilizador Existente\n";
    char msg4[]="3-Sair\n";
    char msg5[]="Indique a opção pretendida:";

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
            char msg6[]="Opção inválida!\n";
            write(clientfd,msg6,sizeof(msg6));
        }
    }
   
    switch (i)
    {
        case 1: ;

            insereUser(clientfd,Lista);
            printUtilizadors(Lista->cabeca_u);
            
            char msg7[]="\nUtilizador registado com sucesso!";
            write(clientfd,msg7,sizeof(msg7));

            menu_admin(clientfd,Lista);
            
            break;
        case 2: ;
            char email[256];
            char buff2[256];

            char msg8[]= "Indique o email do utilizador que pretende eliminar:";
            write(clientfd,msg8,sizeof(msg8));
            bzero(buff2,256);
            read(clientfd,buff2,sizeof(buff2));
            buff2[strcspn(buff2,"\r\n")] = 0;
            strcpy(email,buff2);

            deleteUser(Lista,email);
            printUtilizadors(Lista->cabeca_u);
            
            char msg9[]="Utilizador eliminado com sucesso!";
            write(clientfd,msg9,sizeof(msg9));

            menu_admin(clientfd,Lista);
            break;
        case 3:
            login(clientfd,Lista);
            break;
        default:

            break;
    }
}

void menu_utilizador(int clientfd, Lista_t *Lista,char* email_user)
{
    char buff[20];
    char op[20]; 
    int i;

    char msg1[]="\n*****Menu Utilizador*****\n";
    char msg2[]="1-Caixa de entrada\n";
    char msg3[]="2-Ler mensagens\n";
    char msg4[]="3-Enviar mensagem\n";
    char msg5[]="4-Apagar mensagens lidas\n";
    char msg6[]="5-Sair\n";
    char msg7[]="Indique a opção pretendida:";

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
    case 1: ;
        char msg9[]="\n*****Caixa de Entrada*****\n";
        write(clientfd,msg9,sizeof(msg9));
        printMessages(Lista,email_user);

        menu_utilizador(clientfd,Lista,email_user);
        break;
    case 2:

        break;
    case 3: ;
        char texto[256];
        char buff2[256];
        char users[20];
        char destino[256];
        int j;
        int k;
        int id = 0;

        char msg10[]="Escreva a mensagem que pretende enviar\n";
        write(clientfd,msg10,sizeof(msg10));
        bzero(buff2,256);
        read(clientfd,buff2,sizeof(buff2));
        buff2[strcspn(buff2,"\r\n")] = 0;
        strcpy(texto,buff2);

        char msg11[] = "Para quantos utilizadores prentende enviar essa mensagem? ";
        write(clientfd,msg11,sizeof(msg11));
        bzero(buff,20);
        read(clientfd,buff,sizeof(buff));
        buff[strcspn(buff,"\r\n")] = 0;
        strcpy(users,buff);
        j = atoi(users);

        char msg12[] = "Indique o email do utilizador: ";

        for(k=0; k<j; ++k){
            write(clientfd,msg12,sizeof(msg12));
            bzero(buff2,256);
            read(clientfd,buff2,sizeof(buff2));
            buff2[strcspn(buff2,"\r\n")] = 0;
            strcpy(destino,buff2);

            insereMensagem(Lista,email_user,destino,id,texto,0);
            id+=1;
        }
        menu_utilizador(clientfd,Lista,email_user);
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
