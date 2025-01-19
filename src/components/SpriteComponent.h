#pragma once
#include "../Depend.h"
#include "../Component.h"

class SpriteComponent : public Component {
public:
	SpriteComponent(GameObject* owner, SDL_Renderer* renderer, const char* textureFile, int x = 0, int y = 0);
	~SpriteComponent();

	void SetTexture(const char* newTextureFile);

	void Update(int deltaTime) override;
	void Render() override;

private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect, dstRect;

	int posX;
	int posY;
};