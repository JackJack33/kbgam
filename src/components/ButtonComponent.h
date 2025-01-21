#pragma once
#include "../Depend.h"
#include "../Component.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

class ButtonComponent : public Component {
public:
	ButtonComponent(GameObject* owner, SDL_Renderer* renderer, TTF_Font* font, const char* outlineTexture, const char* fillTexture, const std::string& text, int x = 0, int y = 0);
	~ButtonComponent();

	void Update(int deltaTime) override;
	void Render() override;

	void SetOnClick(std::function<void()> onClickFunc);

private:
	SpriteComponent* spriteComponent;
	TextComponent* textComponent;
	std::string text;
	bool keyDown = true;
	const char* outlineTexture;
	const char* fillTexture;
	std::function<void()> onClick;

	void HandleKeyPress();
};