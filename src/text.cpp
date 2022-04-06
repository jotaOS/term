#include <common.hpp>
#include <cstring>

static size_t base = 0;
static size_t row = 0;
static size_t col = 0;
static char color = DEFAULT_COLOR;

void init(size_t fb, size_t r, size_t c) {
	base = fb;
	row = r;
	col = c;
}

inline static char* getChar(size_t r, size_t c) {
	return ((char*)base) + (COLS * r + c)*2;
}

inline static char* getVideo() { return getChar(row, col); }

inline static void clearRow(size_t r) {
	char* buffer = getChar(r, 0);
	for(size_t i=0; i<COLS; ++i) {
		*buffer++ = ' ';
		*buffer++ = color;
	}
}

inline static void scroll() {
	void* from = (void*)(base + BYTES_PER_ROW);
	// Move up
	memmove((void*)base, from, (ROWS-1)*BYTES_PER_ROW);
	// Go up
	--row;
	// Clear last line
	clearRow(ROWS-1);
}

static void goAhead() {
	// Next column
	++col;

	if(col >= COLS) {
		// Have to go the next line
		++row;
		col = 0;

		if(row >= ROWS) {
			// Have to scroll
			scroll();
		}
	}
}

void writec(char c) {
	if(c == '\n') {
		++row;
		col = 0;
		if(row >= ROWS) scroll();
		return;
	}

	char* video = getVideo();
	*video++ = c;
	*video = color;
	goAhead();
}

void resetColor() { color = DEFAULT_COLOR; }
void setColor(uint8_t c) { color = c; }

void clear() {
	for(size_t i=0; i<ROWS; ++i)
		clearRow(i);
	row = col = 0;
}
