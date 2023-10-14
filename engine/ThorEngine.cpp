#include "ThorEngine.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "Renderer2D.h"
#include "Texture2D.h"

namespace Thor {
	Engine::Engine(int argc, char *argv[]) : mApp(argc, argv), mEditor(nullptr), mCurrentScene(nullptr), mRegistry() {
		spdlog::info("Engine created");
	}

	bool Engine::init(Scene *scene) {
		if (scene == nullptr) {
			spdlog::error("Cannot start with null scene");
			return false;
		}
		mCurrentScene = scene;
		if (mApp.init() == false) {
			spdlog::error("Cannot init application!");
			return false;
		}	
		mRenderer = Renderer2D::create();
		if (mRenderer->init() == false) {
			spdlog::error("Cannot init renderer!");
			return false;
		}

		GlobalContext::instance = std::make_unique<GlobalContext>(mRenderer, mRegistry, mApp);
		
		mCurrentScene->init();

		mEditor = std::make_unique<Editor>();
		mEditor->init();

		spdlog::info("Engine init success.");
		return true;
	}

	void Engine::update() {
		glm::vec2 windowSize = mApp.getWindow().getSize();
		mApp.setViewSize(windowSize);
		// logic stuff	
		if (mCurrentScene != nullptr) mCurrentScene->update();
	}
	
	void Engine::render() {
		if (mCurrentScene != nullptr) mCurrentScene->render();
	}

	int Engine::run() {
		spdlog::info("Engine running...");
		while (!mApp.closeRequested()) {
			update();
			mEditor->update();

			mRenderer->beginBatch();
			render();
			mRenderer->endBatch();

			mEditor->render();

			mApp.process();
		}
		return 0;
	}

	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
