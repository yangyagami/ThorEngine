#include "Camera2D.h"
#include "GlobalContext.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Thor {
    void Camera2D::init() {
		auto &app = GlobalContext::instance->app;
		auto &renderer2D = GlobalContext::instance->renderer2D;
		auto viewsize = app.getViewSize();
		renderer2D->setProjection(glm::ortho(0.0f, viewsize.x, viewsize.y, 0.0f, -1.0f, 1.0f));
    }

    void Camera2D::update() {
    }

    void Camera2D::render() {
    }
}
