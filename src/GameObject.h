#pragma once
#include "Depend.h"
#include "Component.h"

class Component;

class GameObject {
public:
	GameObject() = default;
	virtual ~GameObject();

	void AddComponent(Component* component);
	void DeleteComponents();

	void Update(int deltaTime);
	void Render();

	void PrintTest();

private:
	std::vector<Component*> components;
};