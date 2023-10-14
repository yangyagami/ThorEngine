#ifndef THOR_SPRITE_COMPONENT_H
#define THOR_SPRITE_COMPONENT_H

#include <memory>

#include "Texture2D.h"

namespace Thor {
struct SpriteComponent {
    std::unique_ptr<Texture2D> texture2D;

    SpriteComponent(const std::string &path) : texture2D(nullptr) {
        texture2D = Texture2D::create(path);
    }
};
}

#endif