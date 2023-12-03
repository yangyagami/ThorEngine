#include <memory>
#include <tuple>

#include "TestScene.h"
#include "Camera2DComponent.hpp"
#include "GlobalContext.h"
#include "SceneManager.h"
#include "Texture2DComponent.hpp"
#include "TransformComponent.hpp"
#include "entt/entt.hpp"
#include "spdlog/spdlog.h"

__attribute__((visibility("default")))
void GameInit() {
    auto testScene = std::make_shared<TestScene>("TestScene");
    auto &sceneManager = Thor::GlobalContext::singleton->sceneManager;
    testScene->init();
    sceneManager.switchScene(testScene);
}

void TestScene::init() {
    Thor::Scene::init();

    auto rect = createEntity();
    auto &registry = Thor::GlobalContext::singleton->registry;
    registry.emplace<Thor::TransformComponent>(rect, Thor::TransformComponent());
    registry.emplace<Thor::Camera2DComponent>(rect, Thor::Camera2DComponent());

    mCamera2DSystem.init(rect);
}

void TestScene::update() {
    Thor::Scene::update();

    auto dt = Thor::GlobalContext::singleton->frameDelta;

    auto &registry = Thor::GlobalContext::singleton->registry;
    for (auto &e : getEntities()) {
        auto &transformComponent = registry.get<Thor::TransformComponent>(e);
        transformComponent.position.x += 100 * dt;
    }
}

void TestScene::render() {
    Thor::Scene::render();

    auto &registry = Thor::GlobalContext::singleton->registry;
    auto &renderer2D = Thor::GlobalContext::singleton->renderer2D;

    for (auto &e : getEntities()) {
        auto transformComponent = registry.get<Thor::TransformComponent>(e);
        renderer2D->drawRectangle(
            transformComponent.position,
            glm::vec2(30.0f, 30.0f),
            glm::vec4(0.0f, 0.7f, 1.0f, 1.0f)
        );
    }
}

