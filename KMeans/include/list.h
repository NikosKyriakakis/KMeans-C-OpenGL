#ifndef LIST_H
#define LIST_H

#include "point.h"

typedef struct node {
    point_t point;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
} list_t;

extern list_t *init_list();
extern int delete_head(list_t *list);
extern int insert_head(list_t *list, point_t point);
extern void delete_list(list_t *list);

#endif