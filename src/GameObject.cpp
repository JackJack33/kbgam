#pragma once
#include "GameObject.h"

GameObject::~GameObject() {
	for (auto component : components) {
		delete component;
	}
}

void GameObject::AddComponent(Component* component) {
	components.push_back(component);
}

void GameObject::Update() {
	for (auto component : components) {
		component->Update();
	}
}

void GameObject::Render() {
	for (auto component : components) {
		component->Render();
	}
}