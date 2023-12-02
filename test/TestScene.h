#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Scene.h"
#include "systems/Camera2DSystem.hpp"

class TestScene : public Thor::Scene {
private:
    Thor::Camera2DSystem mCamera2DSystem;
public:
    using Thor::Scene::Scene;

    virtual void init();
    virtual void update();
    virtual void render();
};

#endif
