//
// Created by omen on 31/05/2026.
//

#ifndef MINIGIN_COLLISIONMANAGER_H
#define MINIGIN_COLLISIONMANAGER_H
#include "../Components/Collision/CollisionComponent.h"
#include "Singleton.h"


class CollisionManager final : public dae::Singleton<CollisionManager>
{
public:


    void Register(dae::CollisionComponent* col);
    void Unregister(dae::CollisionComponent* col);

    void Update();

private:
    friend class Singleton<CollisionManager>;
    CollisionManager();

    std::vector<dae::CollisionComponent*> m_cols;
};


#endif //MINIGIN_COLLISIONMANAGER_H