#ifndef THOR_OPENGL_RENDERER_2D_H
#define THOR_OPENGL_RENDERER_2D_H

#include <memory>
#include <array>

#include "Renderer2D.h"
#include "glm/glm.hpp"
#include "OpenglVao.h"
#include "OpenglBuffer.h"
#include "OpenglShader.h"
#include "OpenglTexture2D.h"

#define RENDERER2D_MAX_TRIANGLE (10000)
#define RENDERER2D_EXTERN_TRIANGLE (300)
#define RENDERER2D_MAX_VERTEX (RENDERER2D_MAX_TRIANGLE * 3)
#define RENDERER2D_MAX_INDICES (RENDERER2D_MAX_TRIANGLE * 6)

namespace Thor {
class OpenglRenderer2D : public Renderer2D {
private:
	struct Vertex {
		glm::vec2 pos;
		glm::vec4 color;
		glm::vec2 texCoord;
		
		Vertex() = default;
		Vertex(const glm::vec2 &pos, const glm::vec4 &color, const glm::vec2 &texCoord) : pos(pos), color(color), texCoord(texCoord) {}
	};
private:
	int mCurrentVerticesIndex;
	int mCurrentIndicesIndex;
	Vertex *mVertices;
	unsigned int *mIndices;
	unsigned int mBatchTimes;
private:
	std::unique_ptr<OpenglVao> mVao;	
	std::unique_ptr<OpenglBuffer> mVbo;	
	std::unique_ptr<OpenglBuffer> mEbo;	
	std::unique_ptr<OpenglShader> mShader;	

	OpenglTexture2D mDefaultTexture;
	OpenglTexture2D *mCurrentTexture;
private:
	void render();
public:
	virtual void fflush() override;
public:
	OpenglRenderer2D();
	virtual ~OpenglRenderer2D();
	virtual bool init() override;
	virtual void beginBatch() override;
	virtual void endBatch() override;
	virtual unsigned int getBatchTimes() override;
public:
	void drawRectangle(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) override;
	void drawTriangle(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c, const glm::vec4 &color) override;
	void drawCircle(const glm::vec2 &pos, float radius, const glm::vec4 &color, int count = 80) override;
	void drawTexture(const std::unique_ptr<Texture2D> &texture, const glm::vec2 &pos) override;
};
}

#endif
