#include "ThorEngine.h"
#include "GlobalContext.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "Renderer2D.h"
#include "Texture2D.h"

namespace Thor {
	Engine::Engine(OS *os, int argc, char *argv[]) : mOS(os) {
		spdlog::info("Engine created");
	}

	void Engine::initLuaState() {
		//auto &registry = GlobalContext::instance->registry;

		mLuaState.open_libraries(sol::lib::base);

		// Set entt registry
		//mLuaState["registry"] = mLuaState.create_table_with("emplace", [&](entt::entity e, const std::string &componentName){
		//});
	}

	bool Engine::init() {
		mRenderer2D = Renderer2D::create();
		if (mRenderer2D->init() == false) {
			spdlog::error("Cannot init renderer!");
			return false;
		}

		GlobalContext::singleton = std::make_unique<GlobalContext>(mRenderer2D, mSceneManager, mLuaState);

		initLuaState();

		spdlog::info("Engine init success.");
		return true;
	}

    void Engine::update() {
		//glm::vec2 windowSize = mApp.getWindow().getSize();
		//mApp.setViewSize(windowSize);
		// logic stuff	
		auto currentScene = mSceneManager.getCurrentScene();
		if (currentScene != nullptr) currentScene->update();
	}
	
	void Engine::render() {
		auto currentScene = mSceneManager.getCurrentScene();
		if (currentScene != nullptr) currentScene->render();
	}

	void Engine::run() {
		update();

		mRenderer2D->beginBatch();
		render();
		mRenderer2D->endBatch();
	}

	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
