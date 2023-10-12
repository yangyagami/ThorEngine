#ifndef THOR_OPENGL_SHADER_H
#define THOR_OPENGL_SHADER_H

#include <string>

#include "glm/glm.hpp"
#include "glad/glad.h"

namespace Thor {
class OpenglShader {
private:
	unsigned int mProgram;
private:
	unsigned int createShader(GLenum shaderType, const std::string &source);
public:
	void setVec4(const std::string &name, const glm::vec4 &value);
	void bind();
	void unbind();
	OpenglShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
	~OpenglShader();
};
}

#endif
