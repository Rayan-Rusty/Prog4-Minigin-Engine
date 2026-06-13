
#include "PookaDeadState.h"

#include "CollisionComponent.h"
#include "EventsIds.h"
#include "PookaBehaviour.h"
#include "SceneManager.h"
#include "SpriteAnimationComponent.h"


void DigDug::PookaDeadState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    obj->SetRenderObject(false);
    auto col = obj->GetComponent<dae::CollisionComponent>();

    col->SetEnabled(false);

    obj->GetActor()->NotifyObservers((dae::IObserver::Event::PookaKilled));
    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();
    scene->GetEventBus().QueueEvent(dae::Event{ EnemyDied });
    obj->SetDeletion(true);
}

std::unique_ptr<State<DigDug::PookaBehaviour>> DigDug::PookaDeadState::Update(float , PookaBehaviour &) {
    return nullptr;
}


void DigDug::PookaDeadState::Exit(PookaBehaviour& )
{

}

std::type_index DigDug::PookaDeadState::GetType() const
{
    return std::type_index(typeid(PookaDeadState));
}
