#include <syscalls>

volatile static int bruh;
volatile static int xd = 5;

extern "C" void _start() {
	asm volatile("xchgw %bx, %bx");

	volatile int a = std::test();
	bruh = 7;
	std::exit(a + xd + bruh);
}
