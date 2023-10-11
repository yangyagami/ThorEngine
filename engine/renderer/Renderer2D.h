#ifndef THOR_RENDERER_2D_H
#define THOR_RENDERER_2D_H

#include <memory>

#include "Vec.hpp"

namespace Thor {

class Renderer2D {
public:
	static std::unique_ptr<Renderer2D> create();
public:
	virtual void fflush() = 0;
public:
	virtual bool init() = 0;
	virtual void beginBatch() = 0;
	virtual void endBatch() = 0;
public:
	virtual void drawRectangle(const Vec2 &pos, const Vec2 &size, const Vec4 &color) = 0;
	virtual void drawTriangle(const Vec2 &a, const Vec2 &b, const Vec2 &c, const Vec4 &color) = 0;
	virtual void drawCircle(const Vec2 &pos, float radius, const Vec4 &color, int count = 80) = 0;
};

}

#endif
