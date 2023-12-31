#ifndef THOR_OPENGL_TEXTURE_2D_H
#define THOR_OPENGL_TEXTURE_2D_H

#include <string>

#include "glad/glad.h"
#include "Texture2D.h"

namespace Thor {
class OpenglTexture2D : public Texture2D {
private:
	int mWidth;
	int mHeight;
	unsigned int mTexture;
	unsigned char *mData;
	GLenum mFormat;
	bool mFromStb;
	int *mRefCnt;
private:
	void generateTexture();
	void destroyData();
public:
	OpenglTexture2D();
	OpenglTexture2D(std::string path);
	OpenglTexture2D(const OpenglTexture2D &other) = delete;
	OpenglTexture2D(OpenglTexture2D &&other) = delete;
	OpenglTexture2D(unsigned char *data, int width, int height, int channels);
	~OpenglTexture2D();
	void unbind();
	void bind();
	void update(OpenglTexture2D &other);
	unsigned int getID();
public:
	virtual glm::vec2 getSize() override;
};
}

#endif
