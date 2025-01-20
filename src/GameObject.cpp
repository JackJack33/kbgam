#pragma once
#include "GameObject.h"

GameObject::~GameObject() {
	DeleteComponents();
}

void GameObject::AddComponent(Component* component) {
	components.push_back(component);
}

void GameObject::DeleteComponents() {
	components.clear();
	for (auto component : components) {
		delete component;
	}
	std::cout << "deleted2 " << components.size() << std::endl;
}

void GameObject::Update(int deltaTime) {
	for (auto component : components) {
		component->Update(deltaTime);
	}
}

void GameObject::Render() {
	for (auto component : components) {
		component->Render();
	}
}