#ifndef THOR_OBJECT_H
#define THOR_OBJECT_H

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
    virtual void render() {}
};
}

#endif