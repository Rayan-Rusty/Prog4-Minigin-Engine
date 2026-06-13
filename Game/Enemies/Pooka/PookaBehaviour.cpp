

#include "PookaBehaviour.h"
#include "PookaGhostState.h"
#include "PookaInflatedState.h"
#include "PookaNormalState.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "Layers/GameLayers.h"
#include "PookaMovement.h"


DigDug::PookaBehaviour::PookaBehaviour(dae::GameObject* owner)
    :Component(owner)
{

    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();
    auto pumpObjs = scene->GetObjectByTag(static_cast<int>(GameTag::Pump));
    if (!pumpObjs.empty())
    {
        m_pumpActor = pumpObjs[0]->GetActor();
        m_pumpActor->AddObserver(this);
    }

    auto scoreObjs = scene->GetObjectByTag(static_cast<int>(GameTag::UI));
    if (!scoreObjs.empty())
    {
        if (auto* scoreComp = scoreObjs[0]->GetComponent<ScoreComponent>())
            GetOwner()->GetActor()->AddObserver(scoreComp);
    }


    auto* movement = GetOwner()->GetComponent<PookaMovement>();
    if (movement)
    {
        m_movementActor = movement->GetOwner()->GetActor();
        m_movementActor->AddObserver(this);
    }


    ChangeState(std::make_unique<PookaNormalState>());



}

DigDug::PookaBehaviour::~PookaBehaviour()
{
    m_pumpActor = nullptr;
    m_movementActor = nullptr;
}


void DigDug::PookaBehaviour::Notify(Event event, dae::GameActor *)
{
    if (event == dae::IObserver::Event::EnemyHitWall)
    {
        if (m_dist(m_Rng) < m_GhostChance)
            ChangeState(std::make_unique<PookaGhostState>());
    }
    if (event == dae::IObserver::Event::PumpHitEnemy)
    {
        ChangeState(std::make_unique<PookaInflatedState>());
    }
}

void  DigDug::PookaBehaviour::Update(float dt )
{
     auto newState = m_state->Update(dt, *this);
     if (newState)
         ChangeState(std::move(newState));
}


void  DigDug::PookaBehaviour::ChangeState(std::unique_ptr<State<PookaBehaviour>> newState)
{
     if (m_state)
         m_state->Exit(*this);

     m_state = std::move(newState);
     m_state->Enter(*this);
}

State<DigDug::PookaBehaviour> * DigDug::PookaBehaviour::GetState() const
{
    return m_state.get();
}


std::type_index  DigDug::PookaBehaviour::GetType() const
{
    return typeid(PookaBehaviour);
}
