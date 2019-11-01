#include "window.h"

/**
 * @brief  Function to set plotting window borders
 * @note   
 * @retval None
 */
void set_plot_borders(plot_t *plot, const axis_t *axis)
{
    plot->minus_x = axis->min_x - AXIS_THRESHOLD;
    plot->minus_y = axis->min_y - AXIS_THRESHOLD;
    plot->plus_x  = axis->max_x + AXIS_THRESHOLD;
    plot->plus_y  = axis->max_y + AXIS_THRESHOLD;
}
