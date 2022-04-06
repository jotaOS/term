#include <syscalls>
#include <common.hpp>
#include <cstring>

extern "C" void _start(size_t fb, size_t row, size_t col) {
	init(fb, row, col);
	writes("[OK]", 4);

	std::publish("term");
	std::halt();
}
