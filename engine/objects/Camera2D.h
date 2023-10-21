#ifndef THOR_CAMERA_2D_H
#define THOR_CAMERA_2D_H

#include "Object2D.hpp"

namespace Thor {
class Camera2D : public Object2D {
public:
	Camera2D(const std::string &name) : Object2D(name) {}
    virtual void init() override;
    virtual void update() override;
    virtual void render() override;
};
}

#endif
