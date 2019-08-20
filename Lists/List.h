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
 * URL: https://github.com/LCRERGO/Data_Structures
*/

#ifndef LIST_H
#define LIST_H
typedef struct list List;

/* The n variable shows the number of elements in the list for the head */
struct list {
    union{
        void *data;
        struct {
            unsigned num;
            List *end;
        };
    };
    List *node;
};

List *create_list();
int destroy_list(List *head);
int insert_list(List *head, void *data, List *element);
void *remove_list(List *head, List *element);
List *concat_list(List *l1, List *l2);
int is_empty(List *head);
#endif
