#ifndef THOR_SCENE_MANAGER_H
#define THOR_SCENE_MANAGER_H

#include <memory>
namespace Thor {

class Scene;

class SceneManager {
private:
    std::shared_ptr<Scene> mCurrentScene;
public:
    void switchScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getCurrentScene();
    SceneManager();
};
}

#endif
