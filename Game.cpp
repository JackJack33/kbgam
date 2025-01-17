#pragma once
#include "Game.h"
#include "Scene.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Button.h"

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	isRunning = false;

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

	font = TTF_OpenFont("assets/fonts/Roboto.ttf", 40);
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

	Button* testButton = new Button("assets/outline.png", font, renderer, 32, 32, 10, 10, "Options");

	mainMenu->addGameObject(testButton);

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
	if (keysDown != 0) {
		std::cout << keysDown << std::endl;
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