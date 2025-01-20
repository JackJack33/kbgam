#include "MainMenu.h"
#include "../Game.h"
#include "../components/ButtonComponent.h"

MainMenuScene::MainMenuScene(Game* game_in, SDL_Renderer* renderer_in, TTF_Font* font_in, TTF_Font* fontSmall_in, int w, int h) : Scene(game_in, renderer_in, font_in, fontSmall_in, w, h) {

}

MainMenuScene::~MainMenuScene() {

}

void MainMenuScene::Start() {

	int bh = height / 2;
	int bw = width / 6;

	GameObject* optionsButton = new GameObject();
	GameObject* playButton = new GameObject();
	GameObject* quitButton = new GameObject();

	ButtonComponent* optionsButtonComponent = new ButtonComponent(optionsButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "Q", 2 * bw, bh);
	optionsButtonComponent->SetOnClick([]() {
		std::cout << "Options button pressed!" << std::endl;
		});
	ButtonComponent* playButtonComponent = new ButtonComponent(playButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "W", 3 * bw, bh);
	playButtonComponent->SetOnClick([this]() {
		this->game->transitionToScene(1);
		});
	ButtonComponent* quitButtonComponent = new ButtonComponent(quitButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "E", 4 * bw, bh);
	quitButtonComponent->SetOnClick([this]() {
		this->game->quit();
		});

	optionsButton->AddComponent(optionsButtonComponent);
	playButton->AddComponent(playButtonComponent);
	quitButton->AddComponent(quitButtonComponent);

	optionsButton->AddComponent(new TextComponent(optionsButton, renderer, font, "Optn", 2 * bw, bh - 60));
	playButton->AddComponent(new TextComponent(playButton, renderer, font, "Play", 3 * bw, bh - 60));
	quitButton->AddComponent(new TextComponent(quitButton, renderer, font, "Quit", 4 * bw, bh - 60));

	AddGameObject(optionsButton);
	AddGameObject(playButton);
	AddGameObject(quitButton);
}