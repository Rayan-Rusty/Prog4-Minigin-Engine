#include "BlockDestroyedState.h"

#include <filesystem>

#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "SpriteAnimationComponent.h"
#include "TilemapComponent.h"
#include "Layers/GameLayers.h"

namespace DigDug {
    void BlockDestroyedState::Enter(BlockBehaviour &owner)
    {
        auto* gameObject = owner.GetOwner();

        auto *col = gameObject->GetComponent<dae::CollisionComponent>();
        col->SetEnabled(false);
        CollisionManager::GetInstance().Unregister(col);

        if (auto* spriteComp = gameObject->GetComponent<dae::SpriteAnimationComponent>())
            spriteComp->SetAnimation({{ 13 * 16, 0, 16, 16 }}, 0.f, false);

        gameObject->GetActor()->NotifyObservers(dae::IObserver::Event::TileDestroyed);


    }

    std::unique_ptr<State<BlockBehaviour>> BlockDestroyedState::Update(BlockBehaviour &)
    {
        return nullptr;
    }

    void BlockDestroyedState::Exit(BlockBehaviour &)
    {

    }
} // DigDug