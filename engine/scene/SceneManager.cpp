#include "SceneManager.h"
#include "Scene.h"
#include "pch.h"

namespace Thor {
    void SceneManager::switchScene(std::shared_ptr<Scene> scene) {
        if (scene == nullptr) {
            spdlog::warn("Target scene is null!");
        }
        mCurrentScene = scene;
		//mCurrentScene->init();
    }

    std::shared_ptr<Scene> SceneManager::getCurrentScene() {
        return mCurrentScene;
    }

    SceneManager::SceneManager() : mCurrentScene(nullptr) {
    }
}
