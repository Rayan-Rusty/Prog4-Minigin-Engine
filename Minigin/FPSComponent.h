//
// Created by omen on 14/02/2026.
//

#pragma once
#include <string>


namespace dae
{
    class TextObject;

    class FPSComponent
    {
    public:
        explicit FPSComponent(TextObject* textObject);
        FPSComponent(const FPSComponent&) = delete;
        FPSComponent& operator=(const FPSComponent&) = delete;

        virtual void Update(float deltaTime);
    private:
        TextObject* m_textObject;
    };

}
