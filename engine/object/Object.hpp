#ifndef THOR_OBJECT_H
#define THOR_OBJECT_H

#include "AnchorComponent.hpp"
#include "ScriptComponent.hpp"
#include "Texture2DComponent.hpp"
#include "TransformComponent.hpp"
#include "entt/entt.hpp"
#include "GlobalContext.h"
#include "spdlog/spdlog.h"

namespace Thor {
struct Object {
public:
    entt::entity entity;
	std::string name;
public:
    Object(const std::string &name) : name(name) {
        auto &globalContext = GlobalContext::instance;
        auto &registry = globalContext->registry;
        entity = registry.create();
    }

    virtual ~Object() {

    }

    virtual void init() {
        auto &globalContext = GlobalContext::instance;
        auto &registry = globalContext->registry;
		auto viewScript = registry.view<ScriptComponent>();
		auto &luaState = globalContext->luaState;  

		for (auto [e, scriptComponent] : viewScript.each()) {
			if (entity == e) {
				auto loadResult = luaState.load_file(scriptComponent.scriptPath);
				if (!loadResult.valid()) {
					spdlog::error("Cannot open {}!", scriptComponent.scriptPath);
					return;
				}
				luaState.create_named_table(name);
				loadResult();
				auto initFunc = luaState[name]["init"];
				initFunc();
			}
		}
	}

    virtual void update() {
        auto &globalContext = GlobalContext::instance;
        auto &registry = globalContext->registry;
		auto viewScript = registry.view<ScriptComponent>();
		auto &luaState = globalContext->luaState;  

		for (auto [e, scriptComponent] : viewScript.each()) {
			if (entity == e) {
				auto updateFunc = luaState[name]["update"];
				updateFunc();
			}
		}
	}

    virtual void render() {
        auto &globalContext = GlobalContext::instance;
        auto &registry = globalContext->registry;
		auto &renderer = globalContext->renderer2D;
		auto viewTexture2D = registry.view<Texture2DComponent>();
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
    	for(auto [e, spriteComponent]: viewTexture2D.each()) {
			if (entity == e) {
				auto size = spriteComponent.texture2D->getSize();
				renderer->drawTexture(spriteComponent.texture2D, glm::vec2(pos.x - size.x * anchor.x, pos.y - size.y * anchor.y));
			}
    	}	
	}
};
}

#endif
