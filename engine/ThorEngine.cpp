#include "ThorEngine.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "Renderer.h"

namespace Thor {
	Engine::Engine(int argc, char *argv[]) : mApp(argc, argv) {

	}

	bool Engine::init() {
		if (mApp.init() == false) {
			spdlog::error("Cannot init application!");
			return false;
		}	
		if (mRenderer.init() == false) {
			spdlog::error("Cannot init renderer!");
			return false;
		}
		spdlog::info("Engine init success.");

		return true;
	}

	void Engine::update() {
		// logic stuff	
	}
	
	void Engine::render() {
		for (int row = -20; row < 20; row++) {
			for (int col = -20; col < 20; col++) {
				mRenderer.drawRectangle(Vec2(col * 0.06f, row * 0.06f), Vec2(0.05f, 0.05f), Vec4(1.0f, 0.5f, 1.0f, 1.0f));
			}
		}
	}

	int Engine::run() {
		spdlog::info("Engine running...");
		while (!mApp.closeRequested()) {
			update();

			mRenderer.beginBatch();
			render();
			mRenderer.endBatch();

			mApp.process();
		}
		return 0;
	}

	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
