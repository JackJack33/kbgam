#pragma once
#include "GameObject.h"

GameObject::~GameObject() {
	DeleteComponents();
}

void GameObject::AddComponent(Component* component) {
	components.push_back(component);
}

void GameObject::DeleteComponents() {
	for (auto component : components) {
		delete component;
	}
	components.clear();
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

void GameObject::PrintTest() {
	std::cout << "i am alive" << std::endl;
}