#include "OpenglRenderer2D.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"

#define RENDERER2D_BATCH_DO_NEED_REFRESH { \
	if (mCurrentVerticesIndex >= RENDERER2D_MAX_VERTEX || mCurrentIndicesIndex >= RENDERER2D_MAX_INDICES) { \
		mCurrentVerticesIndex = 0; \
		mCurrentIndicesIndex = 0; \
		fflush(); \
	} \
}

#define RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(texture) { \
	if (texture.getID() != mCurrentTexture.getID()) { \
		glm::vec2 size1 = texture.getSize(); \
		glm::vec2 size2 = mCurrentTexture.getSize(); \
		if (!(size1.x == size2.x && size1.y == size2.y)) { \
			mCurrentTexture = texture; \
			fflush(); \
		} else { \
			mCurrentTexture.update(texture); \
		} \
	} \
}

namespace Thor {
	OpenglRenderer2D::OpenglRenderer2D() : mVao(nullptr), mVbo(nullptr), mEbo(nullptr), mShader(nullptr) {
	
	}
	
	OpenglRenderer2D::~OpenglRenderer2D() {
		delete[] mVertices;	
		delete[] mIndices;	
	}
	
	bool OpenglRenderer2D::init() {
		spdlog::info("OpenglRenderer2D init success");	
		mCurrentIndicesIndex = mCurrentVerticesIndex = 0;	
		mCurrentTexture = mDefaultTexture;

		mVertices = new Vertex[RENDERER2D_MAX_VERTEX + RENDERER2D_EXTERN_TRIANGLE * 3];
		mIndices = new unsigned int[RENDERER2D_MAX_INDICES + RENDERER2D_EXTERN_TRIANGLE * 6];

		std::string vertexSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 customColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	customColor = aColor;
	TexCoord = aTexCoord;
}
		)";
		std::string fragmentSource = R"(
#version 330 core
out vec4 FragColor;

in vec4 customColor;
in vec2 TexCoord;

uniform sampler2D customTexture;

void main()
{
    FragColor = texture(customTexture, TexCoord) * customColor;
} 
		)";

		mVao = std::make_unique<OpenglVao>();
		mVbo = std::make_unique<OpenglBuffer>(GL_ARRAY_BUFFER, RENDERER2D_MAX_VERTEX * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		mEbo = std::make_unique<OpenglBuffer>(GL_ELEMENT_ARRAY_BUFFER, RENDERER2D_MAX_INDICES * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
		mShader = std::make_unique<OpenglShader>(vertexSource, fragmentSource);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);  
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);  
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);  
		return true;	
	}

	void OpenglRenderer2D::render() {
		mVbo->update(0, mCurrentVerticesIndex * sizeof(Vertex), mVertices);
		mEbo->update(0, mCurrentIndicesIndex * sizeof(unsigned int), mIndices);
		glDrawElements(GL_TRIANGLES, mCurrentIndicesIndex, GL_UNSIGNED_INT, 0);
	}

	void OpenglRenderer2D::fflush() {
		render();

		mCurrentVerticesIndex = mCurrentIndicesIndex = 0;

		mBatchTimes++;
	}
	
	void OpenglRenderer2D::beginBatch() {
		glClear(GL_COLOR_BUFFER_BIT);	
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	

		mCurrentVerticesIndex = mCurrentIndicesIndex = 0;

		mBatchTimes = 1;
	}

	void OpenglRenderer2D::endBatch() {
		if (mCurrentIndicesIndex == 0 || mCurrentVerticesIndex == 0) return;
		render();
	}

	unsigned int OpenglRenderer2D::getBatchTimes() {
		return mBatchTimes;
	}
	
	void OpenglRenderer2D::drawRectangle(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;

		int currentPointCount = mCurrentVerticesIndex;

		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 1;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 3;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;

		mVertices[mCurrentVerticesIndex++] = Vertex(pos, color, glm::vec2(0.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x + size.x, pos.y), color, glm::vec2(1.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x + size.x, pos.y + size.y), color, glm::vec2(1.0f, 1.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x, pos.y + size.y), color, glm::vec2(0.0f, 1.0f));	

		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(mDefaultTexture);
	}


	void OpenglRenderer2D::drawTriangle(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c, const glm::vec4 &color) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;

		int currentPointCount = mCurrentVerticesIndex;

		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 1;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	

		mVertices[mCurrentVerticesIndex++] = Vertex(a, color, glm::vec2(0.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(b, color, glm::vec2(1.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(c, color, glm::vec2(0.5f, 0.5f));	

		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(mDefaultTexture);
	}
	
	void OpenglRenderer2D::drawCircle(const glm::vec2 &pos, float radius, const glm::vec4 &color, int count) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;

		if (count >= 200) count = 200;

		int currentPointCount = mCurrentVerticesIndex;
		float angle = 360.0f / count;	

		int tempIndex = 0;

		for (int i = 0; i < count; i++) {
			if (tempIndex >= 3) tempIndex = 0;

			float currentAngle = angle * i;
			float x = pos.x + radius * cos(currentAngle * (3.1415926 / 180.0f));
			float y = pos.y + radius * sin(currentAngle * (3.1415926 / 180.0f));

			if (tempIndex == 0)
				mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(x, y), color, glm::vec2(0.0f, 0.0f));	
			else if (tempIndex == 1)
				mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(x, y), color, glm::vec2(1.0f, 0.0f));	
			else if (tempIndex == 2)
				mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(x, y), color, glm::vec2(0.5f, 0.5f));	
			
			tempIndex++;
		}

		for (int i = 0; i < count - 2; i++) {
			mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
			mIndices[mCurrentIndicesIndex++] = currentPointCount + i + 1;	
			mIndices[mCurrentIndicesIndex++] = currentPointCount + i + 2;	
		}

		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(mDefaultTexture);
	}

	void OpenglRenderer2D::drawTexture(const std::unique_ptr<Texture2D> &texture, const glm::vec2 &pos) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;

		int currentPointCount = mCurrentVerticesIndex;

		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 1;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 3;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;

		glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec2 size(0.5f, 0.5f);

		mVertices[mCurrentVerticesIndex++] = Vertex(pos, color, glm::vec2(0.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x + size.x, pos.y), color, glm::vec2(1.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x + size.x, pos.y + size.y), color, glm::vec2(1.0f, 1.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x, pos.y + size.y), color, glm::vec2(0.0f, 1.0f));	

		auto &openglTexture2D = dynamic_cast<OpenglTexture2D&>(*texture);
		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(openglTexture2D);
	}


}
