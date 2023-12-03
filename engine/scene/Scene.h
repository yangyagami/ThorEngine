#ifndef THOR_SCENE_H
#define THOR_SCENE_H

#include <string>
#include <vector>

#include "Camera2DComponent.hpp"
#include "GlobalContext.h"
#include "Texture2DComponent.hpp"
#include "TransformComponent.hpp"
#include "entt/entity/fwd.hpp"
#include "pch.h"
#include "entt/entt.hpp"

namespace Thor {
    class Scene {
    private:
        std::string mSceneName;
        std::vector<entt::entity> mEntities;
    protected:
        entt::entity &createEntity() {
            auto &registry = GlobalContext::singleton->registry;
            auto entity = registry.create();
            mEntities.push_back(entity);

            return mEntities.back();
        }
        void deleteEntity(entt::entity &e) {
            auto &registry = GlobalContext::singleton->registry;
            mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), e));
            registry.destroy(e);
        }
        std::vector<entt::entity> &getEntities() {
            return mEntities;
        }
    public:
        Scene(std::string name) : mSceneName(name) {

        }

        virtual ~Scene() {

        }

        virtual void update() {
        }

        virtual void render() {
            auto &registry = GlobalContext::singleton->registry;
            auto &renderer2D = GlobalContext::singleton->renderer2D;
            for (auto &e : mEntities) {
                auto texture2DComponent = registry.try_get<Texture2DComponent>(e);
                auto transformComponent = registry.try_get<TransformComponent>(e);
                glm::vec2 pos;
                if (transformComponent != nullptr) {
                    pos = transformComponent->position;
                }
                if (texture2DComponent != nullptr) {
                    renderer2D->drawTexture(texture2DComponent->texture2D, pos);
                }
            }
        }

        virtual void init() {
            SPDLOG_INFO("{} inited", mSceneName);
        }
    };
}

#endif
