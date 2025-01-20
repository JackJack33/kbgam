#pragma once
#include "../Depend.h"
#include "../Scene.h"

class MainMenuScene : public Scene {
public:
	MainMenuScene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h);
	~MainMenuScene();

	void Start() override;

};