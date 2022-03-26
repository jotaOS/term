#ifndef COMMON_HPP
#define COMMON_HPP

#include <types>

#define COLS 80
#define ROWS 25
#define BYTES_PER_ROW (COLS * 2)
#define DEFAULT_COLOR 0x0A

void init(size_t base, size_t row, size_t col);

void writec(char c);

inline void writes(const char* str, size_t sz) {
	while(sz--)
		writec(*str++);
}

void resetColor();
void setColor(uint8_t color);
void clear();

#endif
