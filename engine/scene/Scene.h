#ifndef THOR_SCENE_H
#define THOR_SCENE_H

#include <map>
#include <string>

#include "Object.hpp"

namespace Thor {

class Scene {
private:
	std::map<std::string, Object> mObjects;
public:
	void addObject(Object &obj);
	void removeObject(const std::string &name);
	Scene();
	~Scene();
public:
	virtual void init();
	virtual void update();
	virtual void render();

};

}

#endif
