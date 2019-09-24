/*
 *     _   __  _                __
 *    / | / / (_)___  _________/ /
 *   /  |/ / / / __ \/ ___/ __  / 
 *  / /|  / / / /_/ / /  / /_/ /  
 * /_/ |_/_/ /\____/_/   \__,_/   
 *      /___/                     
 *
 * Name: SkipList.h
 * Author: L.C.R.
 * Desc.: A skiplist header for Njord's project.
 * URL: https://github.com/LCRERGO/Data_Structures
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SKIPLIST_H
#define SKIPLIST_H
typedef struct skiplist SkipList;

struct skiplist{
    struct {
        int key;
        int item;
    };
    unsigned num_levels;
    unsigned max_level;
    SkipList **node;
};

SkipList *create_skiplist(unsigned max);
SkipList *find_sl_wrapper(SkipList *nexus, SkipList *iter, 
        int key, unsigned level);
SkipList *find_skiplist(SkipList *nexus, int key);
SkipList *create_skipnode(SkipList *nexus, int key, int item, 
        unsigned num_levels);

unsigned get_skiplevel(unsigned max);
#endif
