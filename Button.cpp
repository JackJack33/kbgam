#pragma once
#include "Button.h"
#include "GameObject.h"
#include "TextureManager.h"

Button::Button(const char* textureSheet_in, TTF_Font* font_in, SDL_Renderer* renderer_in, int width_in, int height_in, int xpos_in, int ypos_in, std::string text_in) : GameObject(textureSheet_in, renderer_in, xpos_in, ypos_in) {
	width = width_in;
	height = height_in;
	text = text_in;
	font = font_in;
	return;
};

Button::~Button() {};

void Button::Update() {};

void Button::Render() {};