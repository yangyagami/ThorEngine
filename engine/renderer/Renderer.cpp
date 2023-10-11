#include "Renderer.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"

namespace Thor {
	Renderer::Renderer() : mVao(nullptr), mVbo(nullptr), mEbo(nullptr), mShader(nullptr) {
	
	}
	
	Renderer::~Renderer() {
		delete[] mVertices;	
		delete[] mIndices;	
	}
	
	bool Renderer::init() {
		spdlog::info("Renderer init success");	
		mCurrentIndicesIndex = mCurrentVerticesIndex = 0;	

		mVertices = new float[RENDERER_MAX_VERTEX];
		mIndices = new unsigned int[RENDERER_MAX_INDICES];

		std::string vertexSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
		)";
		std::string fragmentSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
		)";

		mVao = std::make_unique<OpenglVao>();
		mVbo = std::make_unique<OpenglBuffer>(GL_ARRAY_BUFFER, RENDERER_MAX_VERTEX * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
		mEbo = std::make_unique<OpenglBuffer>(GL_ELEMENT_ARRAY_BUFFER, RENDERER_MAX_INDICES * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
		mShader = std::make_unique<OpenglShader>(vertexSource, fragmentSource);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);  
		return true;	
	}

	void Renderer::fflush() {
		mVbo->update(0, mCurrentVerticesIndex * sizeof(float), mVertices);
		mEbo->update(0, mCurrentIndicesIndex * sizeof(unsigned int), mIndices);
		glDrawElements(GL_TRIANGLES, mCurrentIndicesIndex, GL_UNSIGNED_INT, 0);
	}
	
	void Renderer::beginBatch() {
		glClear(GL_COLOR_BUFFER_BIT);	
		glClearColor(0.2f, 0.0f, 0.0f, 1.0f);	
	}
	
	void Renderer::endBatch() {
		if (mCurrentIndicesIndex == 0 || mCurrentVerticesIndex == 0) return;
		fflush();
		mCurrentVerticesIndex = mCurrentIndicesIndex = 0;
	}
	
	void Renderer::drawRectangle(const Vec2 &pos, const Vec2 &size, const Vec4 &color) {
		if (mCurrentVerticesIndex >= RENDERER_MAX_VERTEX || mCurrentIndicesIndex >= RENDERER_MAX_INDICES) {
			mCurrentVerticesIndex = 0;
			mCurrentIndicesIndex = 0;
			fflush();
		}

		int currentPointCount = mCurrentVerticesIndex / 2;

		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 1;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 3;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;

		mVertices[mCurrentVerticesIndex++] = pos.x;	
		mVertices[mCurrentVerticesIndex++] = pos.y;	
		mVertices[mCurrentVerticesIndex++] = pos.x + size.x;	
		mVertices[mCurrentVerticesIndex++] = pos.y;	
		mVertices[mCurrentVerticesIndex++] = pos.x + size.x;	
		mVertices[mCurrentVerticesIndex++] = pos.y + size.y;	
		mVertices[mCurrentVerticesIndex++] = pos.x;	
		mVertices[mCurrentVerticesIndex++] = pos.y + size.y;	

	}


	void Renderer::drawTriangle(const Vec2 &a, const Vec2 &b, const Vec2 &c, const Vec4 &color) {
		if (mCurrentVerticesIndex >= RENDERER_MAX_VERTEX || mCurrentIndicesIndex >= RENDERER_MAX_INDICES) {
			mCurrentVerticesIndex = 0;
			mCurrentIndicesIndex = 0;
			fflush();
		}

		int currentPointCount = mCurrentVerticesIndex / 2;

		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 1;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	

		mVertices[mCurrentVerticesIndex++] = a.x;	
		mVertices[mCurrentVerticesIndex++] = a.y;	
		mVertices[mCurrentVerticesIndex++] = b.x;	
		mVertices[mCurrentVerticesIndex++] = b.y;	
		mVertices[mCurrentVerticesIndex++] = c.x;	
		mVertices[mCurrentVerticesIndex++] = c.y;	
	}
	
	void Renderer::drawCircle(const Vec2 &pos, float radius, const Vec4 &color, int count) {
		if (mCurrentVerticesIndex >= RENDERER_MAX_VERTEX || mCurrentIndicesIndex >= RENDERER_MAX_INDICES) {
			mCurrentVerticesIndex = 0;
			mCurrentIndicesIndex = 0;
			fflush();
		}

		int currentPointCount = mCurrentVerticesIndex / 2;
		float angle = 360.0f / count;	

		for (int i = 0; i < count; i++) {

			float currentAngle = angle * i;
			float x = pos.x + radius * cos(currentAngle * (3.1415926 / 180.0f));
			float y = pos.y + radius * sin(currentAngle * (3.1415926 / 180.0f));

			mVertices[mCurrentVerticesIndex++] = x;	
			mVertices[mCurrentVerticesIndex++] = y;	

		}

		for (int i = 0; i < count - 2; i++) {
			mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
			mIndices[mCurrentIndicesIndex++] = currentPointCount + i + 1;	
			mIndices[mCurrentIndicesIndex++] = currentPointCount + i + 2;	
		}

	}


}
