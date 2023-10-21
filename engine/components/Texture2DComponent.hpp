#ifndef THOR_TEXTURE_2D_COMPONENT_H
#define THOR_TEXTURE_2D_COMPONENT_H

#include <memory>

#include "Texture2D.h"

namespace Thor {
struct Texture2DComponent {
    std::unique_ptr<Texture2D> texture2D;

    Texture2DComponent() {
        texture2D = Texture2D::create();
    }
    Texture2DComponent(const std::string &path) : texture2D(nullptr) {
        texture2D = Texture2D::create(path);
    }
};
}

#endif
