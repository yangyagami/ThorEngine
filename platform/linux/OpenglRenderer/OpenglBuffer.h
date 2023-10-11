#ifndef THOR_OPENGL_VBO_H
#define THOR_OPENGL_VBO_H

#include "glad/glad.h"

namespace Thor {

class OpenglBuffer {
private:
	GLenum mMode;
	unsigned int mBuffer;
public:
	OpenglBuffer(GLenum mode, GLsizeiptr dataSize, GLvoid *data, GLenum usage);	
	~OpenglBuffer();	
	void update(GLintptr offset, GLsizeiptr size, const void *data);
	void bind();
	void unbind();
};

}

#endif
