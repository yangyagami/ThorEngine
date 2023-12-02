#ifndef THOR_RENDERER_2D_H
#define THOR_RENDERER_2D_H

#include <memory>

#include "glm/glm.hpp"
#include "Texture2D.h"

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
	virtual void setClearColor(const glm::vec4 &color) = 0;
	virtual glm::vec4 getClearColor() = 0;
	virtual void setRenderToTexture(const std::unique_ptr<Texture2D> &texture) = 0;
	virtual void setView(glm::mat4 &&view) = 0;
	virtual void setView(glm::mat4 &view) = 0;
	virtual void setProjection(glm::mat4 &&projection) = 0;
	virtual void setProjection(glm::mat4 &projection) = 0;
	virtual void drawRectangle(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) = 0;
	virtual void drawTriangle(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c, const glm::vec4 &color) = 0;
	virtual void drawCircle(const glm::vec2 &pos, float radius, const glm::vec4 &color, int count = 80) = 0;
	virtual void drawTexture(const std::unique_ptr<Texture2D> &texture, const glm::vec2 &pos) = 0;
public:
    virtual ~Renderer2D();
};

}

#endif
