#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief  Function to allocate and initialise a list
 * @note   
 * @retval NULL on failure : list pointer on success
 */
extern list_t *init_list()
{
    list_t *list;
    
    list = malloc(sizeof(list_t));
    if(!list) {
        fprintf(stderr, "Allocation of list failed.\n");
        return NULL;
    }
        
    list->head = NULL;
    return list;
}

/**
 * @brief  Function to insert a node to list's head
 * @note   
 * @param  *list: list of points
 * @param  point: the point to be inserted
 * @retval 0 on failure : 1 on success
 */
extern int insert_head(list_t *list, point_t point)
{
    node_t *new_node;

    new_node = malloc(sizeof(node_t));
    if(!new_node) {
        fprintf(stderr, "Allocation of new node failed.\n");
        return 0;
    }
    
    new_node->point = point;
    new_node->next = list->head;
    list->head = new_node;

    return 1;
}

/**
 * @brief  Function to delete head of list
 * @note   
 * @param  *list: list of points
 * @retval 0 on failure : 1 on success
 */
extern int delete_head(list_t *list)
{
    if(!list->head)
        return 0;

    node_t *cur;
    
    cur = list->head;
    list->head = list->head->next;
    free(cur);

    return 1;
}

/**
 * @brief  Function to delete an entire list
 * @note   
 * @param  *list: list of points
 * @retval None
 */
extern void delete_list(list_t *list)
{
    while(delete_head(list));
}