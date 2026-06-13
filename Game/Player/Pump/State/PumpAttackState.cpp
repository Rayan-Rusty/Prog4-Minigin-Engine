#include "PumpAttackState.h"

#include "CollisionComponent.h"
#include "Event.h"
#include "EventsIds.h"
#include "GameObject.h"
#include "IObserver.h"
#include "PumpIdleState.h"
#include "../../../../Minigin/Components/Rendering/RenderComponent.h"
#include "SceneManager.h"
#include "../../../../Minigin/Components/Text/SpriteAnimationComponent.h"
#include "Layers/GameLayers.h"
#include "Movement/PlayerMovement.h"

void DigDug::PumpAttackState::OnEvent(const dae::Event &e)
{
    if (e.id == MOVED)
    {
        m_Dir.x = static_cast<float>(e.args[0].intValue);
        m_Dir.y = static_cast<float>(e.args[1].intValue);
    }

}

void DigDug::PumpAttackState::Enter(PumpBehaviour &Data)
{
    m_HitWall = false;
    m_DistanceTravelled = 0.f;

    auto* col = Data.GetOwner()->GetComponent<dae::CollisionComponent>();
    col->SetEnabled(true);
    Data.GetOwner()->SetRenderObject(true);
    bool* hitWall = &m_HitWall;

    m_StartPos = Data.GetOwner()->GetTransform().GetWorldPosition();
    m_Dir = Data.GetDirection();


    col->SetOnCollision([hitWall](dae::CollisionComponent* other)
    {
        auto tag = other->GetOwner()->GetTag();
        if (tag == static_cast<int>(GameTag::Tilemap))
        {
            *hitWall = true;
        }
        else if (tag == static_cast<int>(GameTag::Enemy))
        {
            other->GetOwner()->GetActor()->NotifyObservers(dae::IObserver::Event::PumpHitEnemy);
            *hitWall = true;
        }
    });

    if (auto* sprite = Data.GetOwner()->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> normalState =
        {
            {0, 0, 32, 16},


        };
        sprite->SetAnimation(normalState , 2.f , false);
        sprite->SetFlipHorizontal(m_Dir.x > 0);

    }

}

std::unique_ptr<State<DigDug::PumpBehaviour>> DigDug::PumpAttackState::Update(float DeltaTime , PumpBehaviour &Data)
{

    m_DistanceTravelled += m_Speed * DeltaTime;




    auto* render = Data.GetOwner()->GetComponent<dae::RenderComponent>();
    auto* col = Data.GetOwner()->GetComponent<dae::CollisionComponent>();

    if (m_Dir.x != 0)
    {
        if (m_Dir.x > 0)
        {

            render->SetDestPositionOffset(0.f, 0.f);
            render->SetDestSizeOverride(m_DistanceTravelled, 16.f);
            col->SetSize(m_DistanceTravelled / 2.f, 12.f);

        }
        else
        {

            render->SetDestPositionOffset(-m_DistanceTravelled, 0.f);
            render->SetDestSizeOverride(m_DistanceTravelled, 16.f);
            col->SetSize(-m_DistanceTravelled / 2.f, 12.f);

        }
    }
    else if (m_Dir.y != 0)
    {
        if (m_Dir.y > 0)
        {

            render->SetDestPositionOffset(0.f, 0.f);
            render->SetDestSizeOverride(12.f, m_DistanceTravelled);
            col->SetSize(12.f, m_DistanceTravelled / 2.f);

        }
        else
        {

            render->SetDestPositionOffset(0.f, -m_DistanceTravelled);
            render->SetDestSizeOverride(12.f, m_DistanceTravelled);
            col->SetSize(12.f, -m_DistanceTravelled / 2.f);

        }
    }

    if (m_HitWall || m_DistanceTravelled > m_MaxRange)
        return std::make_unique<PumpIdleState>();

    return nullptr;
}

void DigDug::PumpAttackState::Exit(PumpBehaviour &Data)
{
    if (auto* col = Data.GetOwner()->GetComponent<dae::CollisionComponent>())
    {
        col->SetEnabled(false);
        col->SetOnCollision(nullptr);
    }
}

std::type_index DigDug::PumpAttackState::GetType() const
{
    return std::type_index(typeid(PumpAttackState));
}
