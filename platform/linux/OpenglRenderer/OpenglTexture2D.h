#ifndef THOR_OPENGL_TEXTURE_2D_H
#define THOR_OPENGL_TEXTURE_2D_H

#include <string>

#include "Texture2D.h"

namespace Thor {
class OpenglTexture2D : public Texture2D {
private:
	int mWidth;
	int mHeight;
	unsigned int mTexture;
public:
	void unbind();
	void bind();
	virtual int getWidth() override;
	virtual int getHeight() override;
	OpenglTexture2D();
	OpenglTexture2D(std::string path);
	~OpenglTexture2D();
};
}

#endif
