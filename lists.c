#include "lists.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

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

void printMensagens(Mensagem_t *node)
{
	Mensagem_t *atual = node;
	while (atual != NULL)
	{
		printf("%d %s %s\n", atual->msgid, atual->email_d, atual->text);
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

void readMessage(int socket_fd, Lista_t *list, int id) // Read a message from a given message id
{
	Mensagem_t *atual = list->cabeca_m;
	char buff[256];
	bzero(buff, 256);

	while (atual != NULL)
	{
		if (atual->msgid == id)
			break;
		atual = atual->proximo;
	}

	if (atual == NULL)
		return;
	strcpy(buff, atual->text);
	write(socket_fd, buff, sizeof(buff));
	atual->lida = true;
}

void printMessages(int socket_fd, Lista_t *list, char *email) //Prints all messages from a user
{
	Mensagem_t *atual = list->cabeca_m;
	char msg_to_send[281];
	bzero(msg_to_send, 281); //Resets the buffer

	while (atual != NULL)
	{
		if ((strcmp(email, atual->email_d) == 0) && (atual->lida == false))
		{
			sprintf(msg_to_send, "id:%d  email remetente:%s\n", atual->msgid, atual->email_r);
			write(socket_fd, msg_to_send, sizeof(msg_to_send));
		}
		atual = atual->proximo;
	}

	if (atual == NULL)
		return;
}

void deleteMessagesUser(Lista_t *list, char *email) //Deletes all the messages from a user
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

		atual = anterior->proximo;
	}
}

void deleteMessagesRead(Lista_t *list, char *email) //Deletes all messages from a user, read
{
	Mensagem_t *atual = list->cabeca_m;
	Mensagem_t *anterior = NULL;

	if (list->cabeca_m == NULL)
		return;

	while ((list->cabeca_m != NULL) && (strcmp(list->cabeca_m->email_d, email) == 0) && (list->cabeca_m->lida == true))
	{
		anterior = list->cabeca_m;
		list->cabeca_m = list->cabeca_m->proximo;
		free(anterior);
	}

	atual = list->cabeca_m;
	anterior = NULL;

	while (atual != NULL)
	{
		while ((atual != NULL) && (atual->lida == false))
		{

			anterior = atual;
			atual = atual->proximo;
		}

		if (atual == NULL)
			return;

		if (strcmp(atual->email_d, email) == 0)
		{
			anterior->proximo = atual->proximo;
			free(atual);
			atual = anterior->proximo;
		}
		anterior = atual;
		atual = atual->proximo;
	}
}

void leMessagesFile(Lista_t *list)
{
	Mensagem_t *atual = list->cabeca_m;
	/* Opens the file for reading in binary mode */
	FILE *infile;
	infile = fopen("mensagens.bin", "rb");

	if (infile == NULL) // Checks for error
	{
		perror("fopen mensgens.bin");
		exit(1);
	}

	/* Checks for empty file */
	fseek(infile, 0, SEEK_END);
	int size = ftell(infile);

	if (0 == size)
	{
		printf("File is empty\n");
		return;
	}
	rewind(infile);

	while (1)
	{
		/* READ */
		Mensagem_t *new = (Mensagem_t *)malloc(sizeof(Mensagem_t));
		int check = fread(new, sizeof(Mensagem_t), 1, infile);

		/* CHECK */
		if (check != sizeof(Mensagem_t))
			break;

		/* USE */
		if (list->cabeca_m == NULL)
		{
			list->cabeca_m = new;
			new->proximo = NULL;
			atual = list->cabeca_m;
		}
		else
		{
			atual->proximo = new;
			new->proximo = NULL;
			atual = atual->proximo;
		}
		free(new);
	}
	fclose(infile);
	return;
}

void leUserFile(Lista_t *list)
{
	Utilizador_t *atual = list->cabeca_u;
	FILE *infile;
	infile = fopen("utilizador.bin", "rb");

	if (infile == NULL)
	{
		perror("fopen utilizador.bin");
		exit(1);
	}

	fseek(infile, 0, SEEK_END);
	int size = ftell(infile);

	if (0 == size)
	{
		printf("File is empty\n");
		return;
	}
	rewind(infile);

	while (1)
	{
		/* READ */
		Utilizador_t *new = (Utilizador_t *)malloc(sizeof(Utilizador_t));
		int check = fread(new, sizeof(Utilizador_t), 1, infile);

		/* CHECK */
		if (check != sizeof(Utilizador_t))
			break;

		/* USE */
		if (list->cabeca_u == NULL)
		{
			list->cabeca_u = new;
			new->proximo = NULL;
			atual = list->cabeca_u;
		}
		else
		{
			atual->proximo = new;
			new->proximo = NULL;
			atual = atual->proximo;
		}
		free(new);
	}

	fclose(infile);
	return;
}

void guardaMensagensFile(Lista_t *list)
{
	Mensagem_t *atual = list->cabeca_m;
	FILE *outfile;
	outfile = fopen("mensagens.bin", "wb");

	if (outfile == NULL)
	{
		perror("fopen mensgens.bin");
		exit(1);
	}

	if (list->cabeca_m == NULL)
	{
		printf("Nothing to write to file...");
		return;
	}

	while (atual != NULL)
	{
		fwrite(atual, sizeof(Mensagem_t), 1, outfile);
		atual = atual->proximo;
	}

	fclose(outfile);
	return;
}

void guardaUsersFile(Lista_t *list)
{
	Utilizador_t *atual = list->cabeca_u;
	FILE *outfile;
	outfile = fopen("utiizador.bin", "wb");

	if (outfile == NULL)
	{
		perror("fopen utiizador.bin");
		exit(1);
	}

	if (list->cabeca_u == NULL)
	{
		printf("Nothing to write to file...");
		return;
	}

	while (atual != NULL)
	{
		fwrite(atual, sizeof(Utilizador_t), 1, outfile);
		atual = atual->proximo;
	}

	fclose(outfile);
	return;
}