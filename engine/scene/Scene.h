#ifndef THOR_SCENE_H
#define THOR_SCENE_H

#include <list>

#include "entt/entt.hpp"

namespace Thor {

class Scene {
private:
	std::list<entt::entity> mEntities;
public:
	void addEntity(entt::entity &entity);
	void removeEntity(entt::entity &entity);
	Scene();
	~Scene();
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

};

}

#endif
