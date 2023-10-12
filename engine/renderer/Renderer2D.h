#ifndef THOR_RENDERER_2D_H
#define THOR_RENDERER_2D_H

#include <memory>

#include "glm/glm.hpp"

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
	virtual unsigned int getBatchTimes() = 0;
public:
	virtual void drawRectangle(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) = 0;
	virtual void drawTriangle(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c, const glm::vec4 &color) = 0;
	virtual void drawCircle(const glm::vec2 &pos, float radius, const glm::vec4 &color, int count = 80) = 0;
};

}

#endif
