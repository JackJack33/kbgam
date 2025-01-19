#pragma once
#include "Game.h"
#include "FileManager.h"
#include "Level.h"
#include "Difficulty.h"
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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

	FileManager fileManager;
	fileManager.InitializeFilesystem();
	std::vector<Level*> levels = fileManager.ReadAllLevels();

	int numKeys;
	const Uint8* keyStateCurrent = SDL_GetKeyboardState(&numKeys);
	keyStatePrevious = new Uint8[numKeys];
	memcpy(keyStatePrevious, keyStateCurrent, numKeys);
	if (!keyStatePrevious) {
		std::cout << "Failed to initialize keyStatePrevious array!" << std::endl;
		return;
	}

	Scene* mainMenu = new Scene(renderer);
	Scene* optionsMenu = new Scene(renderer);
	Scene* levelMenu = new Scene(renderer);
	Scene* game = new Scene(renderer);
	scenes = { mainMenu, levelMenu, game };
	activeScene = scenes.at(0);

	// main menu scene

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
	playButtonComponent->SetOnClick([this]() {
		std::cout << "Play button pressed!" << std::endl;
		this->transitionToScene(scenes.at(1));
		timer1 = SDL_GetTicks();
		});
	ButtonComponent* quitButtonComponent = new ButtonComponent(quitButton, renderer, font, "assets/textures/outline.png", "assets/textures/fill.png", "E", 4 * bw, bh);
	quitButtonComponent->SetOnClick([this]() {
		std::cout << "Quit button pressed!" << std::endl;
		this->quit();
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

	// level menu

	for (int i = 0; i < 5; i++) {
		Level* level = levels.at(i);
		GameObject* levelObject = new GameObject();
		SDL_Color color = { 255,255,255,255 };
		levelObject->AddComponent(new TextComponent(levelObject, renderer, font, level->GetArtistName() + " - " + level->GetSongName(), 100, bh, color, false, true));
		levelObject->AddComponent(new TextComponent(levelObject, renderer, font, level->GetSongSubName(), 100, bh + 60, color, false, true));
		levelMenu->AddGameObject(levelObject);
	}

	std::cout << "Initialized" << std::endl;
	isRunning = true;
	return;
}

void Game::handleEvents(int deltaTime) {
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

void Game::handleSceneTransitions(int deltaTime) {
	if (fadeState == FADE_OUT) {
		fadeAlpha += fadeSpeed * deltaTime;
		if (fadeAlpha >= 255) {
			fadeAlpha = 255;
			activeScene = nextScene;
			fadeState = FADE_IN;
		}
	}
	else if (fadeState == FADE_IN) {
		fadeAlpha -= fadeSpeed * deltaTime;
		if (fadeAlpha <= 0) {
			fadeAlpha = 0;
			fadeState = NONE;
			timer2 = SDL_GetTicks();
			std::cout << timer2 - timer1 << std::endl;
		}
	}
}

void Game::update(int deltaTime) {
	handleEvents(deltaTime);
	handleKeyboard();
	handleSceneTransitions(deltaTime);
	activeScene->Update(deltaTime);
	return;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (activeScene) {
		activeScene->Render();
	}

	if (fadeState != NONE) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, (int)fadeAlpha);
		SDL_Rect rect = { 0,0,width,height };
		SDL_RenderFillRect(renderer, &rect);
	}

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

void Game::quit() {
	isRunning = false;
}

bool Game::running() {
	return isRunning;
}

void Game::transitionToScene(Scene* scene) {
	fadeState = FADE_OUT;
	nextScene = scene;
	fadeAlpha = 0;
}