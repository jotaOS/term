#include <common.hpp>
#include <driver>

void initCursor() {
	std::out8(CURSOR_CONFIG, CURSOR_ENABLE1);
	std::out8(CURSOR_DATA, (std::in8(CURSOR_DATA) & 0xC0) | CURSOR_MIN_SCANLINE);

	std::out8(CURSOR_CONFIG, CURSOR_ENABLE2);
	std::out8(CURSOR_DATA, (std::in8(CURSOR_DATA) & 0xE0) | CURSOR_MAX_SCANLINE);
}

void updateCursor(size_t row, size_t col) {
	uint16_t pos = row * COLS + col;

	std::out8(CURSOR_CONFIG, CURSOR_MOVE_LSB);
	std::out8(CURSOR_DATA, pos & 0xFF);

	std::out8(CURSOR_CONFIG, CURSOR_MOVE_MSB);
	std::out8(CURSOR_DATA, pos >> 8);
}
