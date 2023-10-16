#ifndef THOR_CAMERA_2D_H
#define THOR_CAMERA_2D_H

#include "Object.hpp"

namespace Thor {
class Camera2D : public Object {
private:
    void initCameraSystem();
public:
	Camera2D(const std::string &name) : Object(name) {}
    virtual void init() override;
    virtual void update() override;
    virtual void render() override;
};
}

#endif
