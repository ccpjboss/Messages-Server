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
#include "menu.h"
int id = 0;

void login(int clientfd)
{
    char msg1[] = "\n******Menu Login*****\n";
    char msg2[] = "Insira o seu email: ";
    char msg3[] = "Insira a palavra passe: ";
    char buff[256];
    char buff2[20];
    char email[256];
    char password[20];

    write(clientfd, msg1, sizeof(msg1));

    while (1)
    {
        write(clientfd, msg2, sizeof(msg2));
        bzero(buff, 256);
        read(clientfd, buff, sizeof(buff));
        buff[strcspn(buff, "\r\n")] = 0;
        strcpy(email, buff);

        write(clientfd, msg3, sizeof(msg3));
        bzero(buff2, 20);
        read(clientfd, buff2, sizeof(buff2));
        buff2[strcspn(buff2, "\r\n")] = 0;
        strcpy(password, buff2);

        if (!strcmp(email, "Admin") && !strcmp(password, "admin"))
        {
            menu_admin(clientfd);
        }

        else if (validLogin(email, password))
        {
            menu_utilizador(clientfd, email);
        }
        char msg4[] = "Erro no login! Verifique o email e a palavra passe.\n";
        write(clientfd, msg4, sizeof(msg4));
    }
}

void menu_admin(int clientfd)
{
    char buff[20];
    char op[20];
    int i;

    char msg1[] = "\n*****Menu Administrador*****\n";
    char msg2[] = "1-Registar Novo Utilizador\n";
    char msg3[] = "2-Apagar Utilizador Existente\n";
    char msg4[] = "3-Sair\n";
    char msg5[] = "Indique a opção pretendida:";

    write(clientfd, msg1, sizeof(msg1));
    write(clientfd, msg2, sizeof(msg2));
    write(clientfd, msg3, sizeof(msg3));
    write(clientfd, msg4, sizeof(msg4));

    while (1)
    {
        write(clientfd, msg5, sizeof(msg5));
        bzero(buff, 20);
        read(clientfd, buff, sizeof(buff));
        buff[strcspn(buff, "\r\n")] = 0;
        strcpy(op, buff);
        i = atoi(op);

        if (i == 1 || i == 2 || i == 3)
        {
            break;
        }
        else
        {
            char msg6[] = "Opção inválida!\n";
            write(clientfd, msg6, sizeof(msg6));
        }
    }

    switch (i)
    {
    case 1:;

        insereUser(clientfd);
        printUtilizadors();

        char msg7[] = "\nUtilizador registado com sucesso!";
        write(clientfd, msg7, sizeof(msg7));

        menu_admin(clientfd);

        break;
    case 2:;
        char email[256];
        char buff2[256];

        char msg8[] = "Indique o email do utilizador que pretende eliminar:";
        write(clientfd, msg8, sizeof(msg8));
        bzero(buff2, 256);
        read(clientfd, buff2, sizeof(buff2));
        buff2[strcspn(buff2, "\r\n")] = 0;
        strcpy(email, buff2);

        deleteUser(email);
        printUtilizadors();

        char msg9[] = "Utilizador eliminado com sucesso!";
        write(clientfd, msg9, sizeof(msg9));

        menu_admin(clientfd);
        break;
    case 3:
        login(clientfd);
        break;
    default:

        break;
    }
}

void menu_utilizador(int clientfd, char *email_user)
{
    char buff[20];
    char op[20];
    int i;

    char msg1[] = "\n*****Menu Utilizador*****\n";
    char msg2[] = "1-Caixa de entrada\n";
    char msg3[] = "2-Ler mensagens\n";
    char msg4[] = "3-Enviar mensagem\n";
    char msg5[] = "4-Apagar mensagens lidas\n";
    char msg6[] = "5-Sair\n";
    char msg7[] = "Indique a opção pretendida:";

    write(clientfd, msg1, sizeof(msg1));
    write(clientfd, msg2, sizeof(msg2));
    write(clientfd, msg3, sizeof(msg3));
    write(clientfd, msg4, sizeof(msg4));
    write(clientfd, msg5, sizeof(msg5));
    write(clientfd, msg6, sizeof(msg6));

    while (1)
    {
        write(clientfd, msg7, sizeof(msg7));
        bzero(buff, 20);
        read(clientfd, buff, sizeof(buff));
        buff[strcspn(buff, "\r\n")] = 0;
        strcpy(op, buff);
        i = atoi(op);

        if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5)
        {
            break;
        }
        else
        {
            char msg8[] = "Opção inválida\n";
            write(clientfd, msg8, sizeof(msg8));
        }
    }

    switch (i)
    {
    case 1:;
        char msg9[] = "\n*****Caixa de Entrada*****\n";
        write(clientfd, msg9, sizeof(msg9));
        printMessages(clientfd, email_user);

        menu_utilizador(clientfd, email_user);
        break;
    case 2:;
        char idm[20];
        int num;
        char msg10[] = "Indique o id da mensagem que pretende ler:";
        write(clientfd, msg10, sizeof(msg10));
        bzero(buff, 20);
        read(clientfd, buff, sizeof(buff));
        buff[strcspn(buff, "\r\n")] = 0;
        strcpy(idm, buff);
        num = atoi(idm);

        readMessage(clientfd, num);

        menu_utilizador(clientfd, email_user);
        break;
    case 3:;
        char texto[256];
        char buff2[256];
        char users[20];
        char destino[256];
        int j;
        int k;

        char msg11[] = "Escreva a mensagem que pretende enviar\n";
        write(clientfd, msg11, sizeof(msg11));
        bzero(buff2, 256);
        read(clientfd, buff2, sizeof(buff2));
        buff2[strcspn(buff2, "\r\n")] = 0;
        strcpy(texto, buff2);

        char msg12[] = "Para quantos utilizadores prentende enviar essa mensagem? ";
        write(clientfd, msg12, sizeof(msg12));
        bzero(buff, 20);
        read(clientfd, buff, sizeof(buff));
        buff[strcspn(buff, "\r\n")] = 0;
        strcpy(users, buff);
        j = atoi(users);

        char msg13[] = "Indique o email do utilizador: ";

        for (k = 0; k < j; ++k)
        {
            write(clientfd, msg13, sizeof(msg13));
            bzero(buff2, 256);
            read(clientfd, buff2, sizeof(buff2));
            buff2[strcspn(buff2, "\r\n")] = 0;
            strcpy(destino, buff2);

            insereMensagem(email_user, destino, id, texto, false);
            id += 1;
        }
        menu_utilizador(clientfd, email_user);
        break;
    case 4:;

        deleteMessagesRead(email_user);
        printMensagens();

        menu_utilizador(clientfd, email_user);
        break;
    case 5:
        login(clientfd);
        break;

    default:

        break;
    }
}