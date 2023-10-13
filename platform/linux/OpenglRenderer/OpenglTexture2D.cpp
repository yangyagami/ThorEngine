#include <fstream>
#include <vector>

#include "OpenglTexture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

namespace Thor {
	OpenglTexture2D::OpenglTexture2D() {
		unsigned char data[4] = { 255, 255, 255, 255 };	
		mWidth = 1;
		mHeight = 1;	
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	OpenglTexture2D::OpenglTexture2D(std::string path) {
		int nrChannels;
		stbi_set_flip_vertically_on_load(true);
		mData = stbi_load(path.c_str(), &mWidth, &mHeight, &nrChannels, 0);	
		if (mData == nullptr) {
			spdlog::error("Cannot open file: {}!", path);
			return;
		}
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLenum mFormat = nrChannels == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, mData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	void OpenglTexture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void OpenglTexture2D::bind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture);
	}
	
	OpenglTexture2D::~OpenglTexture2D() {
		stbi_image_free(mData);
	}

	glm::vec2 OpenglTexture2D::getSize() {
		return glm::vec2(mWidth, mHeight);
	}

	void OpenglTexture2D::update(const OpenglTexture2D &other) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, other.mFormat, GL_UNSIGNED_BYTE, other.mData);
	}

	void OpenglTexture2D::operator=(const OpenglTexture2D &other) {
		mWidth = other.mWidth;
		mHeight = other.mHeight;
		mTexture = other.mTexture;
		mData = other.mData;
		mFormat = other.mFormat;

		bind();
	}

	unsigned int OpenglTexture2D::getID() {
		return mTexture;
	}
}
