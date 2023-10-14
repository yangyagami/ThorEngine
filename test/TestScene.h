#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Scene.h"
#include "GlobalContext.h"

class TestScene : public Thor::Scene {
public:
	TestScene();
	void init() override;
	void update() override;
	void render() override;
};

#endif
