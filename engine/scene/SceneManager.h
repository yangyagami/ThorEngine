#ifndef THOR_SCENE_MANAGER_H
#define THOR_SCENE_MANAGER_H

#include "Object.hpp"

namespace Thor {

class SceneManager {
private:
    Object *mCurrentScene;
public:
    void switchScene(Object *scene);
    Object *getCurrentScene();
    SceneManager();
};
}

#endif
