#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Object2D.hpp"
#include "Sprite2D.hpp"

class TestScene : public Thor::Object2D {
private:
	Thor::Sprite2D *mTestSprite;
public:
	TestScene(const std::string &name);
	virtual void init() override;
	virtual void update() override;
	virtual void render() override;
};

#endif
