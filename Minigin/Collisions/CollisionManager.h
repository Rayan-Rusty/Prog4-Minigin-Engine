//
// Created by omen on 31/05/2026.
//

#ifndef MINIGIN_COLLISIONMANAGER_H
#define MINIGIN_COLLISIONMANAGER_H
#include "CollisionComponent.h"
#include "Singleton.h"


class CollisionManager final : public dae::Singleton<CollisionManager>
{
public:


    void ClearPair(dae::CollisionComponent* a, dae::CollisionComponent* b);
    void Register(dae::CollisionComponent* col);
    void Unregister(dae::CollisionComponent* col);
    void Clear();
    void Update();

private:
    friend class Singleton<CollisionManager>;
    CollisionManager() = default;

    std::vector<dae::CollisionComponent*> m_cols;
    std::vector<std::pair<size_t, size_t>> m_activeOverlaps;
};


#endif //MINIGIN_COLLISIONMANAGER_H