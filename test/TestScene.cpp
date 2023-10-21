#include "TestScene.h"
#include "Camera2D.h"
#include "Keyboard.h"
#include "Object2D.hpp"
#include "Sprite2D.hpp"
#include "spdlog/spdlog.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GlobalContext.h"

TestScene::TestScene(const std::string &name) : Thor::Object2D(name) {
	mTestSprite = new Thor::Sprite2D("testSprite");
	addChild(mTestSprite);
	addChild(new Thor::Camera2D("camera"));
}

void TestScene::init() {
	Thor::Object2D::init();
}

void TestScene::update() {
	Thor::Object2D::update();
	auto &app = Thor::GlobalContext::instance->app;

	if (app.getKeyboard().isKeyPressed(GLFW_KEY_D)) {
		mTestSprite->transform.position.x += 0.5f;	
	}
}

void TestScene::render() {
	Thor::Object2D::render();
}

