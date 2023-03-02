#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "RenderComponent.h"
#include "GameObject.h"



TextComponent::TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<dae::Font> font, SDL_Color color)
	:BaseComponent(pOwner), m_pFont{font}, m_Color{color}, m_Text{text}
{
}

TextComponent::TextComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void TextComponent::Initialize()
{
	if (m_pOwner == nullptr) {
		//owner not set correctly
		return;
	}

	auto renderComponent = m_pOwner->GetComponent<RenderComponent>();
	if (renderComponent == nullptr) {
		//rendercomponent not found
		return;
	}

	m_pRenderComponent = renderComponent;
}

void TextComponent::Update(GameObject&)
{
	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; 
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		auto pTexture = std::make_shared<dae::Texture2D>(texture);

		if (m_pRenderComponent != nullptr) {
			m_pRenderComponent->SetTexture(pTexture);
		}
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render(const GameObject&) const
{
}

void TextComponent::Recieve(int) const
{
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	m_pFont = font;
}
