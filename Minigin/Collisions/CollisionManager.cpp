//
// Created by omen on 31/05/2026.
//

#include "CollisionManager.h"

#include "GameObject.h"

void CollisionManager::Register(dae::CollisionComponent *col)
{
    m_cols.emplace_back(col);
}

void CollisionManager::Unregister(dae::CollisionComponent *col)
{
    std::erase(m_cols, col);
}

void CollisionManager::Clear()
{
    m_cols.clear();
}

void CollisionManager::Update()
{
    for (size_t i = 0; i < m_cols.size(); ++i)
    {
        for (size_t j = i + 1; j < m_cols.size(); ++j)
        {
            auto* a = m_cols[i];
            auto* b = m_cols[j];

            if (!a->IsEnabled() || !b->IsEnabled()) continue;

            if (a->Intersect(b))
            {

                a->TriggerCollision(b);
                b->TriggerCollision(a);
            }
        }
    }
}


