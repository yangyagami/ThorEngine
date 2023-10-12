#include "glad/glad.h"
#include "OpenglShader.h"
#include "spdlog/spdlog.h"

namespace Thor {

OpenglShader::OpenglShader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) {
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	char infoLog[512] = { 0 };
	mProgram = glCreateProgram();
	glAttachShader(mProgram, vertexShader);
	glAttachShader(mProgram, fragmentShader);
	glLinkProgram(mProgram);
	int success = 0;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(mProgram, 512, nullptr, infoLog);
		spdlog::error("ERROR::SHADER_PROGRAM::LINK_ERROR {}", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(mProgram);
}

OpenglShader::~OpenglShader() {
	glDeleteProgram(mProgram);
}

unsigned int OpenglShader::createShader(GLenum shaderType, const std::string &source) {
	unsigned int shader = glCreateShader(shaderType);
	auto sourceCstr = source.c_str();
	glShaderSource(shader, 1, &sourceCstr, nullptr);
	glCompileShader(shader);

	int success = 0;
	char infoLog[512] = { 0 };
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
		spdlog::error("ERROR::SHADER::{}::COMPILATION_FAILED {}", shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", infoLog);	
	}

	return shader;
}

void OpenglShader::bind() {
	glUseProgram(mProgram);
}

void OpenglShader::unbind() {
	glUseProgram(0);
}

void OpenglShader::setVec4(const std::string &name, const glm::vec4 &value) {
	int vertexColorLocation = glGetUniformLocation(mProgram, name.c_str());
	glUseProgram(mProgram);
	glUniform4f(vertexColorLocation, value.r, value.g, value.b, value.a);
}

}
