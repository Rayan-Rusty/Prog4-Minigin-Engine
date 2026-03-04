//
// Created by omen on 14/02/2026.
//

#include "FPSComponent.h"
#include "TextComponent.h"
#include <format>
dae::FPSComponent::FPSComponent(GameObject* pOwner)
    : Component(pOwner)
{
    m_textObject = GetOwner()->GetComponent<TextComponent>();
    if (!m_textObject)
    {
        std::cerr << "FPSComponent : Component not found making a new TextComponent" << std::endl;
        auto newTextComponent = std::make_unique<TextComponent>(GetOwner());
        GetOwner()->AddComponent(std::move(newTextComponent));
        m_textObject = GetOwner()->GetComponent<TextComponent>();
    }
}

void dae::FPSComponent::Update(float deltaTime)
{

    if (!m_textObject || deltaTime <= .0f) return;

    float fps { 1.f / deltaTime};
    m_textObject->SetText(std::format("FPS: {:.1f}" , fps ));
    //TODO checkout wether its correctly doing the fps

}

std::type_index dae::FPSComponent::GetType() const
{
    return typeid(FPSComponent);
}
