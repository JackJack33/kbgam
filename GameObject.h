#pragma once
#include "Depend.h"

class GameObject {
public:
	GameObject(const char* textureSheet_in, SDL_Renderer* renderer_in, int xpos_in = 0, int ypos_in = 0);
	~GameObject();

	void Update();
	void Render();

private:
	int xpos;
	int ypos;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, dstRect;
	SDL_Renderer* renderer;
};