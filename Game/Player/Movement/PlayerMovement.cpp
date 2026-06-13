#include "PlayerMovement.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "SpriteAnimationComponent.h"
#include "TilemapComponent.h"
#include "GameLayers.h"

DigDug::PlayerMovement::PlayerMovement(dae::GameObject* gameObject)
    :  Component(gameObject)
{

    auto tilemapObjs = dae::SceneManager::GetInstance().GetActiveScene()
                   ->GetObjectByTag(static_cast<int>(GameTag::TilemapComponent));

    if (!tilemapObjs.empty())
        m_pTilemap = tilemapObjs[0]->GetComponent<TilemapComponent>();

    if (m_pTilemap)
    {
        const glm::ivec2 StartGrid = m_pTilemap->WorldToGrid(GetOwner()->GetTransform().GetWorldPosition());
        m_TargetPos = m_pTilemap->GridToWorld(StartGrid);
        GetOwner()->GetTransform().SetWorldPosition(m_TargetPos);
    }

}

void DigDug::PlayerMovement::Update(float deltaTime)
{
    auto& transform = GetOwner()->GetTransform();
    glm::vec3 currentPos = transform.GetWorldPosition();

    if (m_IsMoving)
    {
        glm::vec3 toTarget = m_TargetPos - currentPos;
        float distance = glm::length(toTarget);
        float step = m_Speed * deltaTime;

        if (step >= distance)
        {
            transform.SetWorldPosition(m_TargetPos);
            m_IsMoving = false;


            if (m_InputDir != glm::ivec2{0,0})
            {
                glm::ivec2 currentGrid = m_pTilemap->WorldToGrid(m_TargetPos);
                glm::ivec2 nextGrid = currentGrid + m_InputDir;
                m_TargetPos = m_pTilemap->GridToWorld(nextGrid);
                m_IsMoving = true;
                FlipDirection();
            }
        }
        else
        {
            transform.SetWorldPosition(currentPos + glm::normalize(toTarget) * step);
        }
    }
    else
    {
        if (m_InputDir != glm::ivec2{0,0})
        {
            glm::ivec2 currentGrid = m_pTilemap->WorldToGrid(currentPos);
            glm::ivec2 nextGrid = currentGrid + m_InputDir;
            m_TargetPos = m_pTilemap->GridToWorld(nextGrid);
            m_IsMoving = true;
            FlipDirection();
        }
    }

    m_InputDir = glm::ivec2{0,0};


}

std::type_index DigDug::PlayerMovement::GetType() const
{
    return std::type_index(typeid(PlayerMovement));
}

void DigDug::PlayerMovement::FlipDirection()
{
    if (m_InputDir.x != 0)
    {
        if (auto* sprite = GetOwner()->GetComponent<dae::SpriteAnimationComponent>())
        {
            sprite->SetFlipHorizontal(m_InputDir.x < 0);
        }
    }
}

void DigDug::PlayerMovement::SetDirection(const glm::ivec2 &direction)
{
    m_InputDir = direction;
}



void DigDug::PlayerMovement::BeginMoveTo(const glm::ivec2 &dir)
{
    m_InputDir = dir;
}
