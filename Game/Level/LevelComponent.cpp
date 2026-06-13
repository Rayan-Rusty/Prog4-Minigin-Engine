#include "LevelComponent.h"

#include "EnemySpawnerComponent.h"
#include "EnemyTraits.h"
#include "EventsIds.h"
#include "SceneManager.h"
#include "TilemapComponent.h"
#include "GameLayers.h"

void DigDug::LevelComponent::OnEvent(const dae::Event &e)
{
    if (e.id == EnemySpawned)
    {
        ++m_EnemiesAlive;
    }
    else if (e.id == EnemyDied)
    {
        --m_EnemiesAlive;

        if (m_EnemiesAlive <= 0 && !m_IsLoading)
            m_PendingAdvance = true;
    }
}

DigDug::LevelComponent::LevelComponent(dae::GameObject *owner, std::vector<LevelData> levels)
    : Component(owner) , m_Levels(levels)
{

}


void DigDug::LevelComponent::Update(float )
{
    if (m_PendingAdvance)
    {
        m_PendingAdvance = false;
        AdvanceLevel();
    }
    if (m_PendingSceneChange)
    {
        m_PendingSceneChange = false;

        dae::SceneManager::GetInstance().SetPendingScene(2);

    }
}

void DigDug::LevelComponent::Render() const
{

}

std::type_index DigDug::LevelComponent::GetType() const
{
    return std::type_index(typeid(LevelComponent));
}

void DigDug::LevelComponent::AdvanceLevel()
{
    dae::Event e(Victory);
    dae::SceneManager::GetInstance().GetActiveScene()->GetEventBus().QueueEvent(e);
    ++m_CurrentLevel;
    if (m_CurrentLevel >= static_cast<int>(m_Levels.size()))
    {
        m_PendingSceneChange = true;
        return;
    }

    m_IsLoading = true;
    m_EnemiesAlive = 0;
    LoadCurrentLevel();
    m_IsLoading = false;
}


void DigDug::LevelComponent::LoadCurrentLevel()
{


    const auto& data = m_Levels[m_CurrentLevel];
    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();

    // Reload tilemap
    auto tilemapObjs = scene->GetObjectByTag(static_cast<int>(GameTag::TilemapComponent));
    if (!tilemapObjs.empty())
        if (auto* tm = tilemapObjs[0]->GetComponent<TilemapComponent>())
        {

            tm->LoadFromFile(data.tilemapIndex);
        }
    auto enemies = scene->GetObjectByTag(static_cast<int>(GameTag::Enemy));
    for (auto* enemy : enemies)
        enemy->SetDeletion(true);

    auto spawners = scene->GetObjectByTag(static_cast<int>(GameTag::Spawner));
    if (!spawners.empty())
         for (auto* spawner : spawners)
        {
            spawner->SetDeletion(true);
        }


    //
    auto pookaSpawnerObj = std::make_unique<dae::GameObject>( static_cast<int>(DigDug::Layer::Background ), static_cast<int>(DigDug::GameTag::Spawner));
    auto pookaComp = std::make_unique<EnemySpawnerComponent<PookaTraits>>(pookaSpawnerObj.get(), scene );
    pookaComp->LoadFromFile(data.EnemyPooka);
    pookaSpawnerObj->AddComponent(std::move(pookaComp));
    scene->Add(std::move(pookaSpawnerObj));

    auto fygarSpawnerObj = std::make_unique<dae::GameObject>(static_cast<int>(DigDug::Layer::Background ), static_cast<int>(DigDug::GameTag::Spawner));
    auto fygarComp = std::make_unique<EnemySpawnerComponent<FygarTraits>>(fygarSpawnerObj.get(), scene);
    fygarComp->LoadFromFile(data.EnemyFygar);
    fygarSpawnerObj->AddComponent(std::move(fygarComp));
    scene->Add(std::move(fygarSpawnerObj));

    auto playerObjs = scene->GetObjectByTag(static_cast<int>(GameTag::Player));
    if (!playerObjs.empty())
        playerObjs[0]->GetTransform().SetWorldPosition(data.PlayerPos);

    scene->SortByLayer();
}

