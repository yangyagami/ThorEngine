#ifndef THOR_SCENE_MANAGER_H
#define THOR_SCENE_MANAGER_H

namespace Thor {

class Scene;

class SceneManager {
private:
    Scene *mCurrentScene;
public:
    void switchScene(Scene *scene);
    Scene *getCurrentScene();
    SceneManager();
};
}

#endif