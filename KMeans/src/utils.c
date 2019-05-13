#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief  Function to split a string in tokens
 * @note   
 * @param  *string: string before splitting it
 * @param  **tokens: parts of string after splitting it
 * @retval None
 */
extern void get_string_tokens(char *string, char **tokens)
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
extern char **allocate_tokens()
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
extern float get_max(const float a, const float b)
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
extern float get_min(const float a, const float b)
{
    return a < b ? a : b;
}