/*
 *     _   __  _                __
 *    / | / / (_)___  _________/ /
 *   /  |/ / / / __ \/ ___/ __  / 
 *  / /|  / / / /_/ / /  / /_/ /  
 * /_/ |_/_/ /\____/_/   \__,_/   
 *      /___/                     
 *
 * Name: List.c
 * Author: L.C.R.
 * Desc.: A list library for Njord's project.
*/
#include <stdio.h>
#include <stdlib.h>

#include "List.h"

/*
 * Desc.: Creates the head of the list.
 * I: NULL
 * O: A pointer to the list head, or NULL in case it fails.
*/
List *
create_list()
{
    List *head;

    head = malloc(sizeof(List));
    if (head == NULL)
        return NULL;
    head->data = NULL;
    head->node = NULL;

    return head;
}

/*
 * Desc.: Destroy the List.
 * I: The head of the List.
 * O: void.
*/
void
destroy_list(List *head)
{
    List *iter, *aux;

    iter = malloc(sizeof(List));
    aux = malloc(sizeof(List));
    iter = head->node;
    while (iter != NULL) {
        aux = iter;
        iter = iter->node;
        free(aux);
        aux = NULL;
    }
    free(head);
    head = NULL;
}

/*
 * Desc.: Inserts an element at the begging of the List.
 * I: The head of the List and the data.
 * O: 1 in case of success, 0 otherwise.
*/
int
insert_list(List *head, void *data)
{
    List *new_node;

    new_node = malloc(sizeof(List));
    if (new_node == NULL)
        return 0;

    new_node->data = data;
    new_node->node = head->node;
    head->node = new_node;

    return 1;
}

/*
 * Desc.: Removes the element with the indicated data from the List.
 * I: The head of the List and the data to be removed.
 * O: 1 in case of success, 0 otherwise
*/
int
remove_list(List *head, void *data)
{
   List *iter, *aux;

   iter = malloc(sizeof(List));
   aux = malloc(sizeof(List));
   iter = head->node;
   while (iter->node->data != data && iter != NULL) {
       iter = iter->node;
   }
   if (iter == NULL)
       return 0;

   aux = iter->node;
   iter->node = aux->node;
   free(aux);
   aux = NULL;

   return 1;
}
