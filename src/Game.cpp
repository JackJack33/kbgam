#pragma once
#include "Game.h"
#include "FileManager.h"
#include "Level.h"
#include "Difficulty.h"
#include "GameObject.h"
#include "Component.h"
#include "components/SpriteComponent.h"
#include "components/TextComponent.h"
#include "components/ButtonComponent.h"
#include "Scene.h"
#include "scenes/MainMenu.h"
#include "scenes/LevelMenu.h"

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
	fontSmall = TTF_OpenFont("assets/fonts/Roboto.ttf", 28);
	if (!font || !fontSmall) {
		std::cout << "Failed to load font!" << std::endl;
		return;
	}

	FileManager fileManager;
	fileManager.InitializeFilesystem();
	levels = fileManager.ReadAllLevels();

	int numKeys;
	const Uint8* keyStateCurrent = SDL_GetKeyboardState(&numKeys);
	keyStatePrevious = new Uint8[numKeys];
	memcpy(keyStatePrevious, keyStateCurrent, numKeys);
	if (!keyStatePrevious) {
		std::cout << "Failed to initialize keyStatePrevious array!" << std::endl;
		return;
	}

	Scene* mainMenu = new MainMenuScene(this, renderer, font, fontSmall, width, height);
	Scene* levelMenu = new LevelMenuScene(this, renderer, font, fontSmall, width, height);
	scenes = { mainMenu, levelMenu };
	activeScene = scenes.at(0);
	activeScene->Start();

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
			activeScene->DeleteGameObjects();
			activeScene = nextScene;
			activeScene->Start();
			fadeState = FADE_IN;
		}
	}
	else if (fadeState == FADE_IN) {
		fadeAlpha -= fadeSpeed * deltaTime;
		if (fadeAlpha <= 0) {
			fadeAlpha = 0;
			fadeState = NONE;
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

std::vector<Level*> Game::getLevels() {
	return levels;
}

Level* Game::getLevel(int levelIndex) {
	return levels.at(levelIndex);
}

void Game::transitionToScene(Scene* scene) {
	fadeState = FADE_OUT;
	nextScene = scene;
	fadeAlpha = 0;
}

void Game::transitionToScene(int sceneIndex) {
	if (sceneIndex < 0 || sceneIndex >= scenes.size()) {
		std::cout << "Could not find scene with index " << sceneIndex << std::endl;
		return;
	}
	fadeState = FADE_OUT;
	nextScene = scenes.at(sceneIndex);
	fadeAlpha = 0;
}