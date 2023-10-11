#include "OpenglVbo.h"

namespace Thor {

OpenglVbo::OpenglVbo(GLenum mode, GLsizeiptr dataSize, GLvoid *data, GLenum usage) : mMode(mode) {
	glGenBuffers(1, &mVbo);
	glBindBuffer(mMode, mVbo);
	glBufferData(mMode, dataSize, data, usage);
}

OpenglVbo::~OpenglVbo() {
}

void OpenglVbo::bind() {
	glBindBuffer(mMode, mVbo);
}

void OpenglVbo::unbind() {

}

}
