#include <iostream>

#include "ThorEngine.h"
#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {
	Thor::Engine engine(argc, argv);
	if (engine.init() == false) {
		spdlog::error("Engine init failed!");
		return -1;
	}
	return engine.run();
}
