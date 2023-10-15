#ifndef THOR_SCENE_H
#define THOR_SCENE_H

#include <map>
#include <string>

#include "Object.hpp"

namespace Thor {

class Scene {
private:
	std::map<std::string, Object *> mObjects;
public:
	void addObject(Object *obj);
	void removeObject(const std::string &name);
	std::map<std::string, Object *> &getObjects();
	Scene();
	~Scene();
public:
	virtual void update();
	virtual void render();

};

}

#endif
