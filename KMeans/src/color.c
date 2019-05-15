#include "color.h"

extern void set_color(const unsigned int index, unsigned char *red, unsigned char *green, unsigned char *blue)
{
    unsigned char pallete[ROWS][COLS] = {
        { 255, 0, 0 },
        { 0, 255, 0 },
        { 0, 0, 255 },
        { 30, 0, 120 },
        { 0, 0, 0 }
    };

    *red = pallete[index][RED];
    *green = pallete[index][GREEN];
    *blue = pallete[index][BLUE];
}