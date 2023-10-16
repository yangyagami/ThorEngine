#ifndef THOR_OBJECT_H
#define THOR_OBJECT_H

#include "AnchorComponent.hpp"
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
		auto viewAnchor = registry.view<AnchorComponent>();
		glm::vec2 pos(0.0f, 0.0f);
		glm::vec2 anchor(0.0f, 0.0f);
    	for(auto [e, anchorComponent]: viewAnchor.each()) {
			if (entity == e) {
				anchor = anchorComponent.point;
			}
    	}	
    	for(auto [e, transformComponent]: viewTransform.each()) {
			if (entity == e) {
				pos = transformComponent.position;
			}
    	}	
    	for(auto [e, spriteComponent]: viewSprite.each()) {
			if (entity == e) {
				auto size = spriteComponent.texture2D->getSize();
				renderer->drawTexture(spriteComponent.texture2D, glm::vec2(pos.x - size.x * anchor.x, pos.y - size.y * anchor.y));
			}
    	}	
	}
};
}

#endif
