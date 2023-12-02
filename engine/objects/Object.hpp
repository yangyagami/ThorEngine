#ifndef THOR_OBJECT_H
#define THOR_OBJECT_H

#include "GlobalContext.h"
#include "entt/entt.hpp"
#include "spdlog/spdlog.h"

namespace Thor {
    class Object {
    public:
        entt::entity mEntity;
    	std::string name;
    public:
        Object() {
            auto &registry = GlobalContext::singleton->registry;
            mEntity = registry.create();
        }
    };
}

#endif
