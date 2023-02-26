#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"

TextComponent::TextComponent(const std::string& text, std::shared_ptr<dae::Font> font, Transform* pTransform)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(std::move(font)), m_pTextTexture(nullptr), m_pTransform(pTransform)
{
}

void TextComponent::Update(GameObject&)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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
		m_pTextTexture = std::make_shared<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render(const GameObject&) const
{
	if (m_pTextTexture == nullptr)
	{
		//Error that textTexture is not set properly
		return;
	}

	if (m_pTransform == nullptr) {
		//Error that transform is not set properly
		return;
	}

	const auto& pos = m_pTransform->GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
}

void TextComponent::Recieve(int) const
{
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}