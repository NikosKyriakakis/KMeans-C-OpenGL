#ifndef UTILS_H
#define UTILS_H

#define TOKENS 2
#define DELIMITER ","

void get_string_tokens(char *string, char **tokens);
char **allocate_tokens();
float get_max(const float a, const float b);
float get_min(const float a, const float b);

#endif