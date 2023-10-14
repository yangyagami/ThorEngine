#include <fstream>
#include <vector>

#include "OpenglTexture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

namespace Thor {
	void OpenglTexture2D::generateTexture() {
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, mData);
		glGenerateMipmap(GL_TEXTURE_2D);
    }

    void OpenglTexture2D::destroyData() {
		if (mRefCnt != nullptr) {
			if (*mRefCnt == 0) {
				if (mFromStb)
					stbi_image_free(mData);
				delete mRefCnt;
			} else {
				--(*mRefCnt);
			}
		}
    }

    OpenglTexture2D::OpenglTexture2D() : mRefCnt(nullptr) {
		mFromStb = false;
		unsigned char data[4] = { 255, 255, 255, 255 };	
		mData = data;
		mWidth = 1;
		mHeight = 1;	
		generateTexture();
	}
	
	OpenglTexture2D::OpenglTexture2D(std::string path) : mRefCnt(nullptr) {
		mFromStb = true;
		int nrChannels;
		stbi_set_flip_vertically_on_load(true);
		mData = stbi_load(path.c_str(), &mWidth, &mHeight, &nrChannels, 0);	
		if (mData == nullptr) {
			spdlog::error("Cannot open file: {}!", path);
			return;
		}
		mFormat = nrChannels == 3 ? GL_RGB : GL_RGBA;
		generateTexture();
	}

    OpenglTexture2D::OpenglTexture2D(unsigned char *data, int width, int height, int channels) : mWidth(width), mHeight(height), mData(data), mFormat(format), mRefCnt(nullptr) {
		mFromStb = false;
		mFormat = channels == 3 ? GL_RGB : GL_RGBA;
		generateTexture();
	}

    void OpenglTexture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void OpenglTexture2D::bind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture);
	}
	
	OpenglTexture2D::~OpenglTexture2D() {
		destroyData();
		glDeleteTextures(1, &mTexture);
	}

	glm::vec2 OpenglTexture2D::getSize() {
		return glm::vec2(mWidth, mHeight);
	}

	void OpenglTexture2D::update(OpenglTexture2D &other) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		mData = other.mData;
		if (other.mRefCnt == nullptr) {
			other.mRefCnt = new int;
			*other.mRefCnt = 0;
		}
		if (mRefCnt != nullptr) {
			destroyData();
		}
		mRefCnt = other.mRefCnt;
		++(*mRefCnt);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, other.mFormat, GL_UNSIGNED_BYTE, other.mData);
	}

	unsigned int OpenglTexture2D::getID() {
		return mTexture;
	}
}
