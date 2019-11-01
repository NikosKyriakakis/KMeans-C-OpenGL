#include "kmeans.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * @brief  Function to generate random centroids 
 * @note   
 * @param  *centroids: dynamic array of points that represent <centers>
 * @param  centroids_size: size of centroids
 * @param  *axis: struct that stores (max, min) point values
 * @retval None
 */
void create_centroids(point_t *centroids, const unsigned int centroids_size, const axis_t *axis)
{
    int x, y, tmp, coin;
    unsigned char r, g, b;

    srand(time(NULL));

    for(int i = 0; i < centroids_size; i++) {
        coin = rand() % RAND_MAX;
        if(coin % 2 == 0) { 
            tmp = (int)(axis->max_x);
            if(tmp == 0) // To avoid % with zero value
                tmp++;
            x = rand() % tmp;
        } else {   
            if(axis->min_x < 0)
                tmp = (int)(-(axis->min_x)); // Alternates sign if negative
            else
                tmp = (int)axis->min_x;

            if(tmp == 0)
                tmp++;

            x = rand() % tmp;
            x = -x;
        }
        
        coin = rand() % RAND_MAX;
        if(coin % 2 == 0) {
            tmp = (int)axis->max_y;
            if(tmp == 0)
                tmp++;
            y = rand() % tmp;
        } else {
            if(axis->min_y < 0)
                tmp = (int)(-(axis->min_y));
            else
                tmp = (int)axis->min_y;

            if(tmp == 0)
                tmp++;

            y = rand() % tmp;
            y = -y;
        }

        // Set centroid attributes
        centroids[i].x = x;
        centroids[i].y = y;
        centroids[i].cid = i;

        // Set centroid color
        set_color(centroids[i].cid, &r, &g, &b);
        centroids[i].rgb.red = r;
        centroids[i].rgb.green = g;
        centroids[i].rgb.blue = b;
    }
}

/**
 * @brief  Function to calculate euclidean distance between two points
 * @note   
 * @param  p1: first point
 * @param  p2: second point
 * @retval float: Distance between given points
 */
static float euclidean_distance(const point_t p1, const point_t p2)
{
    float distance;
    float x, y;

    x = p2.x - p1.x;
    y = p2.y - p1.y;

    distance = sqrt(pow(x, 2) + pow(y, 2));

    return distance;
}

/**
 * @brief  Function to assign points to centroids 
 * @note   
 * @param  *point_list: list of all points
 * @param  *centroids: dynamic array of centroids
 * @param  centroids_size: size of centroids
 * @param  *plot: struct with max and min coordinates
 * @retval None
 */
void assign_points(list_t *point_list, const point_t *centroids, const unsigned int centroids_size, const plot_t *plot)
{
    float distance, min_distance;
    point_t p1, p2;
    unsigned int id;
    unsigned char r, g, b;
    node_t *cur;

    p1.x = plot->minus_x;
    p1.y = plot->minus_y;
    p2.x = plot->plus_x;
    p2.y = plot->plus_y;

    cur = point_list->head;
    while(cur) {
        min_distance = euclidean_distance(p1, p2); // Maximum distance on program's window

        for(int j = 0; j < centroids_size; j++) {
            distance = euclidean_distance(cur->point, centroids[j]);

            if(distance < min_distance) {
                min_distance = distance;
                id = j;
            }
        }

        set_color(id, &r, &g, &b);
        cur->point.cid = id;
        cur->point.rgb.red = r;
        cur->point.rgb.green = g;
        cur->point.rgb.blue = b;
        cur = cur->next;
    }
}

/**
 * @brief  Function to update centroids according to their assigned points
 * @note   
 * @param  *point_list: list of all points
 * @param  *centroids: dynamic array of centroids
 * @param  centroids_size: size of centroids
 * @retval None
 */
void update_centroids(const list_t *point_list, point_t *centroids, const unsigned int centroids_size)
{
    float mean_x, mean_y;
    unsigned int count;
    node_t *cur;

    for(int i = 0; i < centroids_size; i++) {
        count = mean_x = mean_y = 0;
        cur = point_list->head;

        while(cur) {
            if(cur->point.cid == i) {
               mean_x += cur->point.x;
               mean_y += cur->point.y;
               count++;
            }
            cur = cur->next;
        }

        if(count) { // avoids division with zero
            mean_x /= count;
            mean_y /= count;
            centroids[i].x = mean_x;
            centroids[i].y = mean_y;
        }
    }
}
