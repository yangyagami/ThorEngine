#include "Camera2D.h"
#include "GlobalContext.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera2DComponent.hpp"

namespace Thor {
    void Camera2D::initCameraSystem() {
        auto &globalContext = GlobalContext::instance;
        auto &renderer = globalContext->renderer2D;
        auto &registry = globalContext->registry;
        auto &app = globalContext->app;
        registry.emplace<Camera2DComponent>(entity, glm::vec2(0.0f, 0.0f), 0.0f);
        auto view = registry.view<Camera2DComponent>();
        for (auto entity : view) {
            auto &camera2D = view.get<Camera2DComponent>(entity);
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(camera2D.position.x, camera2D.position.y, 0.2f));
            glm::mat4 projection = glm::ortho(0.0f, app.getViewSize().x, app.getViewSize().y, 0.0f, -1.0f, 1.0f);

            renderer->setProjection(std::move(projection));
            renderer->setView(std::move(view));
        }
    }

    void Camera2D::init() {
        initCameraSystem();
    }

    void Camera2D::update() {
    }

    void Camera2D::render() {
    }
}