#include "TestScene.h"
#include "Camera2D.hpp"
#include "spdlog/spdlog.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "OpenglTexture2D.h"

void TestScene::init() {
	auto &globalContext = Thor::GlobalContext::instance;
	auto &renderer = globalContext->renderer2D;
	auto &registry = globalContext->registry;
	auto &app = globalContext->app;
	auto camera2D = registry.create();
	registry.emplace<Thor::Camera2D>(camera2D, glm::vec2(0.0f, 0.0f), glm::vec2(800.0f, 600.0f), 0.0f);
	auto view = registry.view<Thor::Camera2D>();
	for (auto entity : view) {
		auto &camera2D = view.get<Thor::Camera2D>(entity);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(camera2D.position.x, camera2D.position.y, 0.2f));
		glm::mat4 projection = glm::ortho(0.0f, app.getViewSize().x, app.getViewSize().y, 0.0f, -1.0f, 1.0f);
		
		renderer->setProjection(std::move(projection));	
		renderer->setView(std::move(view));	
	}
}

void TestScene::update() {
	auto &globalContext = Thor::GlobalContext::instance;
	auto &renderer = globalContext->renderer2D;
	auto &registry = globalContext->registry;
	auto &app = globalContext->app;
	auto view = registry.view<Thor::Camera2D>();
	for (auto entity : view) {
		auto &camera2D = view.get<Thor::Camera2D>(entity);
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(camera2D.position.x, camera2D.position.y, 0.2f));
		glm::mat4 projection = glm::ortho(0.0f, app.getViewSize().x, app.getViewSize().y, 0.0f, -1.0f, 1.0f);
		
		renderer->setProjection(std::move(projection));	
		renderer->setView(std::move(view));	
	}
}

void TestScene::render() {
	auto &globalContext = Thor::GlobalContext::instance;
	auto &renderer = globalContext->renderer2D;

	renderer->drawRectangle(glm::vec2(30.0f, 30.0f), glm::vec2(130.2f, 130.5f), glm::vec4(0.2f, 0.5f, 0.1f, 1.0f));
}

