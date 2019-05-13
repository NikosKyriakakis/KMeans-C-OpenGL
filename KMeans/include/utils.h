#ifndef UTILS_H
#define UTILS_H

#define TOKENS 2
#define DELIMITER ","

extern char **allocate_tokens();
extern void get_string_tokens(char *string, char **tokens);
extern float get_max(const float a, const float b);
extern float get_min(const float a, const float b);

#endif