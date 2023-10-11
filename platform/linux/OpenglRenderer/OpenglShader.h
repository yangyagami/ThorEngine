#ifndef THOR_OPENGL_SHADER_H
#define THOR_OPENGL_SHADER_H

#include <string>

#include "glad/glad.h"

namespace Thor {
class OpenglShader {
private:
	unsigned int mProgram;
private:
	unsigned int createShader(GLenum shaderType, const std::string &source);
public:
	void bind();
	void unbind();
	OpenglShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
	~OpenglShader();
};
}

#endif
