#ifndef PARSER_H
#define PARSER_H

#include <libconfig.h>
#include "window.h"
#include "list.h"

#define THRESHOLD 5
#define LINE_SIZE 64
#define TITLE 15
#define MAX_CLUSTERS 5

extern int read_cfg_file(config_t *cfg, const char *filename);
extern int set_cluster_num(config_t *cfg, int *clusters);
extern int read_data_file(list_t *point_list, axis_t *axis, const char *filename);
extern int set_data_filename(config_t *cfg, const char **filename);
extern int set_threshold(config_t *cfg, int *threshold);
extern int set_web(config_t *cfg, int *web_flag);
extern window_t *set_window_attr(config_t *cfg);

#endif