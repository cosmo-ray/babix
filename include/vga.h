#ifndef  __VGA_H__
#define  __VGA_H__

#include <stddef.h>
#include <stdint.h>

#include "strops.h"

enum vga_color
  {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
  };

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))
#define COLUMNS                 80
#define LINES                   24
#define ATTRIBUTE               7
#define VIDEO                   0xB8000

void cls (void);
void putchar (int c);

extern int xpos;
extern int ypos;
extern  volatile unsigned char *video;

#endif
