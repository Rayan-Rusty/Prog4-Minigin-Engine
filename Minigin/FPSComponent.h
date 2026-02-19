//
// Created by omen on 14/02/2026.
//

#pragma once
#include <string>

#include "Component.h"
#include "FPSComponent.h"

namespace dae
{
    class TextComponent;
    class GameObject;
    class FPSComponent final : public Component
    {
    public:
        explicit FPSComponent(GameObject* pOwner);
        FPSComponent(const FPSComponent&) = delete;
        ~FPSComponent() = default;
        FPSComponent& operator=(const FPSComponent&) = delete;

        virtual void Update(float deltaTime);

        std::type_index GetType() const override;
    private:
        TextComponent* m_textObject{nullptr};
    };

}
