#pragma once
#include "Depend.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* textureSheet_in, SDL_Renderer* renderer_in);
};