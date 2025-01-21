#include "LevelMenu.h"
#include "../Game.h"
#include "../components/ButtonComponent.h"

LevelMenuScene::LevelMenuScene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h) : Scene(game_in, renderer_in, font_in, fontSmall_in, w, h) {

}

LevelMenuScene::~LevelMenuScene() {}

void LevelMenuScene::Start() {

	numLevels = game->getLevels().size();
	levelListGameObjects.clear();

	SDL_Color color = { 255,255,255,255 };
	GameObject* backButton = new GameObject();
	backButton->AddComponent(new TextComponent(backButton, renderer, font, "Back", 100, 40, color, true, true));
	ButtonComponent* backButtonComponent = new ButtonComponent(backButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "Q", 100, 100);
	backButtonComponent->SetOnClick([this]() {
		this->game->transitionToScene(0);
		});
	backButton->AddComponent(backButtonComponent);
	AddGameObject(backButton);

	GameObject* arrowButtons = new GameObject();
	arrowButtons->AddComponent(new TextComponent(arrowButtons, renderer, font, "Up", 200, 40, color, true, true));
	arrowButtons->AddComponent(new TextComponent(arrowButtons, renderer, font, "Down", 200, height - 40, color, true, true));
	ButtonComponent* upLevelButtonComponent = new ButtonComponent(arrowButtons, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "W", 200, 100);
	ButtonComponent* downLevelButtonComponent = new ButtonComponent(arrowButtons, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "S", 200, height - 100);
	upLevelButtonComponent->SetOnClick([this]() {
		PrevLevelIndex();
		UpdateLevelList();
		});
	downLevelButtonComponent->SetOnClick([this]() {
		NextLevelIndex();
		UpdateLevelList();
		});
	arrowButtons->AddComponent(upLevelButtonComponent);
	arrowButtons->AddComponent(downLevelButtonComponent);
	AddGameObject(arrowButtons);

	UpdateLevelList();
}

void LevelMenuScene::NextLevelIndex() {
	levelListIndex++;
	if (levelListIndex > numLevels - 5) {
		levelListIndex = numLevels - 5;
	}
	if (levelListIndex < 0) {
		levelListIndex = 0;
	}
}

void LevelMenuScene::PrevLevelIndex() {
	levelListIndex--;
	if (levelListIndex < 0) {
		levelListIndex = 0;
	}
}

void LevelMenuScene::UpdateLevelList() {

	for (auto gameObject : levelListGameObjects) {
		if (gameObject != nullptr) {
			RemoveGameObject(gameObject);
			delete gameObject;
		}
	}
	levelListGameObjects.clear();

	int bw = width / 6;
	for (int i = 0; (i < 5) && (i + levelListIndex < numLevels); i++) {

		int levelIndex = i + levelListIndex;
		Level* level = game->getLevel(levelIndex);
		GameObject* levelButton = new GameObject();

		SDL_Color color = { 255,255,255,255 };
		levelButton->AddComponent(new TextComponent(levelButton, renderer, font, level->GetSongName(), 300 + 50, 100 * (i+1), color, false, true));
		ButtonComponent* levelButtonComponent = new ButtonComponent(
			levelButton, renderer, font,
			"assets/textures/outline.png", "assets/textures/fill.png",
			std::to_string(i + 1),
			300, 100 * (i+1));

		levelButtonComponent->SetOnClick([this, level]() {
			std::cout << "level selected: " << level->GetSongName() << std::endl;
			});

		levelButton->AddComponent(levelButtonComponent);
		levelListGameObjects.push_back(levelButton);

		AddGameObject(levelButton);
	}
}