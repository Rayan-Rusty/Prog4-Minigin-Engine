//
// Created by omen on 14/02/2026.
//

#include "FPSComponent.h"
#include "TextObject.h"
#include <iostream>
dae::FPSComponent::FPSComponent(TextObject* textObject)
    : m_textObject(textObject)
{

}

void dae::FPSComponent::Update(float deltaTime)
{

    if (!m_textObject || deltaTime <= 0.0f) return;

    int fps = static_cast<int>(1.f / deltaTime);
    m_textObject->SetText("FPS: " + std::to_string(fps));
}