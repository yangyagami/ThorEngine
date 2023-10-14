#ifndef THOR_CAMERA_2D_H
#define THOR_CAMERA_2D_H

#include "Object.hpp"

namespace Thor {
class Camera2D : public Object {
private:
    void initCameraSystem();
public:
    void init() override;
    void update() override;
    void render() override;
};
}

#endif