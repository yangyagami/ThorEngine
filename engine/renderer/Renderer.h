#ifndef THOR_RENDERER_H
#define THOR_RENDERER_H

#include "Vec.h"

namespace Thor {
class Renderer {
public:
	Renderer();
	~Renderer();
	bool init();
	void beginBatch();
	void endBatch();
	void drawRectangle(const Vec2 &pos, const Vec2 &size, const Vec4 &color);
};
}

#endif
