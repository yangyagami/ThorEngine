#include "Scene.h"

namespace Thor {
    void Scene::addObject(Object *obj) {
		int count = mObjects.size();
		std::string name = "Object " + std::to_string(count);
		mObjects[name] = obj;
    }

    void Scene::removeObject(const std::string &name) {
		mObjects.erase(name);
    }

    Scene::Scene() {
    }

    Scene::~Scene() {
	
	}

    void Scene::init() {
		for (auto &&[name, obj] : mObjects) {
			obj->init();
		}
    }

    void Scene::update() {
		for (auto &&[name, obj] : mObjects) {
			obj->update();
		}
	}

    void Scene::render() {
		for (auto &&[name, obj] : mObjects) {
			obj->render();
		}
	}
}
