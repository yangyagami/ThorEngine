#include "ThorEngine.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "Renderer2D.h"

namespace Thor {
	Engine::Engine(int argc, char *argv[]) : mApp(argc, argv) {

	}

	bool Engine::init() {
		if (mApp.init() == false) {
			spdlog::error("Cannot init application!");
			return false;
		}	
		mRenderer = Renderer2D::create();
		if (mRenderer->init() == false) {
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
		mRenderer->drawRectangle(Vec2(0.5f, 0.5f), Vec2(0.05f, 0.05f), Vec4(1.0f, 0.5f, 1.0f, 1.0f));
		mRenderer->drawTriangle(Vec2(0.6f, 0.6f), Vec2(0.7f, 0.6f), Vec2(0.7f, 0.8f), Vec4(1.0f, 0.5f, 1.0f, 1.0f));
		mRenderer->drawCircle(Vec2(0.0f, 0.0f), 0.3f, Vec4(1.0f, 0.5f, 1.0f, 1.0f), 36);
		mRenderer->drawCircle(Vec2(-0.4f, -0.4f), 0.3f, Vec4(1.0f, 0.5f, 1.0f, 1.0f), 36);
	}

	int Engine::run() {
		spdlog::info("Engine running...");
		while (!mApp.closeRequested()) {
			update();

			mRenderer->beginBatch();
			render();
			mRenderer->endBatch();

			mApp.process();
		}
		return 0;
	}

	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
