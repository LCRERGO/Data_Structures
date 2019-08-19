/*
 *     _   __  _                __
 *    / | / / (_)___  _________/ /
 *   /  |/ / / / __ \/ ___/ __  / 
 *  / /|  / / / /_/ / /  / /_/ /  
 * /_/ |_/_/ /\____/_/   \__,_/   
 *      /___/                     
 *
 * Name: List.h
 * Author: L.C.R.
 * Desc.: A list header for Njord's project.
*/

#ifndef LIST_H
#define LIST_H
typedef struct list List;

struct list {
    void *data;
    List *node;
};

List *create_list();
void destroy_list(List *head);
int insert_list(List *head, void *data);
int remove_list(List *head, void *data);
#endif
