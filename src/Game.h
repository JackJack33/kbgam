#pragma once
#include "Depend.h"
#include "Level.h"

enum FadeState {
	NONE,
	FADE_IN,
	FADE_OUT
};

class Scene;
class GameObject;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos = SDL_WINDOWPOS_CENTERED, int ypos = SDL_WINDOWPOS_CENTERED, int w = 800, int h = 600, bool fullscreen = false);

	void handleEvents(int deltaTime);
	void handleKeyboard();
	void handleSceneTransitions(int deltaTime);
	void update(int deltaTime);
	void render();
	void clean();

	void quit();
	bool running();

	void transitionToScene(Scene* scene);
	void transitionToScene(int sceneIndex);

	std::vector<Level*> getLevels();
	Level* getLevel(int levelIndex);

	std::vector<Scene*> scenes;

private:

	int width;
	int height;
	int count;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	TTF_Font* fontSmall;

	Uint8* keyStatePrevious;

	Scene* activeScene;

	FadeState fadeState = NONE;
	double fadeAlpha = 255.0f;
	Scene* nextScene = nullptr;
	float fadeSpeed = 255.0f / 100.0f; // 255 opacity units per 100 milliseconds

	std::vector<Level*> levels;
};