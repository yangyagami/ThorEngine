#include "SceneManager.h"
#include "spdlog/spdlog.h"

namespace Thor {
    void SceneManager::switchScene(Object *scene) {
        if (scene == nullptr) {
            spdlog::warn("Target scene is null!");
        }
        mCurrentScene = scene;
		mCurrentScene->init();
    }

    Object *SceneManager::getCurrentScene() {
        return mCurrentScene;
    }

    SceneManager::SceneManager() : mCurrentScene(nullptr) {
    }
}
