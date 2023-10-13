#include <iostream>

#include "ThorEngine.h"
#include "spdlog/spdlog.h"
#include "TestScene.h"

int main(int argc, char *argv[]) {
	Thor::Engine engine(argc, argv);
	
	TestScene testScene;

	if (engine.init(&testScene) == false) {
		spdlog::error("Engine init failed!");
		return -1;
	}
	return engine.run();
}
