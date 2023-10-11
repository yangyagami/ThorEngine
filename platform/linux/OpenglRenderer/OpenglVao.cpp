#include "OpenglVao.h"
#include "glad/glad.h"

namespace Thor {

OpenglVao::OpenglVao() {
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
}

void OpenglVao::bind() {
	glBindVertexArray(mVao);
}

void OpenglVao::unbind() {

}

OpenglVao::~OpenglVao() {

}

}
