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




        void Update(float deltaTime) override;

        std::type_index GetType() const override;

        FPSComponent(const FPSComponent&) = delete;
        ~FPSComponent() = default;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;
    private:
        TextComponent* m_textObject{nullptr};
    };

}
