#include "TestScene.h"
#include "Camera2D.h"
#include "ScriptComponent.hpp"
#include "spdlog/spdlog.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "OpenglTexture2D.h"
#include "Texture2DComponent.hpp"
#include "GlobalContext.h"

TestScene::TestScene() {
	auto &registry = Thor::GlobalContext::instance->registry;
	auto player = addObject("player");
	registry.emplace<Thor::ScriptComponent>(player->entity, "player.lua");
}

void TestScene::init() {
	Scene::init();
}

void TestScene::update() {
	Scene::update();
}

void TestScene::render() {
	Scene::render();
}

