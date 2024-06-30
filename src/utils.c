#include <gint/display.h>
#include <gint/gint.h>
#include <gint/bfile.h>
#include <stdio.h>

#include "utils.h"

/* Short-shorthand for calling out vsprintf() */
#define shortprint(str, format) {   \
    va_list _args;          \
    va_start(_args, format);    \
    vsprintf(str, format, _args);   \
    va_end(_args);          \
}

//---
//  Row manipulation functions
//---

#ifdef FX9860G
#define ROW_X      1
#define ROW_W      6
#define ROW_Y      0
#define ROW_YPAD   0
#define ROW_H      8
#define ROW_COUNT  8
#endif /* FX9860G */

#ifdef FXCG50
#define ROW_X      6
#define ROW_W      8
#define ROW_Y      20
#define ROW_YPAD   2
#define ROW_H      14
#define ROW_COUNT  14
#endif /* FXCG50 */

/* row_title(): Render the main title */
void row_title(char const *format, ...)
{
    char str[80];
    shortprint(str, format);

    #ifdef FX9860G
    dtext(1, 0, C_BLACK, str);
    #endif

    #ifdef FXCG50
    drect(0, 0, DWIDTH-1, 15, C_BLUE);
    dtext(ROW_X, 3, C_WHITE, str);
    #endif
}

/* row_print(): Formatted printing in a predefined row */
void row_print(int row, int x, char const *format, ...)
{
    if(row < _(0,1) || row > ROW_COUNT) return;

    char str[80];
    shortprint(str, format);

    dtext(ROW_X + ROW_W * (x - 1), ROW_Y + ROW_H * (row - 1) + ROW_YPAD,
        C_BLACK, str);
}

/* row_print_color(): Formatted printing... with custom colors! */
void row_print_color(int row, int x, int fg, int bg, char const *format, ...)
{
    if(row < _(0,1) || row > ROW_COUNT) return;

    char str[80];
    shortprint(str, format);

    dtext_opt(ROW_X + ROW_W * (x-1), ROW_Y + ROW_H * (row-1) + ROW_YPAD,
        fg, bg, DTEXT_LEFT, DTEXT_TOP, str);
}

/* row_highlight(): Invert a row's pixels to highlight it */
void row_highlight(int row)
{
    int y1 = ROW_Y + ROW_H * (row - 1);
    int y2 = y1 + ROW_H;

    #ifdef FX9860G
    drect(0, y1, 125, y2 - 1, C_INVERT);
    #endif

    #ifdef FXCG50
    drect(0, y1, DWIDTH - 1, y2 - 1, C_INVERT);
    #endif
}

/* row_right(): Print at the last column of a row */
void row_right(int row, char const *character)
{
    #ifdef FX9860G
    row_print(row, 21, character);
    #endif

    #ifdef FXCG50
    dtext(370, ROW_Y + ROW_H * (row - 1) + ROW_YPAD, C_BLACK, character);
    #endif
}

/* scrollbar(): Show a scrollbar */
void scrollbar(int offset, int length, int top, int bottom)
{
    int area_x      = _(127, 391);
    int area_width  = _(1, 2);
    int area_top    = ROW_Y + ROW_H * (top - 1);
    int area_height = ROW_H * (bottom - top);

    int bar_top = (offset * area_height) / length;
    int bar_height = ((bottom - top) * area_height) / length;

    drect(area_x, area_top + bar_top, area_x + area_width - 1,
        area_top + bar_top + bar_height, C_BLACK);
}

/* row_count(): Number of rows available to row_print() */
int row_count(void)
{
    return ROW_COUNT;
}

int row_x(int x)
{
    return ROW_X + ROW_W * (x - 1);
}
int row_y(int y)
{
    return ROW_Y + ROW_H * (y - 1) + ROW_YPAD;
}

//---
//  General rendering
//---

/* scrollbar_px(): Pixel-based scrollbar */
void scrollbar_px(int view_top, int view_bottom, int range_min, int range_max,
    int range_pos, int range_view)
{
    int view_x      = _(127, 391);
    int view_width  = _(1, 2);
    int view_height = view_bottom - view_top;

    /* Bring virtual range to 0..range_max */
    range_max -= range_min;
    range_pos -= range_min;

    int bar_pos    = (range_pos  * view_height + range_max/2) / range_max;
    int bar_height = (range_view * view_height + range_max/2) / range_max;

    drect(view_x, view_top + bar_pos, view_x + view_width - 1,
        view_top + bar_pos + bar_height, C_BLACK);
}


/* fkey_button(): A rectangular F-key */
void fkey_button(int position, char const *text)
{
    int width;
    dsize(text, NULL, &width, NULL);

    int x = 4 + 65 * (position - 1);
    int y = 207;
    int w = 63;

    dline(x + 1, y, x + w - 2, y, C_BLACK);
    dline(x + 1, y + 14, x + w - 2, y + 14, C_BLACK);
    drect(x, y + 1, x + w - 1, y + 13, C_BLACK);

    dtext(x + ((w - width) >> 1), y + 3, C_WHITE, text);
}

void fkey_button_selected(int position, char const *text)
{
    int width;
    dsize(text, NULL, &width, NULL);

    int x = 4 + 65 * (position - 1);
    int y = 207;
    int w = 63;

    dline(x + 1, y, x + w - 2, y, C_BLUE);
    dline(x + 1, y + 14, x + w - 2, y + 14, C_BLUE);
    drect(x, y + 1, x + w - 1, y + 13, C_BLUE);

    dtext(x + ((w - width) >> 1), y + 3, C_WHITE, text);
}