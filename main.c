#include "lists.h"
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    Lista_t *Lista = (Lista_t *) malloc(sizeof(Lista_t));
    inicia_lista(Lista);
    insereUser(Lista);
    insereUser(Lista);
    printUtilizadors(Lista->cabeca_u);
    return 0;
}
