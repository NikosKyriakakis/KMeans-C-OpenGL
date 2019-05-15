#ifndef POINT_H
#define POINT_H

#include "color.h"

typedef struct point {
    float x;
    float y;
    int cid;     // Cluster id
    color_t rgb; // Color of each point
} point_t;

extern point_t *allocate_points(const unsigned int size);

#endif