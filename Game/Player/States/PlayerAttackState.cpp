#include "PlayerAttackState.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "PumpBehaviour.h"
#include "PumpAttackState.h"

void DigDug::PlayerAttackState::Enter(PlayerBehaviour &Data)
{
    auto* owner = Data.GetOwner();
    auto pumps = owner->GetChildren();
    for (auto pump : pumps)
    {
        pump->SetRenderObject(true);


        if (auto* pumpBehaviour = pump->GetComponent<PumpBehaviour>())
            pumpBehaviour->ChangeState(std::make_unique<PumpAttackState>());
    }

}

std::unique_ptr<State<DigDug::PlayerBehaviour>> DigDug::PlayerAttackState::Update(float ,
    PlayerBehaviour &)
{
    return nullptr;
}

void DigDug::PlayerAttackState::Exit(PlayerBehaviour &)
{

}

std::type_index DigDug::PlayerAttackState::GetType() const
{
    return std::type_index(typeid(PlayerAttackState));
}
