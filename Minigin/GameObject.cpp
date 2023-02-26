#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

GameObject::~GameObject() {
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			delete it.second;
			it.second = nullptr;
		}
	}
};

void GameObject::Update()
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Update(*this);
		}
	}
}

void GameObject::Render() const
{
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Render(*this);
		}
	}
}

void GameObject::Send(int message)
{
	//Send message to all components
	for (auto& it : m_pComponents) {
		if (it.second != nullptr) {
			it.second->Recieve(message);
		}
	}
}

