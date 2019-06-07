#include <stdio.h>
#include <stdlib.h>
#include "kmeans.h"
#include "parser.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

window_t win;
axis_t axis;
plot_t plot;
list_t *points;
point_t *centroids;
int web_flag;
int centroids_size;
const unsigned int square_size = 5;
const unsigned int dot_size = 10;

static void plot_points(int *argc, char *argv[]);
static void draw_squares();
static void draw_lines();
static void draw_dots();
static void display();

int main(int argc, char *argv[])
{
    config_t cfg;
    int status;
    int threshold;
    const char *data_filename;
    const char *cfg_filename = "config.txt";
 
    // Init config structure
    config_init(&cfg);

    // Read config file
    status = read_cfg_file(&cfg, cfg_filename);
    if(!status)
        return EXIT_FAILURE;

    // Init window
    status = set_window_attr(&win, &cfg);
    if(!status) {
    	config_destroy(&cfg);
    	return EXIT_FAILURE;
    }
    	
    // Get number of clusters
    // and name of data file from cfg file
    status = set_cluster_num(&cfg, &centroids_size);
    if(!status) {
        config_destroy(&cfg);
        return EXIT_FAILURE;
    }

    // Get data filename from config file
    status = set_data_filename(&cfg, &data_filename);
    if(!status) {
        config_destroy(&cfg);
        return EXIT_FAILURE;
    }

    // Allocate point array
    points = init_list();
    if(!points) {
        config_destroy(&cfg);
        return EXIT_FAILURE;
    }

    // Store points in array and extract axis values
    status = read_data_file(points, &axis, data_filename);
    if(!status) {
        delete_list(points);
        config_destroy(&cfg);
        return EXIT_FAILURE;
    }

    // Allocate centroids 
    centroids = allocate_points(centroids_size);
    if(!centroids) {
        delete_list(points);
        config_destroy(&cfg);
        return EXIT_FAILURE;
    }

    create_centroids(centroids, centroids_size, &axis);
    set_plot_borders(&plot, &axis);

    status = set_web(&cfg, &web_flag);
    if(!status)
        web_flag = 1;

    status = set_threshold(&cfg, &threshold);
    if(!status)
        threshold = THRESHOLD;

    config_destroy(&cfg);

    while(threshold--) {
        assign_points(points, centroids, centroids_size, &plot);
        update_centroids(points, centroids, centroids_size);
    }
    
    plot_points(&argc, argv);

    return 0;
}

/**
 * @brief  Function to draw centroids as dots
 * @note   
 * @retval None
 */
static void draw_dots()
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_NOTEQUAL, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(dot_size);

    glBegin(GL_POINTS);
        for(int i = 0; i < centroids_size; i++) {
            glColor3f(centroids[i].rgb.red, centroids[i].rgb.green, centroids[i].rgb.blue);
            glVertex2f(centroids[i].x, centroids[i].y);
        } 
    glEnd();

    glDisable(GL_POINT_SMOOTH);
    glBlendFunc(GL_NONE, GL_NONE);
    glDisable(GL_BLEND);
}

/**
 * @brief  Function to draw lines between points and centroids
 * @note   
 * @retval None
 */
static void draw_lines()
{
    node_t *cur;

    glBegin(GL_LINES);
        for(int i = 0; i < centroids_size; i++) {
            glColor3f(centroids[i].rgb.red, centroids[i].rgb.green, centroids[i].rgb.blue); // Paint lines with current cluster's color

            cur = points->head;
            while(cur) {
                if(cur->point.cid == i) {
                    glVertex2f(cur->point.x, cur->point.y);
                    glVertex2f(centroids[i].x, centroids[i].y);
                }
                cur = cur->next;
            }
        }
    glEnd();
}

/**
 * @brief  Function to draw points as squares
 * @note   
 * @retval None
 */
static void draw_squares()
{
    node_t *cur;

    glPointSize(square_size);
    glBegin(GL_POINTS);
        cur = points->head;
		while(cur) {
            glColor3f(cur->point.rgb.red, cur->point.rgb.green, cur->point.rgb.blue); // Set appropriate color
            glVertex2f(cur->point.x, cur->point.y);                                   
            cur = cur->next;
        }
	glEnd();
}

/**
 * @brief  Callback function to output plot
 * @note   
 * @retval None
 */
static void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set white background
	glClear(GL_COLOR_BUFFER_BIT);

    draw_squares();  // Draw points as squares
    draw_dots();     // Draw centroids as dots

    if(web_flag)
        draw_lines(); // Draw "spider-web"

	glFlush();
}

/**
 * @brief  Function to plot points and centroids
 * @note   
 * @param  *argc: Number of main args
 * @param  *argv[]: Main args vector
 * @retval None
 */
static void plot_points(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Select single buffer and rgb bitmask
    glutInitWindowPosition(win.pos_x, win.pos_y);
    glutInitWindowSize(win.width, win.height);
    glutCreateWindow(win.title);
    glMatrixMode(GL_PROJECTION); // Set field of view
	glLoadIdentity();
    gluOrtho2D(plot.minus_x, plot.plus_x, plot.minus_y, plot.plus_y); // Set coordinate system
    glutDisplayFunc(display);
    glutMainLoop();
}