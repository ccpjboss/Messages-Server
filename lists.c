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

void deleteUser(Lista_t *list, char *email)
{
	Utilizador_t *atual = list->cabeca_u;
	Utilizador_t *anterior = NULL;

	if ((atual != NULL) && (strcmp(email, atual->email) == 0)) //Se a cabeca for diferente de NULL e for o email procurado
	{
		list->cabeca_u = atual->proximo; //A cabeca passa a ser o no a seguir
		free(atual);					 //Apaga o atual
		return;
	}

	while (atual != NULL) //Enquanto a cabeca for diferente de NULL
	{
		if (strcmp(email, atual->email) == 0) //Se a condicao se verificar, sai do while e temos atual == ao no que queremos apagar
			break;

		anterior = atual;		//O anterior vai ser igual ao atual
		atual = atual->proximo; //e o atual vai ser igual ao atual proximo
	}

	if (atual == NULL)
		return; //Se não encontrou nenhum no

	anterior->proximo = atual->proximo;
	free(atual);
	return;
}

bool validLogin(Lista_t *list, char *email, char *pass)
{
	Utilizador_t *atual = list->cabeca_u;

	while (atual != NULL)
	{
		if (strcmp(atual->email, email) == 0)
			break;
		atual = atual->proximo;
	}
	if (atual == NULL) //Se o atual for igual a NULL significa que percorreu a lista toda e não encontrou nenhum email
		return false;

	if (strcmp(atual->password, pass) == 0) //Atual aqui esta igual ao no do email passado
		return true;
	else
		return false;
}

void insereMensagem(Lista_t *list, char *email_r, char *email_d, int id, char *text, bool lida)
{
	Mensagem_t *new = (Mensagem_t *)malloc(sizeof(Mensagem_t));
	Mensagem_t *atual = list->cabeca_m;

	strcpy(new->email_r, email_r);
	strcpy(new->email_d, email_d);
	new->msgid = id;
	strcpy(new->text, text);
	new->lida = false;
	new->proximo = NULL;

	if (list->cabeca_m == NULL)
	{
		list->cabeca_m = new;
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

void readMessage(Lista_t *list, int id) // Read a message from a given message id
{
	Mensagem_t *atual = list->cabeca_m;

	while (atual != NULL)
	{
		if (atual->msgid == id)
			break;
		atual = atual->proximo;
	}

	if (atual == NULL)
		return;

	printf("%s ->\t", atual->email_r);
	printf("%s.\n", atual->text);
	atual->lida = true;
}

void printMessages(Lista_t *list, char *email) //Prints all messages from a user
{
	Mensagem_t *atual = list->cabeca_m;

	while (atual != NULL)
	{
		if ((strcmp(email, atual->email_d) == 0) && (atual->lida == false))
		{
			printf("%d-> ", atual->msgid);
			printf("%s ", atual->email_r);
			printf("\n");
		}
		atual = atual->proximo;
	}

	if (atual == NULL)
		return;
}
void deleteMessagesUser(Lista_t *list, char *email) //Deletes all the messages read from a user
{
	Mensagem_t *atual = list->cabeca_m;
	Mensagem_t *anterior = NULL;

	while ((atual != NULL) && (strcmp(atual->email_d, email) == 0))
	{
		list->cabeca_m = atual->proximo;
		free(atual);
		atual = list->cabeca_m;
	}

	while (atual != NULL)
	{
		while ((atual != NULL) && (strcmp(atual->email_d, email) != 0))
		{
			anterior = atual;
			atual = atual->proximo;
		}

		if (atual == NULL)
			return;

		anterior->proximo = atual->proximo;
		free(atual);

		atual=anterior->proximo;
	}
}

void deleteMessagesRead(Lista_t *list, char *email) //Deletes all messages from a user, read and not read
{
	Mensagem_t *atual = list->cabeca_m;
	Mensagem_t *anterior = NULL;

	while ((atual != NULL) && (strcmp(atual->email_d, email) == 0) && (atual->lida == true))
	{
		list->cabeca_m = atual->proximo;
		free(atual);
		atual = list->cabeca_m;
	}

	while (atual != NULL)
	{
		while ((atual != NULL) && (strcmp(atual->email_d, email) != 0) && (atual->lida == false))
		{
			anterior = atual;
			atual = atual->proximo;
		}

		if (atual == NULL)
			return;

		anterior->proximo = atual->proximo;
		free(atual);

		atual=anterior->proximo;
	}
}