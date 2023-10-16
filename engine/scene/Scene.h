#ifndef THOR_SCENE_H
#define THOR_SCENE_H

#include <map>
#include <string>

#include "Object.hpp"

namespace Thor {

class Scene {
private:
	std::vector<Object *> mObjects;
public:
	template<typename T = Object>
	Object *addObject(const std::string &name = "") {
		int count = mObjects.size();
		std::string n;
		if (name == "")
			n = "Object " + std::to_string(count);
		else
			n = name;
		Object *retObj = new T(n);
		mObjects.push_back(retObj);

		return retObj;
	}
	void removeObject(const std::string &name);
	std::vector<Object *> &getObjects();
	Scene();
	~Scene();
public:
	virtual void init();
	virtual void update();
	virtual void render();

};

}

#endif
