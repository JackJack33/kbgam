#include "LevelMenu.h"
#include "../Game.h"
#include "../components/ButtonComponent.h"

LevelMenuScene::LevelMenuScene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h) : Scene(game_in, renderer_in, font_in, fontSmall_in, w, h) {

}

LevelMenuScene::~LevelMenuScene() {}

void LevelMenuScene::Start() {
	GameObject* levelList = new GameObject();
	GameObject* arrowButtons = new GameObject();
	ButtonComponent* upLevelButtonComponent = new ButtonComponent(arrowButtons, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "W", 100, 100);
	ButtonComponent* downLevelButtonComponent = new ButtonComponent(arrowButtons, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "S", 100, height - 100);
	upLevelButtonComponent->SetOnClick([this]() {
		levelListIndex--;
		if (levelListIndex <= 0) {
			levelListIndex = 0;
		}
		std::cout << levelListIndex << std::endl;
		updateLevelList(levelMenu, levelList);
		});
	downLevelButtonComponent->SetOnClick([this]() {
		levelListIndex++;
		if (levelListIndex >= ((int)levels.size() - 5)) {
			levelListIndex = ((int)levels.size() - 5);
		}
		if (levelListIndex <= 0) {
			levelListIndex = 0;
		}
		std::cout << levelListIndex << std::endl;
		updateLevelList(levelMenu, levelList);
		});
	arrowButtons->AddComponent(upLevelButtonComponent);
	arrowButtons->AddComponent(downLevelButtonComponent);
	levelMenu->AddGameObject(arrowButtons);
}