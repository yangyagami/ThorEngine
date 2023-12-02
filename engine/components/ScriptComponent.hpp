#ifndef THOR_SCRIPT_COMPONENT_H
#define THOR_SCRIPT_COMPONENT_H

#include <memory>

#include "Texture2D.h"

namespace Thor {
    struct ScriptComponent {
    	std::string scriptPath;
    
        ScriptComponent(const std::string &path) : scriptPath(path) {
        }
    };
}

#endif
