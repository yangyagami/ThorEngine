#ifndef THOR_OBJECT_H
#define THOR_OBJECT_H

#include <vector>

#include "spdlog/spdlog.h"

namespace Thor {
class Object {
protected:
	std::vector<Object *> mChildren;
	Object *mParent;
public:
	std::string name;
public:
    Object(const std::string &name) : mParent(nullptr), name(name) {
    }

	Object *getParent() {
		return mParent;
	}

	Object *getRoot() {
		Object *root = mParent;
		while (root != nullptr) {
			root = root->mParent;
		}

		return root;
	}

	void addChild(Object *child) {
		child->mParent = this;
		mChildren.push_back(child);
	}

    virtual ~Object() {
		for (auto child : mChildren) {
			delete child;
		}
    }

    virtual void init() {
		for (auto child : mChildren) {
			child->init();
		}
	}

    virtual void update() {
		for (auto child : mChildren) {
			child->update();
		}
	}

    virtual void render() {
		for (auto child : mChildren) {
			child->render();
		}
	}
};
}

#endif
