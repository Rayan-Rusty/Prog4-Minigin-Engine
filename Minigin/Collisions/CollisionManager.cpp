

#include "CollisionManager.h"

#include "GameObject.h"

void CollisionManager::ClearPair(dae::CollisionComponent *a, dae::CollisionComponent *b)
{
    auto itA = std::find(m_pCols.begin(), m_pCols.end(), a);
    auto itB = std::find(m_pCols.begin(), m_pCols.end(), b);
    if (itA == m_pCols.end() || itB == m_pCols.end()) return;

    size_t i = std::distance(m_pCols.begin(), itA);
    size_t j = std::distance(m_pCols.begin(), itB);

    auto pair = std::make_pair(std::min(i,j), std::max(i,j));
    std::erase_if(m_activeOverlaps, [&pair](const std::pair<size_t,size_t>& p) {
        return p == pair;
    });
}

void CollisionManager::Register(dae::CollisionComponent *pCol)
{
    m_pCols.emplace_back(pCol);
}

void CollisionManager::Unregister(dae::CollisionComponent *pCol)
{
    auto it = std::find(m_pCols.begin(), m_pCols.end(), pCol);
    if (it == m_pCols.end()) return;
    size_t removedIdx = std::distance(m_pCols.begin(), it);

    std::erase_if(m_activeOverlaps, [removedIdx](const std::pair<size_t, size_t>& p) {
        return p.first == removedIdx || p.second == removedIdx;
    });


    for (auto& pair : m_activeOverlaps)
    {
        if (pair.first  > removedIdx) pair.first--;
        if (pair.second > removedIdx) pair.second--;
    }

    m_pCols.erase(it);
}

void CollisionManager::Clear()
{
    m_pCols.clear();
}

void CollisionManager::Update()
{
    std::vector<std::pair<size_t, size_t>> currentoverlaps;

    for (size_t i = 0; i < m_pCols.size(); ++i)
    {
        for (size_t j = i + 1; j < m_pCols.size(); ++j)
        {
            auto* a = m_pCols[i];
            auto* b = m_pCols[j];

            if (!a->IsEnabled() || !b->IsEnabled()) continue;

            if (a->Intersect(b))
            {
                auto pair = std::make_pair(i, j);
                currentoverlaps.push_back(pair);
                if (std::find(m_activeOverlaps.begin(), m_activeOverlaps.end(), pair) == m_activeOverlaps.end())
                {
                    a->TriggerCollision(b);
                    b->TriggerCollision(a);
                }

            }
        }
    }
    m_activeOverlaps = std::move(currentoverlaps);
}


