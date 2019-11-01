#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define TOKENS 2
#define DELIMITER ","

/**
 * @brief  Function to split a string in tokens
 * @note   
 * @param  *string: string before splitting it
 * @param  **tokens: parts of string after splitting it
 * @retval None
 */
static void get_string_tokens(char *string, char **tokens)
{
    int count;
    char *token;

    for(count = 0, token = strtok(string, DELIMITER); token && count < TOKENS; count++) {
        tokens[count] = token;
        token = strtok(NULL, DELIMITER);
    }
}

/**
 * @brief  Function to allocate an array of pointers to "strings"
 * @note   
 * @retval NULL on failure : pointer to tokens on success
 */
static char **allocate_tokens()
{
    char **tokens;

    tokens = malloc(TOKENS * sizeof(char *));
    if(!tokens) {
        fprintf(stderr, "Allocation of tokens failed.\n");
        return NULL;
    }

    return tokens;
}

/**
 * @brief  Function to get max of two numbers
 * @note   
 * @param  a: first number
 * @param  b: second number
 * @retval float : max of two params
 */
static float get_max(const float a, const float b)
{
    return a > b ? a : b;
}

/**
 * @brief  Function to get min of two numbers
 * @note   
 * @param  a: first number
 * @param  b: second number
 * @retval float : min of two params
 */
static float get_min(const float a, const float b)
{
    return a < b ? a : b;
}

/**
 * @brief  Function to read parameters passed in the configuration file
 * @note   
 * @param  *cfg: config structure to store parameters
 * @param  *filename: path and name of file on disk
 * @retval CONFIG_TRUE on success : CONFIG_FALSE on failure
 */
int read_cfg_file(config_t *cfg, const char *filename)
{
    int cfg_status;
    int cfg_err_line;

    const char *cfg_err_file;
    const char *cfg_err_txt;

    // Store configuration in cfg
    cfg_status = config_read_file(cfg, filename);

    if(!cfg_status) {
        // Get error values
        cfg_err_file = config_error_file(cfg);
        cfg_err_line = config_error_line(cfg);
        cfg_err_txt = config_error_text(cfg);

        // Print error message to stderr and destroy configuration structure
        fprintf(stderr, "%s:%d - %s\n", cfg_err_file, cfg_err_line, cfg_err_txt);
        config_destroy(cfg);

        // Failure code: 0
        return CONFIG_FALSE;
    }

    // Success code: 1
    return CONFIG_TRUE;
}

/**
 * @brief  Function to allocate a window structure and initialise it
 * @note   
 * @param  *cfg: config structure for project's params
 * @retval NULL on failure : pointer to window_t struct on success 
 */
int set_window_attr(window_t *win, const config_t *cfg)
{
    int status;
        
    // Fetch window width
    status = config_lookup_int(cfg, "width", &(win->width));
    if(!status) {
        fprintf(stderr, "Unable to acquire <width> parameter.\n");
        return 0;
    }
       
    // Fetch window height
    status = config_lookup_int(cfg, "height", &(win->height));
    if(!status) {
        fprintf(stderr, "Unable to acquire <height> parameter.\n");
        return 0;
    }

    // Fetch window 'x' position
    status = config_lookup_int(cfg, "pos_x", &(win->pos_x));
    if(!status) {
        fprintf(stderr, "Unable to acquire <pos_x> parameter.\n");
        return 0;
    }

    // Fetch window 'y' position
    status = config_lookup_int(cfg, "pos_y", &(win->pos_y));
    if(!status) {
        fprintf(stderr, "Unable to acquire <pos_y> parameter.\n");
        return 0;
    }

    // Fetch window title
    status = config_lookup_string(cfg, "title", &(win->title));
    if(!status) {
        fprintf(stderr, "Unable to acquire <title> parameter.\n");
        return 0;
    }

    if(strlen(win->title) > TITLE)
        win->title = "K-Means";

    return 1;
}

/**
 * @brief  Function to set the number of centroids to produce
 * @note   
 * @param  *cfg: config structure to store parameters
 * @param  *clusters: number of clusters
 * @retval CONFIG_TRUE on success : CONFIG_FALSE on failure
 */
int set_cluster_num(const config_t *cfg, int *clusters)
{
    int status;

    status = config_lookup_int(cfg, "clusters", clusters);
    if(!status) {
        fprintf(stderr, "Unable to acquire <clusters>.\n");
        return CONFIG_FALSE;
    }

    if(*clusters <= 0 || *clusters > MAX_CLUSTERS)
        *clusters = MAX_CLUSTERS;

    return CONFIG_TRUE;
}

/**
 * @brief  Function to set the path and filename of the file containing the points
 * @note   
 * @param  *cfg: config structure to store parameters
 * @param  **filename: name and path of the file
 * @retval CONFIG_TRUE on success : CONFIG_FALSE on failure
 */
int set_data_filename(const config_t *cfg, const char **filename)
{
    int status;

    status = config_lookup_string(cfg, "filename", filename);
    if(!status) {
        fprintf(stderr, "Unable to acquire <filename>.\n");
        return CONFIG_FALSE;
    }

    return CONFIG_TRUE;
}

/**
 * @brief  Searches for <threshold> value in the config file
 * @note   
 * @param  *cfg: config structure to store parameters
 * @param  *threshold: bound for the kmeans algorithm
 * @retval CONFIG_TRUE on success : CONFIG_FALSE on failure
 */
int set_threshold(const config_t *cfg, int *threshold)
{
    int status;

    status = config_lookup_int(cfg, "threshold", threshold);
    if(!status) {
        fprintf(stderr, "Unable to acquire <threshold>.\n");
        return CONFIG_FALSE;
    }
    
    if(*threshold <= 0)
        *threshold = THRESHOLD;

    return CONFIG_TRUE;
}

/**
 * @brief  Function to set "spider-web" flag on or off
 * @note   Essentialy if web_flag == 1 lines will be drawn between each point with it's centroid
 * @param  *cfg:  config structure to store parameters
 * @param  *web_flag: 
 * @retval 
 */
int set_web(const config_t *cfg, int *web_flag)
{
    int status;

    status = config_lookup_int(cfg, "web_flag", web_flag);
    if(!status) {
        fprintf(stderr, "Unable to acquire <web_flag>.\n");
        return CONFIG_FALSE;
    }

    if(*web_flag != 0 && *web_flag != 1)
        *web_flag = 1;

    return CONFIG_TRUE;
}

/**
 * @brief  Function to overwrite previous contents of a line with '\0'
 * @note   
 * @param  *line: contains a whole line before it gets split
 * @retval None
 */
static void clean(char *line)
{
    memset(line, '\0', strlen(line));
}

/**
 * @brief  Function read contents of file in a list of points
 * @note   
 * @param  *point_list: List of all points
 * @param  *axis: contains max and min point values
 * @param  *filename: path and name of data file
 * @retval 
 */
int read_data_file(list_t *point_list, axis_t *axis, const char *filename)
{
    FILE *file_ptr;

    file_ptr = fopen(filename, "r");
    if(!file_ptr) {
        fprintf(stderr, "Error in data file.\n");
        return 0;
    }

    int line_count;
    char line[LINE_SIZE];
    char **tokens;
    point_t p;
    unsigned char r, g, b;

    // Allocate array of char pointers
    tokens = allocate_tokens();
    if(!tokens) 
        return 0;

    // Fill line with 
    // the '\0' character
    clean(line);

    for(line_count = 0; fgets(line, LINE_SIZE, file_ptr); line_count++) {
        // Split string by ","
        get_string_tokens(line, tokens);

        // Init point
        p.cid = RED;
        p.x = strtof(tokens[0], NULL);
        p.y = strtof(tokens[1], NULL);

        // Assign it an initial color
        set_color(p.cid, &r, &g, &b);
        p.rgb.red = r;
        p.rgb.green = g;
        p.rgb.blue = b;
        
        // Add point to list
        insert_head(point_list, p);
        
        // Get maximum and minimum axis values
        if(line_count == 0) {
            axis->max_x = axis->min_x = p.x;
            axis->max_y = axis->min_y = p.y;
        } else {
            axis->max_x = get_max(p.x, axis->max_x);
            axis->max_y = get_max(p.y, axis->max_y);
            axis->min_x = get_min(p.x, axis->min_x);
            axis->min_y = get_min(p.y, axis->min_y);
        }

        clean(line);
    }

    free(tokens);
    fclose(file_ptr);

    return 1;
}
