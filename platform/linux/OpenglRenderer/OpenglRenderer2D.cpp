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
	if (mCurrentTexture == nullptr) {\
		mCurrentTexture = &texture; \
		mCurrentTexture->bind(); \
	} \
	if (texture.getID() != mCurrentTexture->getID()) { \
		glm::vec2 size1 = texture.getSize(); \
		glm::vec2 size2 = mCurrentTexture->getSize(); \
		if (!(size1.x == size2.x && size1.y == size2.y)) { \
			fflush(); \
			mCurrentTexture = &texture; \
			mCurrentTexture->bind(); \
		} else { \
			mCurrentTexture->update(texture); \
		} \
	} \
}

namespace Thor {
	OpenglRenderer2D::OpenglRenderer2D() : mVao(nullptr), mVbo(nullptr), mEbo(nullptr), mFbo(nullptr), mShader(nullptr), mCurrentTexture(nullptr) {
	
	}
	
	OpenglRenderer2D::~OpenglRenderer2D() {
		delete[] mVertices;	
		delete[] mIndices;	
	}
	
	bool OpenglRenderer2D::init() {
		spdlog::info("OpenglRenderer2D init success");	
		mCurrentIndicesIndex = mCurrentVerticesIndex = 0;	

		mVertices = new Vertex[RENDERER2D_MAX_VERTEX + RENDERER2D_EXTERN_TRIANGLE * 3];
		mIndices = new unsigned int[RENDERER2D_MAX_INDICES + RENDERER2D_EXTERN_TRIANGLE * 6];

		std::string vertexSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 projection;

out vec4 customColor;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * vec4(aPos, 0.0, 1.0);
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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mProjection = glm::mat4(1.0f);
		mView = glm::mat4(1.0f);

		setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		return true;	
	}

	void OpenglRenderer2D::render() {
		mShader->bind();
		mVao->bind();
		mVbo->update(0, mCurrentVerticesIndex * sizeof(Vertex), mVertices);
		mEbo->update(0, mCurrentIndicesIndex * sizeof(unsigned int), mIndices);
		glDrawElements(GL_TRIANGLES, mCurrentIndicesIndex, GL_UNSIGNED_INT, 0);
	}

	void OpenglRenderer2D::fflush() {
		render();

		mCurrentVerticesIndex = mCurrentIndicesIndex = 0;
		mCurrentTexture = nullptr;

		mBatchTimes++;
	}
	
	void OpenglRenderer2D::beginBatch() {		
		if (mFbo != nullptr)
			mFbo->bind();
		else 
			mFbo->unbind();

		glClear(GL_COLOR_BUFFER_BIT);	
		glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);	
		mCurrentVerticesIndex = mCurrentIndicesIndex = 0;
		mCurrentTexture = nullptr;

		mShader->bind();
		mVao->bind();
		mShader->setMat4("projection", mProjection);
		mShader->setMat4("view", mView);

		mBatchTimes = 1;
	}

	void OpenglRenderer2D::endBatch() {
		if (!(mCurrentIndicesIndex == 0 || mCurrentVerticesIndex == 0)) {
			render();
		}
		if (mFbo != nullptr) {
			mFbo->unbind();
			glClear(GL_COLOR_BUFFER_BIT);	
			glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);	
		}
	}

	unsigned int OpenglRenderer2D::getBatchTimes() {
		return mBatchTimes;
	}
	
	void OpenglRenderer2D::drawRectangle(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;
		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(mDefaultTexture);

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

	}


	void OpenglRenderer2D::drawTriangle(const glm::vec2 &a, const glm::vec2 &b, const glm::vec2 &c, const glm::vec4 &color) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;
		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(mDefaultTexture);

		int currentPointCount = mCurrentVerticesIndex;

		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 1;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	

		mVertices[mCurrentVerticesIndex++] = Vertex(a, color, glm::vec2(0.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(b, color, glm::vec2(1.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(c, color, glm::vec2(0.5f, 0.5f));	

	}
	
	void OpenglRenderer2D::drawCircle(const glm::vec2 &pos, float radius, const glm::vec4 &color, int count) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;
		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(mDefaultTexture);

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

	}

	void OpenglRenderer2D::drawTexture(const std::unique_ptr<Texture2D> &texture, const glm::vec2 &pos) {
		RENDERER2D_BATCH_DO_NEED_REFRESH;
		auto &openglTexture2D = dynamic_cast<OpenglTexture2D&>(*texture);
		RENDERER2D_BATCH_DO_TEXTURE_NEED_REFRESH(openglTexture2D);

		int currentPointCount = mCurrentVerticesIndex;

		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 1;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 2;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 3;	
		mIndices[mCurrentIndicesIndex++] = currentPointCount + 0;

		glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec2 size = texture->getSize();

		mVertices[mCurrentVerticesIndex++] = Vertex(pos, color, glm::vec2(0.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x + size.x, pos.y), color, glm::vec2(1.0f, 0.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x + size.x, pos.y + size.y), color, glm::vec2(1.0f, 1.0f));	
		mVertices[mCurrentVerticesIndex++] = Vertex(glm::vec2(pos.x, pos.y + size.y), color, glm::vec2(0.0f, 1.0f));	

	}

	void OpenglRenderer2D::setClearColor(const glm::vec4 &color) {
		mBackgroundColor = color;	
	}

    void OpenglRenderer2D::setRenderToTexture(const std::unique_ptr<Texture2D> &texture) {
		auto &openglTexture2D = dynamic_cast<OpenglTexture2D&>(*texture);
		if (mFbo != nullptr) {
			spdlog::warn("Already set a framebuffer! Will be reset");
			mFbo.reset();
		}
		mFbo = std::make_unique<OpenglFrameBuffer>(openglTexture2D);
    }

    glm::vec4 OpenglRenderer2D::getClearColor() {
		return mBackgroundColor;
	}

	void OpenglRenderer2D::setView(glm::mat4 &&view) {
		mView = view;	
	}

	void OpenglRenderer2D::setProjection(glm::mat4 &&projection) {
		mProjection = projection;	
	}

}
