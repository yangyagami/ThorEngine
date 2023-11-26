#ifndef THOR_OS_H
#define THOR_OS_H

#include <string>

namespace Thor {
    class OS {
    public:
        virtual std::string getPlatform() = 0;
        virtual void process() = 0;
        virtual bool init() = 0;
        virtual bool appClosedRequested() = 0;
    };
}

#endif
