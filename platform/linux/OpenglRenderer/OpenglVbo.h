#ifndef THOR_OPENGL_VBO_H
#define THOR_OPENGL_VBO_H

#include "glad/glad.h"

namespace Thor {

class OpenglVbo {
private:
	GLenum mMode;
	unsigned int mVbo;
public:
	OpenglVbo(GLenum mode, GLsizeiptr dataSize, GLvoid *data, GLenum usage);	
	~OpenglVbo();	
	void bind();
	void unbind();
};

}

#endif
