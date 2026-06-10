#include "ScoreComponent.h"

#include "SceneManager.h"
#include "TilemapComponent.h"
#include "Layers/GameLayers.h"

namespace DigDug {
    ScoreComponent::ScoreComponent(dae::GameObject *owner)
        : Component(owner)
    {
        auto players = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag(static_cast<int>(GameTag::Player));

        for (auto* player : players)
            player->GetActor()->AddObserver(this);
    }

    ScoreComponent::~ScoreComponent() {
    }

    void ScoreComponent::Notify(dae::GameActor *actor, Event event)
    {
        if (event == Event::EnemyKilled)
        {
            // Ask the tilemap what layer this enemy was on
            auto tilemaps = dae::SceneManager::GetInstance()
                .GetActiveScene()
                ->GetObjectByTag(static_cast<int>(GameTag::Tilemap));

            if (!tilemaps.empty())
            {
                auto* tilemap = tilemaps[0]->GetComponent<TilemapComponent>();
                int layer = tilemap->GetLayerForWorldPos(
                    actor->GetOwner()->GetTransform().GetWorldPosition());
                m_score += PointsForPooka(layer);
            }
        }
    }

    int ScoreComponent::GetScore()
    {
        return m_score;
    }
} // DigDug