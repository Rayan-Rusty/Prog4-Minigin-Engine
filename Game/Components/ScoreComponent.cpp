#include "ScoreComponent.h"

#include "IObserver.h"
#include "SceneManager.h"
#include "TilemapComponent.h"
#include "GameLayers.h"
#include "GameObject.h"
#include "TextComponent.h"

namespace DigDug {

    ScoreComponent::ScoreComponent(dae::GameObject *owner)
        : Component(owner)
    {
        auto players = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag(static_cast<int>(GameTag::Player));

        for (auto* player : players)
            player->GetActor()->AddObserver(this);
    }

    ScoreComponent::~ScoreComponent()
    {

    }

    void ScoreComponent::Notify( dae::IObserver::Event event, dae::GameActor *actor)
    {
        if (event == Event::PookaKilled || event == Event::FygarKilled)
        {
            // Ask the tilemap what layer this enemy was on
            auto tilemaps = dae::SceneManager::GetInstance()
                .GetActiveScene()
                ->GetObjectByTag(static_cast<int>(GameTag::TilemapComponent));

            if (!tilemaps.empty())
            {
                auto* tilemap = tilemaps[0]->GetComponent<TilemapComponent>();
                int layer = tilemap->GetLayerForWorldPos(
                    actor->GetOwner()->GetTransform().GetWorldPosition());

                m_score += (event == Event::FygarKilled) ? PointsForFygar(layer) : PointsForPooka(layer);
                s_LastScore = m_score;

                if (auto* text = GetOwner()->GetComponent<dae::TextComponent>())
                    text->SetText("Score: " + std::to_string(m_score));
            }
        }
    }

    int ScoreComponent::GetScore()
    {
        return m_score;
    }
    std::type_index ScoreComponent::GetType() const
    {
        return std::type_index(typeid(ScoreComponent));
    }

} // DigDug