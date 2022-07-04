#ifndef COMMON_HPP
#define COMMON_HPP

#include <types>

#define COLS 80
#define ROWS 25
#define BYTES_PER_ROW (COLS * 2)
#define DEFAULT_COLOR 0x0A

void init(size_t base, size_t* sync);

void writec(char c);
void writes(const char* str, size_t sz);

void resetColor();
void setColor(uint8_t color);
void clear();



#define CURSOR_CONFIG 0x3D4
#define CURSOR_DATA   0x3D5

#define CURSOR_ENABLE1 0x0A
#define CURSOR_ENABLE2 0x0B
#define CURSOR_MOVE_LSB 0x0F
#define CURSOR_MOVE_MSB 0x0E

#define CURSOR_MIN_SCANLINE 0
#define CURSOR_MAX_SCANLINE 15

void initCursor();
void updateCursor(size_t row, size_t col);

#endif
