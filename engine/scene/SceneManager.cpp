#include "SceneManager.h"
#include "spdlog/spdlog.h"

namespace Thor {
    void SceneManager::switchScene(Scene *scene) {
        if (scene == nullptr) {
            spdlog::warn("Target scene is null!");
        }
        mCurrentScene = scene;
    }

    Scene *SceneManager::getCurrentScene() {
        return mCurrentScene;
    }

    SceneManager::SceneManager() : mCurrentScene(nullptr) {
    }
}
