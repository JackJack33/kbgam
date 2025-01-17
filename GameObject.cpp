#pragma once
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet_in, SDL_Renderer* renderer_in, int xpos_in, int ypos_in) {
	renderer = renderer_in;
	objectTexture = TextureManager::LoadTexture(textureSheet_in, renderer_in);
	xpos = xpos_in;
	ypos = ypos_in;
	return;
}

GameObject::~GameObject() {};

void GameObject::Update() {
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = xpos;
	dstRect.y = ypos;
	dstRect.w = srcRect.w;
	dstRect.h = srcRect.h;
	return;
}

void GameObject::Render() {
	SDL_RenderCopy(renderer, objectTexture, &srcRect, &dstRect);
	return;
}