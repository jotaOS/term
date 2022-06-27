#include "common.hpp"
#include <cstring>
#include <export>
#include <rpc>
#include <shared_memory>
#include <unordered_map>

std::unordered_map<std::PID, char*> shared;

bool connect(std::PID client, std::SMID smid) {
	// Already connected?
	if(!std::smRequest(client, smid))
		return false;

	char* ptr = (char*)std::smMap(smid);
	if(!ptr)
		return false;

	// TODO: unmap previous, release SMID
	shared[client] = ptr;
	return true;
}

size_t flush(std::PID client, size_t sz) {
	if(sz >= PAGE_SIZE)
		return ~0;

	writes(shared[client], sz);
	return sz;
}

extern "C" void _start(size_t fb, size_t* sync) {
	init(fb, sync);

	std::exportProcedure((void*)connect, 1);
	std::exportProcedure((void*)flush, 1);
	std::enableRPC();
	std::publish("term");
	std::halt();
}
