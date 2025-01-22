#include "DifficultyMenu.h"
#include "../Game.h"
#include "../components/ButtonComponent.h"

DifficultyMenuScene::DifficultyMenuScene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h)
	: Scene(game_in, renderer_in, font_in, fontSmall_in, w, h) {}

DifficultyMenuScene::~DifficultyMenuScene() {}

void DifficultyMenuScene::Start() {

	diffListGameObjects.clear();

	SDL_Color color = { 255,255,255,255 };
	GameObject* backButton = new GameObject();
	backButton->AddComponent(new TextComponent(backButton, renderer, font, "Back", 100, 40, color, true, true));
	ButtonComponent* backButtonComponent = new ButtonComponent(backButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "Q", 100, 100);
	backButtonComponent->SetOnClick([this]() {
		this->game->transitionToScene(1);
		});
	backButton->AddComponent(backButtonComponent);
	AddGameObject(backButton);

	GameObject* arrowButtons = new GameObject();
	arrowButtons->AddComponent(new TextComponent(arrowButtons, renderer, font, "Up", 200, 40, color, true, true));
	arrowButtons->AddComponent(new TextComponent(arrowButtons, renderer, font, "Down", 200, height - 40, color, true, true));
	ButtonComponent* upLevelButtonComponent = new ButtonComponent(arrowButtons, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "W", 200, 100);
	ButtonComponent* downLevelButtonComponent = new ButtonComponent(arrowButtons, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "S", 200, height - 100);
	upLevelButtonComponent->SetOnClick([this]() {
		PrevDifficultyIndex();
		UpdateDifficultyList();
		});
	downLevelButtonComponent->SetOnClick([this]() {
		NextDifficultyIndex();
		UpdateDifficultyList();
		});
	arrowButtons->AddComponent(upLevelButtonComponent);
	arrowButtons->AddComponent(downLevelButtonComponent);
	AddGameObject(arrowButtons);
}

void DifficultyMenuScene::NextDifficultyIndex() {
	diffListIndex++;
	if (diffListIndex > numDiffs - 5) {
		diffListIndex = numDiffs - 5;
	}
	if (diffListIndex < 0) {
		diffListIndex = 0;
	}
}

void DifficultyMenuScene::PrevDifficultyIndex() {
	diffListIndex--;
	if (diffListIndex < 0) {
		diffListIndex = 0;
	}
}

void DifficultyMenuScene::SetLevel(Level* level_in) {
	level = level_in;
	numDiffs = level->GetDifficulties().size();
	UpdateDifficultyList();
}

void DifficultyMenuScene::DeleteDifficultyListObjects() {
	for (auto gameObject : diffListGameObjects) {
		if (gameObject != nullptr) {
			RemoveGameObject(gameObject);
			delete gameObject;
		}
	}
	diffListGameObjects.clear();
}

void DifficultyMenuScene::UpdateDifficultyList() {

	DeleteDifficultyListObjects();
	for (int i = 0; (i < 5) && (i + diffListIndex < numDiffs); i++) {

		int diffIndex = i + diffListIndex;
		Difficulty* diff = level->GetDifficulty(diffIndex);
		GameObject* diffButton = new GameObject();

		SDL_Color color = { 255,255,255,255 };
		diffButton->AddComponent(new TextComponent(diffButton, renderer, fontSmall, diff->GetDifficultyName(), 300 + 50, 100 * (i + 1), color, false, true));
		ButtonComponent* diffButtonComponent = new ButtonComponent(
			diffButton, renderer, font,
			"assets/textures/outline.png", "assets/textures/fill.png",
			std::to_string(i + 1),
			300, 100 * (i + 1));

		diffButtonComponent->SetOnClick([this, diff]() {
			std::cout << "diff selected: " << diff->GetDifficultyName() << std::endl;
			});

		diffButton->AddComponent(diffButtonComponent);
		diffListGameObjects.push_back(diffButton);

		AddGameObject(diffButton);
	}

}