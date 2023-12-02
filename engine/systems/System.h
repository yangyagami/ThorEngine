#ifndef THOR_SYSTEM_H
#define THOR_SYSTEM_H

#include "entt/entity/fwd.hpp"
namespace Thor {
    class System {
    public:
        virtual void init(entt::entity &e) {};
        virtual void update(entt::entity &e) {};
    };
}

#endif
