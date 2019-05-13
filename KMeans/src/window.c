#include "window.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief  Function to allocate plot
 * @note   
 * @retval NULL on failure : plot_t pointer on success
 */
extern plot_t *allocate_plot()
{
    plot_t *plot;

    plot = malloc(sizeof(plot_t));
    if(!plot) {
        fprintf(stderr, "Allocation of plot failed.\n");
        return NULL;
    }

    return plot;
}

/**
 * @brief  Function to allocate axis
 * @note   
 * @retval NULL on failure : axis_t pointer on success
 */
extern axis_t *allocate_axis()
{
    axis_t *axis;

    axis = malloc(sizeof(axis_t));
    if(!axis) {
        fprintf(stderr, "Allocation of axis failed.\n");
        return NULL;
    }
    
    return axis;
}

/**
 * @brief  Function to set plotting window borders
 * @note   
 * @retval None
 */
extern void set_plot_borders(plot_t *plot, axis_t *axis)
{
    plot->minus_x = axis->min_x - AXIS_THRESHOLD;
    plot->minus_y = axis->min_y - AXIS_THRESHOLD;
    plot->plus_x  = axis->max_x + AXIS_THRESHOLD;
    plot->plus_y  = axis->max_y + AXIS_THRESHOLD;
}