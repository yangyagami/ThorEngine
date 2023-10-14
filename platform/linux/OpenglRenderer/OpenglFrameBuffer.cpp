#include "OpenglFrameBuffer.h"
#include "glad/glad.h"

namespace Thor {
    OpenglFrameBuffer::OpenglFrameBuffer(OpenglTexture2D &texture) {
        glGenFramebuffers(1, &mFbo);
        glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
        texture.bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getID(), 0);  
    }
    
    void OpenglFrameBuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    }

    void OpenglFrameBuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenglFrameBuffer::~OpenglFrameBuffer() {
        glDeleteFramebuffers(1, &mFbo);
    }
}