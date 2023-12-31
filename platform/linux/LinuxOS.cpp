#include "LinuxOS.h"
#include "spdlog/spdlog.h"

namespace Thor {

    bool LinuxOS::init() {
        bool ret = true;
        if (!mWindow.init(800, 600)) {
            SPDLOG_ERROR("Window inited failed!!!");
            ret = false;
        }

        return ret;
    }
    
    bool LinuxOS::appClosedRequested() {
        return mWindow.shouldClose(); 
    }

    std::string LinuxOS::getPlatform() {
        return "Linux"; 
    }

    void LinuxOS::process() {
        mWindow.swapBuffers(); 
        mWindow.pollEvents();
    }

}
