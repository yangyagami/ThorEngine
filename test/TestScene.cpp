#include "TestScene.h"

void TestScene::init() {

}

void TestScene::update() {

}

void TestScene::render() {
	auto &globalContext = Thor::GlobalContext::instance;
	auto &renderer = globalContext->renderer2D;

	renderer->drawRectangle(glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.5f), glm::vec4(0.2f, 0.2f, 0.1f, 1.0f));
}

