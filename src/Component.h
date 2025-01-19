#pragma once
#include "Depend.h"
#include "GameObject.h"

class GameObject;

class Component {
public:
	Component(GameObject* owner) : owner(owner) {}
	virtual ~Component() = default;

	virtual void Update(int deltaTime) = 0;
	virtual void Render() = 0;

protected:
	GameObject* owner;
};