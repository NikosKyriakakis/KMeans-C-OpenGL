#ifndef PARSER_H
#define PARSER_H

#include <libconfig.h>
#include "window.h"
#include "list.h"

#define THRESHOLD 5
#define LINE_SIZE 64
#define TITLE 15
#define MAX_CLUSTERS 5

static void get_string_tokens(char *string, char **tokens);
static char **allocate_tokens();
static float get_max(const float a, const float b);
static float get_min(const float a, const float b);
extern int read_cfg_file(config_t *cfg, const char *filename);
extern int set_cluster_num(const config_t *cfg, int *clusters);
extern int read_data_file(list_t *point_list, axis_t *axis, const char *filename);
extern int set_data_filename(const config_t *cfg, const char **filename);
extern int set_threshold(const config_t *cfg, int *threshold);
extern int set_web(const config_t *cfg, int *web_flag);
extern int set_window_attr(window_t *win, const config_t *cfg);

#endif