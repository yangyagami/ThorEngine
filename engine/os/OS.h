#ifndef THOR_OS_H
#define THOR_OS_H

#include <string>

#include "glm/glm.hpp"

namespace Thor {
    class OS {
    public:
        virtual std::string getPlatform() = 0;
        virtual void process() = 0;
        virtual bool init() = 0;
        virtual bool appClosedRequested() = 0;
        virtual glm::vec2 getViewSize() = 0;
    };
}

#endif
