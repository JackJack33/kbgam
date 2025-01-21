#pragma once
#include "Depend.h"
#include "GameObject.h"

class Game;

class Scene {
public:
	Scene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h);
	virtual ~Scene();

	void AddGameObject(GameObject* gameObject_in);
	void RemoveGameObject(GameObject* gameObject_in);
	void DeleteGameObjects();

	virtual void Start();
	virtual void Update(int deltaTime);
	virtual void Render();

protected:
	
	Game* game;
	SDL_Renderer* renderer;
	TTF_Font* font;
	TTF_Font* fontSmall;
	int width;
	int height;

	std::vector<GameObject*> gameObjects;

};