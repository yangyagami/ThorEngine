#ifndef THOR_SPRITE_2D_H
#define THOR_SPRITE_2D_H

#include "GlobalContext.h"
#include "Object2D.hpp"
#include "Texture2DComponent.hpp"
#include "TransformComponent.hpp"

namespace Thor {
class Sprite2D : public Object2D {
public:
	Texture2DComponent texture2D;
public:
    Sprite2D(const std::string &name) : Object2D(name) {
    }

    virtual void init() override {
		transform.position = glm::vec2(0.0f, 0.0f);
		transform.scale = glm::vec2(1.0f, 1.0f);
	}

    virtual void update() override {
	}

    virtual void render() override {
		auto &renderer2D = GlobalContext::instance->renderer2D;
		auto root = getRoot();
		glm::vec2 finalPos = transform.position;
		if (root != nullptr) {
			finalPos.x = dynamic_cast<Object2D *>(root)->transform.position.x + transform.position.x;	
			finalPos.y = dynamic_cast<Object2D *>(root)->transform.position.y + transform.position.y;	
		}
		renderer2D->drawRectangle(finalPos, glm::vec2(30.0f, 30.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
};
}

#endif
