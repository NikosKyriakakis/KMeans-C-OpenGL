#ifndef WINDOW_H
#define WINDOW_H

#define AXIS_THRESHOLD 10

typedef struct window {
    int width;
    int height;
    int pos_x;
    int pos_y;
    const char *title;
} window_t;

typedef struct axis {
    int max_x;
    int max_y;
    int min_x;
    int min_y;
} axis_t;

typedef struct plot {
    int plus_x;
    int plus_y;
    int minus_x;
    int minus_y;
} plot_t;

extern plot_t *allocate_plot();
extern axis_t *allocate_axis();
extern void set_plot_borders(plot_t *plot, axis_t *axis);

#endif