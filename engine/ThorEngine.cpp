#include "ThorEngine.h"
#include "GlobalContext.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "Renderer2D.h"
#include "Texture2D.h"

namespace Thor {
	Engine::Engine(int argc, char *argv[]) : mApp(argc, argv), mEditor(nullptr), mRegistry(), mSceneManager(), mLuaState() {
		spdlog::info("Engine created");
	}

	void Engine::initLuaState() {
		//auto &registry = GlobalContext::instance->registry;

		mLuaState.open_libraries(sol::lib::base);

		// Set entt registry
		//mLuaState["registry"] = mLuaState.create_table_with("emplace", [&](entt::entity e, const std::string &componentName){
		});
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

		GlobalContext::instance = std::make_unique<GlobalContext>(mRenderer, mRegistry, mApp, mSceneManager, mLuaState);

		//mEditor = std::make_unique<Editor>();
		//mEditor->init();

		initLuaState();

		spdlog::info("Engine init success.");
		return true;
	}

    void Engine::update() {
		glm::vec2 windowSize = mApp.getWindow().getSize();
		mApp.setViewSize(windowSize);
		// logic stuff	
		auto currentScene = mSceneManager.getCurrentScene();
		if (currentScene != nullptr) currentScene->update();
	}
	
	void Engine::render() {
		auto currentScene = mSceneManager.getCurrentScene();
		if (currentScene != nullptr) currentScene->render();
	}

	int Engine::run() {
		spdlog::info("Engine running...");
		while (!mApp.closeRequested()) {
			update();
			//mEditor->update();

			mRenderer->beginBatch();
			render();
			mRenderer->endBatch();

			//mEditor->render();

			mApp.process();
		}
		return 0;
	}

	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
