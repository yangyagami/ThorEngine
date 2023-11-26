#ifndef THOR_LINUX_OS_H
#define THOR_LINUX_OS_H

#include "os/OS.h"
#include "Window.h"

namespace Thor {
    class LinuxOS : public OS {
    private:
        Window mWindow;
    public:
        virtual std::string getPlatform() override;
        virtual void process() override;
        virtual bool init() override;
        virtual bool appClosedRequested() override;
    };
}

#endif
