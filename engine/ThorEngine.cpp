#include "ThorEngine.h"
#include "spdlog/spdlog.h"

namespace Thor {
	Engine::Engine(int argc, char *argv[]) {

	}

	int Engine::run() {
		spdlog::info("Engine running!");
		return 0;
	}
}
