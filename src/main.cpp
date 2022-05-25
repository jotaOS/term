#include <syscalls>
#include <common.hpp>
#include <cstring>
#include <export>

size_t asdf(size_t client, size_t x) {
	IGNORE(client);
	writec(x);
	return 42;
}

//extern "C" void rpcEntry();

extern "C" void _start(size_t fb, size_t row, size_t col) {
	init(fb, row, col);
	writes("[OK]", 4);

	std::exportProcedure((void*)asdf, 1);
	std::enableRPC(/*rpcEntry*/);
	std::publish("term");
	std::halt();
}
