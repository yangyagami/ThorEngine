#include "Scene.h"

namespace Thor {
    void Scene::addObject(Object *obj) {
		int count = mObjects.size();
		std::string name = "Object " + std::to_string(count);
		mObjects[name] = obj;
    }

    void Scene::removeObject(const std::string &name) {
		for (auto &&[name, obj] : mObjects) {
			mObjects.erase(name);
			delete obj;
		}
    }

    std::map<std::string, Object *> &Scene::getObjects() {
		return mObjects;
    }

    Scene::Scene() {
    }

    Scene::~Scene() {
		for (auto &&[name, obj] : mObjects) {
			delete obj;
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
