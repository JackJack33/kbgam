#pragma once
#include "ButtonComponent.h"
#include "../GameObject.h"

ButtonComponent::ButtonComponent(GameObject* owner, SDL_Renderer* renderer, TTF_Font* font, const char* outlineTexture, const char* fillTexture, const std::string& text, int x, int y)
    : Component(owner), text(text), outlineTexture(outlineTexture), fillTexture(fillTexture) {

    spriteComponent = new SpriteComponent(owner, renderer, outlineTexture, x, y);
    textComponent = new TextComponent(owner, renderer, font, text, x, y);

    owner->AddComponent(spriteComponent);
    owner->AddComponent(textComponent);
}

ButtonComponent::~ButtonComponent() {}

void ButtonComponent::Update() {
    HandleKeyPress();
}

void ButtonComponent::Render() {
    spriteComponent->Render();
    textComponent->Render();
}

void ButtonComponent::SetOnClick(void (*onClickFunc)()) {
    onClick = onClickFunc;
}

void ButtonComponent::HandleKeyPress() {
    std::string keyText(1, text[0]);
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyText.c_str());

    if (keyState[scancode]) {
        if (!keyDown) {
            spriteComponent->SetTexture(fillTexture);
            textComponent->SetColor({ 0,0,0,255 });
            if (onClick) {
                onClick();
            }
            keyDown = true;
        }
    }
    else {
        if (keyDown) {
            spriteComponent->SetTexture(outlineTexture);
            textComponent->SetColor({ 255,255,255,255 });
            keyDown = false;
        }
    }
}