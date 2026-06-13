
#include "PookaInflatedState.h"


#include "CollisionComponent.h"
#include "PookaBehaviour.h"
#include "PookaDeadState.h"
#include "SpriteAnimationComponent.h"


void DigDug::PookaInflatedState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> InflateFrames =
        {
            {0, 32, 16, 16},
            {16 , 32, 32, 32},
            {48 , 32, 32, 32},
            {80 , 32, 32, 32}
        };

        spriteComp->SetAnimation( InflateFrames, 0.2f , true);
    }
    auto col = obj->GetComponent<dae::CollisionComponent>();

    col->SetEnabled(false);


}

std::unique_ptr<State<DigDug::PookaBehaviour>> DigDug::PookaInflatedState::Update(float dt , PookaBehaviour & )
{
    m_timer += dt;

    if (m_timer >= m_DeflateTime)
    {

        return std::make_unique<PookaDeadState>();
    }



    return nullptr;
}
void DigDug::PookaInflatedState::Exit(PookaBehaviour& ) {

}

std::type_index DigDug::PookaInflatedState::GetType() const
{
    return std::type_index(typeid(PookaInflatedState));
}
