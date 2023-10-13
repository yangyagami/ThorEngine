#include "Scene.h"

namespace Thor {

	void Scene::addEntity(entt::entity &entity) {
		mEntities.push_back(entity);	
	}
	
	void Scene::removeEntity(entt::entity &entity) {
		mEntities.remove_if([&](entt::entity e){return (entity == e);});
	}

	Scene::Scene() {
	
	}
	
	Scene::~Scene() {
	
	}

}
