#pragma once
#include "GameObject.h"

class Button : public GameObject {
public: 
	Button(const char* textureSheet_in, TTF_Font* font_in, SDL_Renderer* renderer_in, int width_in, int height_in, int xpos_in = 0, int ypos_in = 0, std::string text_in = "Lorem Ipsum");
	~Button();

	void Update(); // override
	void Render(); // override

private:
	int width;
	int height;

	TTF_Font* font;
	std::string text;
};