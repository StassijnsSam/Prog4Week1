#include "FPSComponent.h"

#include "TextComponent.h"
#include "GameObject.h"
#include "Time.h"

FPSComponent::FPSComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void FPSComponent::Initialize()
{
	//Needs a text component to work
	if (m_pOwner == nullptr) {
		//owner is not set correctly
		return;
	}

	auto textComponent = m_pOwner->GetComponent<TextComponent>();
	if (textComponent == nullptr) {
		//textcomponent is not found
		return;
	}

	m_pTextComponent = textComponent;
}

void FPSComponent::Update(GameObject&)
{
	//If the textComponent is not set throw an error
	if (m_pTextComponent == nullptr) {
		return;
	}
	
	float elapsedTime = Time::GetInstance().GetDeltaTime();

	m_CurrTime += elapsedTime;

	if (m_CurrTime < m_MinTime) {
		m_FrameAmount++;
	}
	else {
		float FPS = m_FrameAmount / m_MinTime;
		int FPSInt = static_cast<int>(FPS);

		m_pTextComponent->SetText(std::to_string(FPSInt) + " FPS");

		//Reset counters
		m_CurrTime = 0.f;
		m_FrameAmount = 0;
	}
}

void FPSComponent::Render(const GameObject&) const
{
}

void FPSComponent::Recieve(int) const
{
}
