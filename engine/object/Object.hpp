#ifndef THOR_OBJECT_H
#define THOR_OBJECT_H

#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "entt/entt.hpp"
#include "GlobalContext.h"

namespace Thor {
struct Object {
public:
    entt::entity entity;
public:
    Object() {
        auto &globalContext = GlobalContext::instance;
        auto &registry = globalContext->registry;
        entity = registry.create();
    }
    virtual ~Object() {

    }
    virtual void init() {}
    virtual void update() {}
    virtual void render() {
        auto &globalContext = GlobalContext::instance;
        auto &registry = globalContext->registry;
		auto &renderer = globalContext->renderer2D;
		auto viewSprite = registry.view<SpriteComponent>();
		auto viewTransform = registry.view<TransformComponent>();
		glm::vec2 pos(0.0f, 0.0f);
    	for(auto [e, transformComponent]: viewTransform.each()) {
			if (entity == e) {
				pos = transformComponent.position;
			}
    	}	
    	for(auto [e, spriteComponent]: viewSprite.each()) {
			if (entity == e) {
				renderer->drawTexture(spriteComponent.texture2D, pos);
			}
    	}	
	}
};
}

#endif
