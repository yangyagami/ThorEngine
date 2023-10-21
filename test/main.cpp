#include <iostream>

#include "GlobalContext.h"
#include "ThorEngine.h"
#include "spdlog/spdlog.h"
#include "TestScene.h"
#include "Camera2D.h"
#include "sol/sol.hpp"

int main(int argc, char *argv[]) {
	Thor::Engine engine(argc, argv);

	if (engine.init() == false) {
		spdlog::error("Engine init failed!");
		return -1;
	}

	TestScene testScene("TestScene");
	auto &sceneManager = Thor::GlobalContext::instance->sceneManager;
	sceneManager.switchScene(&testScene);

	return engine.run();
}
