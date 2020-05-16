#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>

typedef struct Utilizador
{
    char email[256];
    char password[20];
    bool admin;
    struct Utilizador *proximo;
} Utilizador_t;

struct Date
{
    int dia;
    int mes;
    int ano;
};

typedef struct Mensagem
{
    struct Date data;
    char email_r[256]; //codigo_user remetente
    char email_d[256]; //codigo_user destinatario
    int msgid;         //ID da mensagem
    char text[256];
    bool lida;
    struct Mensagem *proximo;
} Mensagem_t;

typedef struct Lista
{
    struct Mensagem *cabeca_m;
    struct Utilizador *cabeca_u;
} Lista_t;

void inicia_lista(Lista_t *const list);
void printUtilizadors();
void printMensagens();
void insereUser(int socket_fd);
bool verificaUser(char *email);
bool validLogin(char *email, char *pass);
void deleteUser(char *email);
void insereMensagem(char *email_r, char *email_d, int id, char *text, bool lida);
void readMessage(int socket_fd, int id, char *email);        // Read a message from a given message id
void printMessages(int socket_fd, char *email); //Prints all messages from a user
void deleteMessagesRead(char *email);           //Deletes all the messages read from a user
void deleteMessagesUser(char *email);           //Deletes all messages from a user, read and not read
void guardaMensagensFile(Lista_t *list);
void leMessagesFile(Lista_t *list);
void guardaUsersFile(Lista_t *list);
void leUserFile(Lista_t *list);

#endif
