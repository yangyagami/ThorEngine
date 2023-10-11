#include "ThorEngine.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "OpenglVao.h"
#include "OpenglVbo.h"
#include "OpenglShader.h"

namespace Thor {
	Engine::Engine(int argc, char *argv[]) : mApp(argc, argv) {

	}

	bool Engine::init() {
		if (mApp.init() == false) {
			spdlog::error("Cannot init application!");
			return false;
		}	
		spdlog::info("Engine init success.");

		return true;
	}

	void Engine::update() {
		// logic stuff	
	}
	
	void Engine::render() {
		glClear(GL_COLOR_BUFFER_BIT);	
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	}

	int Engine::run() {
		spdlog::info("Engine running...");
		while (!mApp.closeRequested()) {
			update();
			render();

			mApp.process();
		}
		return 0;
	}

	
	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
