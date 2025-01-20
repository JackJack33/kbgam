#pragma once
#include "Scene.h"

Scene::Scene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h) {
	game = game_in;
	renderer = renderer_in;
	font = font_in;
	fontSmall = fontSmall_in;
	width = w;
	height = h;
}

Scene::~Scene() {
	for (auto gameObject : gameObjects) {
		delete gameObject;
	}
}

void Scene::AddGameObject(GameObject* gameObject_in) {
	gameObjects.push_back(gameObject_in);
}

void Scene::Start() {}

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