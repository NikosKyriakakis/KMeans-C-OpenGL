#include "point.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief  Function to allocate dynamic array of points
 * @note   
 * @param  size: the size to allocate
 * @retval 
 */
point_t *allocate_points(const unsigned int size)
{
    point_t *points;

    points = malloc(size * sizeof(point_t));
    if(!points) {
        fprintf(stderr, "Allocation of points failed.\n");
        return NULL;
    }

    return points;
}
