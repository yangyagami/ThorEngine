#ifndef THOR_ANCHOR_COMPONENT_H
#define THOR_ANCHOR_COMPONENT_H

#include "glm/glm.hpp"

namespace Thor {
struct AnchorComponent {
    glm::vec2 point;

    AnchorComponent() = default;
    AnchorComponent(const glm::vec2 &p) : point(p) {}
};
}

#endif
