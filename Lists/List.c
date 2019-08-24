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
 * URL: https://github.com/LCRERGO/Data_Structures
*/

#include "List.h"

/*
 * Desc.: Creates the head of the list.
 * I: void
 * O: A pointer to the list head, or NULL in case it fails.
*/
List *
create_list()
{
    List *head;

    head = malloc(sizeof(List));
    if (head == NULL)
        return NULL;
    head->num = 0;
    head->end = NULL;
    head->node = NULL;

    return head;
}

/*
 * Desc.: Destroy the List.
 * I: The head of the List.
 * O: 1 if the list has been destroied, 0 otherwise.
*/
int
destroy_list(List *head)
{
    List *iter, *aux;

    iter = head->node;
    while (iter != NULL) {
        aux = iter;
        iter = iter->node;
        free(aux);
        aux = NULL;
        (head->num)--;
    }
    free(head);
    head = NULL;
    if (head != NULL)
        return 0;

    return 1;
}

/*
 * Desc.: Inserts an element after the specified element, if element 
 * is NULL or not found insert at the end of the list, if it's 
 * the head then insert at the beginning.
 * I: The head of the List, the data to be inserted and the data 
 * of the elementwhere to insert.
 * O: 1 in case of success, 0 otherwise.
*/
int
insert_list(List *head, void *data, List *element)
{
    List *iter, *aux, *head_aux;

    if (element == NULL) {
        /* to insert at the end */
        head_aux = create_list();
        insert_list(head_aux, data, head_aux);
        concat_list(head, head_aux);
        return 1;
    }

    aux = malloc(sizeof(List));
    aux->data = data;
    iter = head->node;
    if (aux == NULL){
        return 0;
    }


    if (element == head) {
        /* inserts at beginning */
        if (is_empty(head))
            head->end = aux;
        aux->node = head->node;
        head->node = aux;
        (head->num)++;
        

        return 1;
    }
    while (iter->node != NULL && iter->node != element) {
        iter = iter->node;
    }
    if (iter->node == NULL){
        /* element not found, inserts at the end */
        aux->node = NULL;
        iter->node = aux;
        (head->num)++;

        return 1;
    }
    /* iter->node != NULL && iter->node->data == element */
    /* inserts at the required element */
    aux->node = iter->node->node;
    iter->node->node = aux;
    (head->num)++;

    return 1;
}

/*
 * Desc.: Removes the element with the indicated data from the List.
 * I: The head of the List and the list pointer to be removed, 
 * if element is the head removes first element.
 * O: The data of the element removed, if the list is not found
 * return NULL.
*/
void *
remove_list(List *head, List *element)
{
   List *iter, *aux;
   void *data;

   if(element == head || element == head->node){
       /* in case it's the head */
       aux = head->node;
       head->node = head->node->node;
       data = aux->data;
       free(aux);
       (head->num)--;

       return data;
    }

   iter = head;
   while (iter->node != NULL && iter->node != element) {
       iter = iter->node;
   }
   if (iter->node == NULL)
       return NULL;

   /* iter->node == element */
   if (iter->node->node == NULL)
       /* in case it's the last */
       head->end = iter;
   data = iter->node->data;
   aux = iter->node;
   iter->node = aux->node;
   free(aux);
   aux = NULL;
   (head->num)--;

   return data;
}

/*
 * Desc.: Copies a list to a pointer.
 * I: A list and a pointer to a list.
 * O: 1 in case of success, 0 otherwise.
*/
int
cpy_list(List *l1, List **l2)
{
    List *iter;
    void *data_aux;

    *l2 = create_list();
    iter = l1->node;
    while (iter != NULL) {
        data_aux = malloc(sizeof(iter->data));
        memcpy(data_aux, iter->data, sizeof(iter->data));
        insert_list(*l2, data_aux, NULL);
        iter = iter->node;
    }

    return 1;
}

/*
 * Desc.: Concatenates two lists
 * I: Two lists.
 * O: A list concatenated.
*/
List *
concat_list(List *l1, List *l2)
{
    if (l1->node == NULL){
        /* in case l1 is empty */
        l1->node = l2->node;
        l1->end = l2->end;
        l1->num = l1->num + l2->num;
        free(l2);

        return l1;
    }
    l1->end->node = l2->node;
    l1->end = l2->end;
    l1->num = l1->num + l2->num;    
    free(l2);
    
    return l1;
}

/*
 * Desc.: Tests if the list is empty or not.
 * I: The head of the list.
 * O: 1 in case it is empty, 0 otherwise.
*/
int
is_empty(List *head)
{
    if (!head->num)
        return 1;
    return 0;
}
