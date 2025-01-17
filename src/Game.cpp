#pragma once
#include "Game.h"
#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "components/SpriteComponent.h"
#include "components/TextComponent.h"
#include "components/ButtonComponent.h"

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen) {

	isRunning = false;
	width = w;
	height = h;

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize SDL!" << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window) {
		std::cout << "Failed to create window!" << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cout << "Failed to create renderer!" << std::endl;
		return;
	}

	if (TTF_Init() != 0) {
		std::cout << "Failed to initialize TTF!" << std::endl;
		return;
	}

	font = TTF_OpenFont("assets/fonts/Roboto.ttf", 35);
	if (!font) {
		std::cout << "Failed to load font!" << std::endl;
		return;
	}

	int numKeys;
	const Uint8* keyStateCurrent = SDL_GetKeyboardState(&numKeys);
	keyStatePrevious = new Uint8[numKeys];
	memcpy(keyStatePrevious, keyStateCurrent, numKeys);
	if (!keyStatePrevious) {
		std::cout << "Failed to initialize keyStatePrevious array!" << std::endl;
		return;
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	Scene* mainMenu = new Scene(renderer);
	Scene* game = new Scene(renderer);
	scenes = { mainMenu, game };
	activeScene = scenes.at(0);

	int bh = h / 2;
	int bw = w / 6;

	GameObject* optionsButton = new GameObject();
	GameObject* playButton = new GameObject();
	GameObject* quitButton = new GameObject();

	ButtonComponent* optionsButtonComponent = new ButtonComponent(optionsButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "Q", 2 * bw, bh);
	optionsButtonComponent->SetOnClick([]() {
		std::cout << "Options button pressed!" << std::endl;
		});
	ButtonComponent* playButtonComponent = new ButtonComponent(playButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "W", 3 * bw, bh);
	playButtonComponent->SetOnClick([]() {
		std::cout << "Play button pressed!" << std::endl;
		});
	ButtonComponent* quitButtonComponent = new ButtonComponent(quitButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "E", 4 * bw, bh);
	quitButtonComponent->SetOnClick([]() {
		std::cout << "Quit button pressed!" << std::endl;
		});

	optionsButton->AddComponent(optionsButtonComponent);
	playButton->AddComponent(playButtonComponent);
	quitButton->AddComponent(quitButtonComponent);

	optionsButton->AddComponent(new TextComponent(optionsButton, renderer, font, "Optn", 2 * bw, bh - 60));
	playButton->AddComponent(new TextComponent(playButton, renderer, font, "Play", 3 * bw, bh - 60));
	quitButton->AddComponent(new TextComponent(quitButton, renderer, font, "Quit", 4 * bw, bh - 60));

	mainMenu->AddGameObject(optionsButton);
	mainMenu->AddGameObject(playButton);
	mainMenu->AddGameObject(quitButton);

	std::cout << "Initialized" << std::endl;
	isRunning = true;
	return;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
	return;
}

void Game::handleKeyboard() {
	int numKeys;
	const Uint8* keyStateCurrent = (Uint8*)SDL_GetKeyboardState(&numKeys);

	int keysDown = 0;
	for (int i = 0; i < numKeys; i++) {
		if (keyStateCurrent[i] == 1 && keyStatePrevious[i] == 0) {
			keysDown++;
		}
	}
	memcpy(keyStatePrevious, keyStateCurrent, numKeys);
	return;
}

void Game::update() {
	activeScene->Update();
	return;
}

void Game::render() {
	SDL_RenderClear(renderer);
	activeScene->Render();
	SDL_RenderPresent(renderer);
	return;
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Cleaned" << std::endl;
	return;
}

bool Game::running() {
	return isRunning;
}