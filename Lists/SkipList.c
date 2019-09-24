/*
 *     _   __  _                __
 *    / | / / (_)___  _________/ /
 *   /  |/ / / / __ \/ ___/ __  / 
 *  / /|  / / / /_/ / /  / /_/ /  
 * /_/ |_/_/ /\____/_/   \__,_/   
 *      /___/                     
 *
 * Name: SkipList.c
 * Author: L.C.R.
 * Desc.: A skiplist library for Njord's project.
 * URL: https://github.com/LCRERGO/Data_Structures
*/

/*
 * Desc.: Creates a skiplist.
 * I: The (non-negative)max level number.
 * O: A skiplist is created and the nexus is returned.
*/

#include "SkipList.h"

/*
 * Desc.: Creates a skiplist with maximum number of levels.
 * I: The number maximum of levels.
 * O: The nexus of a skiplist.
*/
SkipList *
create_skiplist(unsigned max)
{
    SkipList *nexus;

    nexus = malloc(sizeof(SkipList));

    nexus->max_level = max;
    nexus->num_levels = log(max+1);
    /* TODO:initialize for node variable */

    return nexus;    
}

/*
 * Desc.: Finds a item with a given item in a given level.
 * I: The nexus of the skiplist and the head of the skiplist, 
 * the key of the item to be found and the initial level to be searched for.
 * O: The SkipList node where it was found.
*/
SkipList *
find_sl_wrapper(SkipList *nexus, SkipList *iter, int key, unsigned level)
{
    if (iter != nexus && key == iter->key)
        return iter;
    if (iter->node[level] == NULL || key < iter->node[level]->key) {
        if (!level)
            /* level == 0(not found) */
            return NULL;
        return find_sl_wrapper(nexus, iter, key, level-1);
    }
    return find_sl_wrapper(nexus, iter->node[level], key, level);
}

/*
 * Desc.: A wrapper function for the find function.
 * I: The nexus of the skiplist and a key to be searched for.
 * O: NULL if the element is not found or the element
*/
SkipList *
find_skiplist(SkipList *nexus, int key)
{
    return find_sl_wrapper(nexus, nexus, key, nexus->max_level);
}

/*
 * Desc.: Creates a new skiplist node.
 * I: The nexus of the skiplist a key, it's item, the number of levels
 * it will have.
 * O: The node created.
*/
SkipList *
create_skipnode(SkipList *nexus, int key, int item, unsigned num_levels)
{
    unsigned i;

    SkipList *new_node = malloc(sizeof(SkipList *));
    new_node->key = key;
    new_node->item = item;
    new_node->node = malloc(num_levels * sizeof(SkipList *));
    new_node->num_levels = num_levels;

    for (i = 0; i < num_levels; i++)
        new_node->node[i] = NULL;
    return new_node;
}

/*
 * Desc.: Gets a random level max for a new node.
 * I: None.
 * O: A random level to a node.
*/
unsigned
get_skiplevel(unsigned max)
{
    unsigned level;
    int aleat, accumulator, factor;

    factor = 10;
    accumulator = factor;
    aleat = rand();
    for (level = 0; level < max; level++) {
        if (aleat > RAND_MAX / accumulator)
            break;
        accumulator *= factor;
    }
    
    if (level > max)
        max = level;
    return level;
}

