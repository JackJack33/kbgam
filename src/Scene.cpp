#pragma once
#include "Scene.h"

Scene::Scene(SDL_Renderer* renderer_in) {
	renderer = renderer_in;
}

Scene::~Scene() {
	for (auto gameObject : gameObjects) {
		delete gameObject;
	}
}

void Scene::AddGameObject(GameObject* gameObject_in) {
	gameObjects.push_back(gameObject_in);
}

void Scene::Update(int deltaTime) {
	for (auto gameObject : gameObjects) {
		gameObject->Update(deltaTime);
	}
}

void Scene::Render() {
	for (auto gameObject : gameObjects) {
		gameObject->Render();
	}
}