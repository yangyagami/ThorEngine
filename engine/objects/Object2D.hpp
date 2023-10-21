#ifndef THOR_OBJECT_2D_H
#define THOR_OBJECT_2D_H

#include "Object.hpp"
#include "TransformComponent.hpp"

namespace Thor {
class Object2D : public Object {
public:
	TransformComponent transform;
public:
    Object2D(const std::string &name) : Object(name) {
    }

    virtual void init() override {
		Object::init();
		transform.position = glm::vec2(0.0f, 0.0f);
		transform.scale = glm::vec2(1.0f, 1.0f);
	}

    virtual void update() override {
		Object::update();
	}

    virtual void render() override {
		Object::render();
	}
};
}

#endif
