#include "LinuxOS.h"
#include "GLFW/glfw3.h"
#include "pch.h"

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

    glm::vec2 LinuxOS::getViewSize() {
        return mWindow.getSize();
    }

    double LinuxOS::getCurrentTime() {
        return glfwGetTime();
    }

}
