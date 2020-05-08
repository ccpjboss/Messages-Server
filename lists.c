#include "lists.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h> 


void inicia_lista(Lista_t *list)
{
	list->cabeca_m = NULL;
	list->cabeca_u = NULL;
}

void printUtilizadors(Utilizador_t *node)
{
	Utilizador_t *atual = node;
	while (atual != NULL)
	{
		printf("%s  %s \n", atual->email, atual->password);
		atual = atual->proximo;
	}
}

bool verificaUser(Lista_t *list, char *email)
{
	bool dup = false;
	Utilizador_t *atual = list->cabeca_u;
	while (atual != NULL)
	{
		if (strcmp(email, atual->email) == 0)
			dup = true;
		atual = atual->proximo;
	}
	return dup;
}

void insereUser(int socket_fd, Lista_t *list)
{
	Utilizador_t *new = (Utilizador_t *)malloc(sizeof(Utilizador_t));
	Utilizador_t *atual = list->cabeca_u;

	char msg_send1[] = "Insira o email: ";
	char msg_send2[] = "Insira a palavra passe: ";
	char buff[256];
	char buff2[20];

	do
	{
		write(socket_fd, msg_send1, sizeof(msg_send1)); //Envia mensagem de input para o cliente
		bzero(buff, 256);								//Coloca o buffer a 0
		read(socket_fd, buff, sizeof(buff));			//Le o input do cliente
		buff[strcspn(buff, "\r\n")] = 0;
		strcpy(new->email, buff); //Copia para a variavel da struct
	} while (verificaUser(list, new->email));

	write(socket_fd, msg_send2, sizeof(msg_send2));
	bzero(buff2, 20);
	read(socket_fd, buff2, sizeof(buff2));
	buff2[strcspn(buff2, "\r\n")] = 0;
	strcpy(new->password, buff2);

	new->admin = false;
	new->codigo_user = 1; //TODO: Think about user code
	new->proximo = NULL;

	if (list->cabeca_u == NULL) //Se a cabeça for igual a NULL então new vai ser o primeiro nó
	{
		list->cabeca_u = new;
		return;
	}
	else
	{
		while (atual->proximo != NULL)
		{
			atual = atual->proximo;
		}
		atual->proximo = new;
		return;
	}
}

bool validLogin(Lista_t *list, char *email, char *pass)
{
	Utilizador_t *atual = list->cabeca_u;

	while (strcmp(atual->email,email) != 0 || atual->proximo != NULL)
		atual=atual->proximo;

	if (atual == NULL) //Se o atual for igual a NULL significa que percorreu a lista toda e não encontrou nenhum email
		return false;

	if (strcmp(atual->password, pass) == 0) //Atual aqui esta igual ao no do email passado
		return true;
	else
		return false;
}