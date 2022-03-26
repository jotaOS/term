#include <syscalls>
#include <common.hpp>
#include <cstring>

extern "C" void _start(size_t fb, size_t row, size_t col) {
	asm volatile("xchgw %bx, %bx");
	init(fb, row, col);
	writes("[OK]", 4);

	while(true);
	// TODO: publish & halt
}
