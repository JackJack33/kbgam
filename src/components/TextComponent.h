#pragma once
#include "../Depend.h"
#include "../Component.h"

class TextComponent : public Component {
public:
	TextComponent(GameObject* owner, SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x = 0, int y = 0, SDL_Color color = { 255,255,255,255 });
	~TextComponent();

	void SetText(const std::string& newText);
	void SetColor(SDL_Color newColor);
	void Update() override;
	void Render() override;

private:
	SDL_Texture* textTexture;
	SDL_Renderer* renderer;
	SDL_Rect textRect;
	TTF_Font* font;
	SDL_Color color;
	std::string text;

	int posX;
	int posY;

	void CreateTextTexture();
};