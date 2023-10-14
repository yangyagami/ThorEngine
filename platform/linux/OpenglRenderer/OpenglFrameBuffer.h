#ifndef THOR_OPENGL_FRAME_BUFFER_H
#define THOR_OPENGL_FRAME_BUFFER_H

#include "OpenglTexture2D.h"

namespace Thor {
    class OpenglFrameBuffer {
    public:
        unsigned int mFbo;
    public:
        OpenglFrameBuffer(OpenglTexture2D &texture);
        void bind();
        void unbind();
        ~OpenglFrameBuffer();
    };

}

#endif