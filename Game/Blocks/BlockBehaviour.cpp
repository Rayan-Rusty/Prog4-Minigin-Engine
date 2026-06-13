#include "BlockBehaviour.h"

#include <control.h>

#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "GameActor.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "TilemapComponent.h"
#include "GameLayers.h"
#include "BlockDestroyedState.h"
#include "BlockSolidState.h"



DigDug::BlockBehaviour::BlockBehaviour(dae::GameObject *owner)
    : Component(owner)
{

    ChangeState(std::make_unique<BlockSolidState>());

    GetOwner()->GetComponent<dae::CollisionComponent>()->SetOnCollision(
        [this](dae::CollisionComponent* other)
        {
            if (other->GetOwner()->GetTag() != static_cast<int>(GameTag::Player)) return;
            if (m_iSDestroyed) return;

            m_iSDestroyed = true;
            ChangeState(std::make_unique<BlockDestroyedState>());
            GetOwner()->GetComponent<dae::CollisionComponent>()->SetEnabled(false);
            CollisionManager::GetInstance().Unregister(GetOwner()->GetComponent<dae::CollisionComponent>());
        }
    );
}

void DigDug::BlockBehaviour::Notify(dae::IObserver::Event  , dae::GameActor *)
{

}

void DigDug::BlockBehaviour::Update(float dt)
{
    if (auto newState= m_state->Update(dt, *this))
        ChangeState(std::move(newState));
}

void DigDug::BlockBehaviour::ChangeState(std::unique_ptr<State<BlockBehaviour>> newState)
{
    if (m_state)
        m_state->Exit(*this);

    m_state = std::move(newState);
    m_state->Enter(*this);
}

std::type_index DigDug::BlockBehaviour::GetType() const
{
    return typeid(BlockBehaviour);
}

