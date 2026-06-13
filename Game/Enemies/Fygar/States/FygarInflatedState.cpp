//
// Created by omen on 08/05/2026.
//

#include "FygarInflatedState.h"

#include "CollisionComponent.h"
#include "SpriteAnimationComponent.h"
#include "FygarBehaviour.h"
#include "FygarDeadState.h"
#include "GameObject.h"


void DigDug::FygarInflatedState::Enter(FygarBehaviour& Data)
{

    auto* obj = Data.GetOwner();


    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> InflateFrames =
        {
            {0, 64, 16, 16},
            {16 , 64, 32, 32},
            {48 , 64, 32, 32},
            {70+16 , 64, 32, 32}
        };

        spriteComp->SetAnimation( InflateFrames, 0.2f , true);
    }
    auto col = obj->GetComponent<dae::CollisionComponent>();

    col->SetEnabled(false);
}

std::unique_ptr<State<DigDug::FygarBehaviour>> DigDug::FygarInflatedState::Update(float dt, FygarBehaviour &)
{
    m_timer += dt;

    if (m_timer >= m_DeflateTime)
    {

        return std::make_unique<FygarDeadState>();
    }
    return nullptr;
}


void DigDug::FygarInflatedState::Exit(FygarBehaviour &) {

}

std::type_index DigDug::FygarInflatedState::GetType() const
{
    return std::type_index(typeid(FygarInflatedState));
}
