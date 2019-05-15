#ifndef COLOR_H
#define COLOR_H

#define ROWS 10
#define COLS 3
#define RED 0
#define GREEN 1
#define BLUE 2

typedef struct color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color_t;

extern void set_color(const unsigned int index, unsigned char *red, unsigned char *green, unsigned char *blue);

#endif