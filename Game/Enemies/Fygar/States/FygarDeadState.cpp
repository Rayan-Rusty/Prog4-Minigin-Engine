//
// Created by omen on 08/05/2026.
//

#include "FygarDeadState.h"


#include "CollisionComponent.h"
#include "EventsIds.h"
#include "SpriteAnimationComponent.h"
#include "FygarBehaviour.h"
#include "SceneManager.h"
#include "GameObject/GameObject.h"

void DigDug::FygarDeadState::Enter(FygarBehaviour& Data )
{

    auto* obj = Data.GetOwner();

    obj->SetRenderObject(false);
    auto col = obj->GetComponent<dae::CollisionComponent>();

    col->SetEnabled(false);

    obj->GetActor()->NotifyObservers((dae::IObserver::Event::FygarKilled));
    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();
    scene->GetEventBus().QueueEvent(dae::Event{ EnemyDied });
    obj->SetDeletion(true);

}

std::unique_ptr<State<DigDug::FygarBehaviour>> DigDug::FygarDeadState::Update(float , FygarBehaviour &)
{
    return nullptr;
}


void DigDug::FygarDeadState::Exit(FygarBehaviour &) {

}

std::type_index DigDug::FygarDeadState::GetType() const
{
    return std::type_index(typeid(FygarBehaviour));
}
