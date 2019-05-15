#ifndef KMEANS_H
#define KMEANS_H

#include "window.h"
#include "list.h"

extern void create_centroids(point_t *centroids, const unsigned int centroids_size, const axis_t *axis);
extern void assign_points(list_t *point_list, const point_t *centroids, const unsigned int centroids_size, const plot_t *plot);
extern void update_centroids(const list_t *point_list, point_t *centroids, const unsigned int centroids_size);

#endif