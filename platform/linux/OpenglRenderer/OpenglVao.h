#ifndef THOR_OPENGL_VAO_H
#define THOR_OPENGL_VAO_H

namespace Thor {
class OpenglVao {
private:
	unsigned int mVao;
public:
	OpenglVao();
	void bind();
	void unbind();
	~OpenglVao();
};
}

#endif
