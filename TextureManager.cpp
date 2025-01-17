#pragma once
#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* textureSheet_in, SDL_Renderer* renderer_in) {
	SDL_Surface* tempSurface = IMG_Load(textureSheet_in);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_in, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}