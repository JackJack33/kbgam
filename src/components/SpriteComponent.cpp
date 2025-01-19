#pragma once
#include "SpriteComponent.h"
#include "../GameObject.h"

SpriteComponent::SpriteComponent(GameObject* owner, SDL_Renderer* renderer, const char* textureFile, int x, int y)
	: Component(owner), renderer(renderer), posX(x), posY(y) {
	SetTexture(textureFile);

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	srcRect = { 0,0,w,h };
	dstRect = { x-w/2,y-h/2,w,h };
	return;
}

SpriteComponent::~SpriteComponent() {
	SDL_DestroyTexture(texture);
}

void SpriteComponent::SetTexture(const char* newTextureFile) {
	SDL_DestroyTexture(texture);
	texture = IMG_LoadTexture(renderer, newTextureFile);
	if (!texture) {
		std::cout << "Failed to load texture " << IMG_GetError() << std::endl;
	}
}

void SpriteComponent::Update(int deltaTime) {}

void SpriteComponent::Render() {
	SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}