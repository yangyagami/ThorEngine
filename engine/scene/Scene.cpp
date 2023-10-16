#include "Scene.h"

namespace Thor {
    void Scene::removeObject(const std::string &name) {
		for (auto it = mObjects.begin(); it != mObjects.end(); it++) {
			if ((*it)->name == name) {
				mObjects.erase(it);
				delete (*it);
				break;
			}
		}
    }

    std::vector<Object *> &Scene::getObjects() {
		return mObjects;
    }

    Scene::Scene() {
    }

    Scene::~Scene() {
		for (auto it = mObjects.begin(); it != mObjects.end(); it++) {
			delete (*it);
		}
	}

	void Scene::init() {
		for (auto obj : mObjects) {
			obj->init();
		}
	}

    void Scene::update() {
		for (auto obj : mObjects) {
			obj->update();
		}
	}

    void Scene::render() {
		for (auto obj : mObjects) {
			obj->render();
		}
	}
}
