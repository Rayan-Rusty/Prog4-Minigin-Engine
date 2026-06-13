
#include "PlayerWalkingState.h"

#include "GameObject.h"
#include "PlayerIdleState.h"
#include "SpriteAnimationComponent.h"
#include "PlayerBehaviour.h"



void DigDug::PlayerWalkingState::Enter(PlayerBehaviour &Data)
{
    m_Timer = 0;
    auto* obj = Data.GetOwner();



    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> normalState =
        {
            {0, 0, 16, 16},
            {16 , 0, 16, 16}

        };

        spriteComp->SetAnimation( normalState, 0.2f , true);
    }
}

std::unique_ptr<State<DigDug::PlayerBehaviour>> DigDug::PlayerWalkingState::Update(float , PlayerBehaviour&Data )
{

    if (!Data.GetIsMoving())
    {
        return std::make_unique<PlayerIdleState>();
    }

    return nullptr;

}

void DigDug::PlayerWalkingState::Exit(PlayerBehaviour &) {

}

std::type_index DigDug::PlayerWalkingState::GetType() const
{
    return std::type_index(typeid(PlayerWalkingState));
}
