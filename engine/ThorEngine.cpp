#include <chrono>
#include <ratio>
#include <thread>
#include <unistd.h>

#include "ThorEngine.h"
#include "GlobalContext.h"
#include "pch.h"
#include "glad/glad.h"
#include "Renderer2D.h"
#include "Texture2D.h"
#include "Scene.h"

namespace Thor {
	Engine::Engine(OS *os, int argc, char *argv[]) : mOS(os) {
#ifdef _DEBUG
        spdlog::set_level(spdlog::level::trace);
#endif
		spdlog::info("Engine created");
	}

	void Engine::initLuaState() {
		//auto &registry = GlobalContext::instance->registry;

		mLuaState.open_libraries(sol::lib::base);

		// Set entt registry
		//mLuaState["registry"] = mLuaState.create_table_with("emplace", [&](entt::entity e, const std::string &componentName){
		//});
	}

    void Engine::initECS() {
    }

	bool Engine::init() {
		mRenderer2D = Renderer2D::create();
		if (mRenderer2D->init() == false) {
			spdlog::error("Cannot init renderer!");
			return false;
		}

		GlobalContext::singleton = std::make_unique<GlobalContext>(
            mOS,
            mRenderer2D,
            mSceneManager, 
            mLuaState, 
            mEnttRegistry
        );

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
        static double startTime = 0.0f;
        static double endTime = 0.0f;
        static double diffTime = 0.0f;

        startTime = mOS->getCurrentTime();

		update();

		mRenderer2D->beginBatch();
		render();
		mRenderer2D->endBatch();

        endTime = mOS->getCurrentTime();

        diffTime = endTime - startTime;

        if (fabs(diffTime) < 0.0001f) diffTime = 0.0001f;
        auto maxFrameLimit = GlobalContext::singleton->maxFrameLimit;
        if (diffTime < 1.0f / maxFrameLimit) {
            auto diffTimeForSleep = 1.0f / maxFrameLimit - diffTime;
            sleep(diffTimeForSleep);
            diffTime = 1.0f / maxFrameLimit;
        }

        GlobalContext::singleton->frameDelta = diffTime;
	}

	Engine::~Engine() {
		spdlog::info("Engine destroyed.");	
	}

}
