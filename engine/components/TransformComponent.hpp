#ifndef THOR_TRANSFORM_COMPONENT_H
#define THOR_TRANSFORM_COMPONENT_H

#include "glm/glm.hpp"

namespace Thor {
struct TransformComponent {
    glm::vec2 position;
    glm::vec2 scale;

    TransformComponent() = default;
    TransformComponent(const glm::vec2 &pos, const glm::vec2 &scale) : position(pos), scale(scale) {}
};
}

#endif
