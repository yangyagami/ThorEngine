#ifndef THOR_CAMERA_2D_COMPONENT_H
#define THOR_CAMERA_2D_COMPONENT_H

#include "glm/glm.hpp"

namespace Thor {

    struct Camera2DComponent {
        glm::mat4 view;
        glm::mat4 projection;
    };

}

#endif
