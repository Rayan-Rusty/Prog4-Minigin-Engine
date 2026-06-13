//
// Created by omen on 06/05/2026.
//

#include "PookaNormalState.h"


#include "CollisionComponent.h"
#include "PookaBehaviour.h"
#include "PookaInflatedState.h"
#include "SceneManager.h"
#include "../../../../Minigin/Components/Sprites/SpriteAnimationComponent.h"
#include "Layers/GameLayers.h"
#include "Movement/PookaMovement.h"


void DigDug::PookaNormalState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    if (auto* col = obj->GetComponent<dae::CollisionComponent>())
        col->SetEnabled(true);

    auto tilemapObjs = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag(static_cast<int>(GameTag::TilemapComponent));
    if (!tilemapObjs.empty())
    {
        auto* tilemap = tilemapObjs[0]->GetComponent<TilemapComponent>();
        auto pos= obj->GetTransform().GetWorldPosition();
        auto snapped= tilemap->GridToWorld(tilemap->WorldToGrid(pos));
        obj->GetTransform().SetWorldPosition(snapped);
    }

    if (auto* spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> normalState = { {0,0,16,16}, {16,0,16,16} };
        spriteComp->SetAnimation(normalState, 0.2f, true);
    }


}

std::unique_ptr<State<DigDug::PookaBehaviour>> DigDug::PookaNormalState::Update(float DeltaTime, PookaBehaviour &Data)
{
    auto* movement = Data.GetOwner()->GetComponent<PookaMovement>();
    if (movement)
        movement->Move(DeltaTime);


    return nullptr;
}


void DigDug::PookaNormalState::Exit(PookaBehaviour& )
{

}

std::type_index DigDug::PookaNormalState::GetType() const
{
    return std::type_index(typeid(PookaNormalState));
}
