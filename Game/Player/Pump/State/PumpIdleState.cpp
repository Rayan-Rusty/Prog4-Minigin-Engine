#include "PumpIdleState.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "../../../../Minigin/Components/Rendering/RenderComponent.h"

void DigDug::PumpIdleState::Enter(PumpBehaviour &Data)
{
    Data.GetOwner()->SetRenderObject(false);
    auto* col = Data.GetOwner()->GetComponent<dae::CollisionComponent>();
    col->SetEnabled(false);
    if (auto* render = Data.GetOwner()->GetComponent<dae::RenderComponent>())
        render->ClearDestSizeOverride();

    Data.GetOwner()->GetTransform().SetLocalPosition({0.f,0.f,0.f});
}

std::unique_ptr<State<DigDug::PumpBehaviour>> DigDug::PumpIdleState::Update(float , PumpBehaviour &)
{
    return nullptr;
}

void DigDug::PumpIdleState::Exit(PumpBehaviour &)
{
}

std::type_index DigDug::PumpIdleState::GetType() const
{
    return std::type_index(typeid(PumpIdleState));
}
