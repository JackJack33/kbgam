#pragma once
#include "Depend.h"
#include "GameObject.h"

class Scene {
public:
	Scene(SDL_Renderer* renderer_in);
	~Scene();

	void AddGameObject(GameObject* gameObject_in);

	void Update(int deltaTime);
	void Render();

private:
	
	std::vector<GameObject*> gameObjects;
	SDL_Renderer* renderer;

};