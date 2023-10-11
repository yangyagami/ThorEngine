#ifndef THOR_RENDERER_H
#define THOR_RENDERER_H

#include <memory>
#include <array>

#include "Vec.hpp"
#include "OpenglVao.h"
#include "OpenglBuffer.h"
#include "OpenglShader.h"

#define RENDERER_MAX_TRIANGLE (10000)
#define RENDERER_MAX_VERTEX (RENDERER_MAX_TRIANGLE * 3)
#define RENDERER_MAX_INDICES (RENDERER_MAX_VERTEX * 6)

namespace Thor {
class Renderer {
private:
	int mCurrentVerticesIndex;
	int mCurrentIndicesIndex;
	float *mVertices;
	unsigned int *mIndices;
private:
	std::unique_ptr<OpenglVao> mVao;	
	std::unique_ptr<OpenglBuffer> mVbo;	
	std::unique_ptr<OpenglBuffer> mEbo;	
	std::unique_ptr<OpenglShader> mShader;	
private:
	void fflush();
public:
	Renderer();
	~Renderer();
	bool init();
	void beginBatch();
	void endBatch();
public:
	void drawRectangle(const Vec2 &pos, const Vec2 &size, const Vec4 &color);
	void drawTriangle(const Vec2 &a, const Vec2 &b, const Vec2 &c, const Vec4 &color);
	void drawCircle(const Vec2 &pos, float radius, const Vec4 &color, int count = 80);
};
}

#endif
