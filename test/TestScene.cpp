#include "TestScene.h"
#include "Camera2D.h"
#include "spdlog/spdlog.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "OpenglTexture2D.h"
#include "SpriteComponent.hpp"
#include "GlobalContext.h"

TestScene::TestScene() {
	static Thor::Camera2D camera;
	addObject(&camera);

	static Thor::Object player;
	auto &globalContext = Thor::GlobalContext::instance;
    auto &registry = globalContext->registry;
    registry.emplace<Thor::SpriteComponent>(player.entity, "test.png");

	addObject(&player);
}

void TestScene::init() {
    Scene::init();
}

void TestScene::update() {
	Scene::update();
}

void TestScene::render() {
	Scene::render();
	auto &globalContext = Thor::GlobalContext::instance;
	auto &renderer = globalContext->renderer2D;
	auto &registry = globalContext->registry;
	renderer->drawRectangle(glm::vec2(30.0f, 30.0f), glm::vec2(130.2f, 130.5f), glm::vec4(0.2f, 0.5f, 0.1f, 1.0f));

	auto view = registry.view<Thor::SpriteComponent>();
	for (auto entity : view) {
		auto &textureComponent = view.get<Thor::SpriteComponent>(entity);

		renderer->drawTexture(textureComponent.texture2D, glm::vec2(200.0f, 280.0f));
	}
}

