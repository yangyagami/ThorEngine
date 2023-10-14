#include "TestScene.h"
#include "Camera2D.h"
#include "spdlog/spdlog.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "OpenglTexture2D.h"

void TestScene::init() {
	Scene::init();
	Thor::Camera2D camera;
	addObject(camera);
}

void TestScene::update() {
	Scene::update();
}

void TestScene::render() {
	Scene::render();
	auto &globalContext = Thor::GlobalContext::instance;
	auto &renderer = globalContext->renderer2D;

	renderer->drawRectangle(glm::vec2(30.0f, 30.0f), glm::vec2(130.2f, 130.5f), glm::vec4(0.2f, 0.5f, 0.1f, 1.0f));
}

