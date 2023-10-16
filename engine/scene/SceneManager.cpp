#include "SceneManager.h"
#include "spdlog/spdlog.h"
#include "Scene.h"

namespace Thor {
    void SceneManager::switchScene(Scene *scene) {
        if (scene == nullptr) {
            spdlog::warn("Target scene is null!");
        }
        mCurrentScene = scene;
		mCurrentScene->init();
    }

    Scene *SceneManager::getCurrentScene() {
        return mCurrentScene;
    }

    SceneManager::SceneManager() : mCurrentScene(nullptr) {
    }
}
