#ifndef THOR_CAMERA_2D_SYSTEM_H
#define THOR_CAMERA_2D_SYSTEM_H

#include "Camera2DComponent.hpp"
#include "System.h"
#include "GlobalContext.h"
#include "glm/ext/matrix_clip_space.hpp"

namespace Thor {
    class Camera2DSystem : public System {
    public:
        virtual void init(entt::entity &e) {
            auto &registry = GlobalContext::singleton->registry;
            auto &renderer2D = GlobalContext::singleton->renderer2D;
            auto os = GlobalContext::singleton->os;
            auto viewSize = os->getViewSize();
            auto camera2DComponent = registry.try_get<Camera2DComponent>(e);
            if (camera2DComponent != nullptr) {
                camera2DComponent->projection = glm::ortho(0.0f, viewSize.x, viewSize.y, 0.0f, -1.0f, 1.0f);
                camera2DComponent->view = glm::mat4(1.0f);
                renderer2D->setProjection(camera2DComponent->projection);
                renderer2D->setView(camera2DComponent->view);
            }
        }
    };
}


#endif
