#pragma once
#include "TextComponent.h"
#include "../GameObject.h"

TextComponent::TextComponent(GameObject* owner, SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color)
	: Component(owner), renderer(renderer), font(font), text(text), posX(x), posY(y), color(color) {
	CreateTextTexture();
}

TextComponent::~TextComponent() {
	SDL_DestroyTexture(textTexture);
}

void TextComponent::SetText(const std::string& newText) {
	text = newText;
	CreateTextTexture();
}

void TextComponent::SetColor(SDL_Color newColor) {
	color = newColor;
	CreateTextTexture();
}

void TextComponent::CreateTextTexture() {
	if (textTexture) {
		SDL_DestroyTexture(textTexture);
	}

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (!surface) {
		std::cout << "Failed to create surface: " << TTF_GetError() << std::endl;
		return;
	}

	textTexture = SDL_CreateTextureFromSurface(renderer, surface);

	textRect.w = surface->w;
	textRect.h = surface->h;
	textRect.x = posX - textRect.w / 2;
	textRect.y = posY - textRect.h / 2;

	SDL_FreeSurface(surface);
}

void TextComponent::Update() {}

void TextComponent::Render() {
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}