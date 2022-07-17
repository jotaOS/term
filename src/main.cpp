#include "common.hpp"
#include <cstring>
#include <export>
#include <rpc>
#include <shared_memory>
#include <unordered_map>
#include <mutex>

bool connect(std::PID client, std::SMID smid) {
	return std::sm::connect(client, smid);
}

static std::mutex lock;

size_t flush(std::PID client, size_t sz) {
	if(sz >= PAGE_SIZE)
		return ~0;

	char* ptr = (char*)std::sm::get(client);
	if(!ptr)
		return 0;

	lock.acquire();
	writes(ptr, sz);
	lock.release();
	return sz;
}

void pubClear(std::PID client) {
	IGNORE(client);

	lock.acquire();
	clear();
	lock.release();
}

extern "C" void _start(size_t fb, size_t* sync) {
	// Need IO privileges for cursor
	if(std::allowIO() != 0)
		std::exit(1);

	init(fb, sync);
	initCursor();

	std::exportProcedure((void*)connect, 1);
	std::exportProcedure((void*)flush, 1);
	std::exportProcedure((void*)pubClear, 1);
	std::enableRPC();
	std::publish("term");
	std::halt();
}
