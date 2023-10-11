#include "OpenglBuffer.h"

namespace Thor {

OpenglBuffer::OpenglBuffer(GLenum mode, GLsizeiptr dataSize, GLvoid *data, GLenum usage) : mMode(mode) {
	glGenBuffers(1, &mBuffer);
	glBindBuffer(mMode, mBuffer);
	glBufferData(mMode, dataSize, data, usage);
}

OpenglBuffer::~OpenglBuffer() {
	glDeleteBuffers(1, &mBuffer);
}

void OpenglBuffer::bind() {
	glBindBuffer(mMode, mBuffer);
}

void OpenglBuffer::unbind() {
	glBindBuffer(mMode, 0);
}

}
