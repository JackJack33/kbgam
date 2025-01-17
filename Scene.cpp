#pragma once
#include "Scene.h"

Scene::Scene(SDL_Renderer* renderer_in) {
	renderer = renderer_in;
	return;
}
Scene::~Scene() {}

void Scene::addGameObject(GameObject* gameObject_in) {
	gameObjects.push_back(gameObject_in);
	return;
}

void Scene::Update() {
	for (GameObject* gameObject : gameObjects) {
		gameObject->Update();
	}
	return;
}

void Scene::Render() {
	for (GameObject* gameObject : gameObjects) {
		gameObject->Render();
	}
	return;
}