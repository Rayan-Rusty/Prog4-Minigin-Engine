//
// Created by omen on 02/05/2026.
//

#ifndef MINIGIN_PLAYER_H
#define MINIGIN_PLAYER_H
#include <memory>

namespace dae { class GameObject; }

class Player
{
public:
    Player();
    ~Player();

    void Update(float dt);
    void Draw();

private:
    std::unique_ptr<dae::GameObject> m_pGameObject;
};


#endif //MINIGIN_PLAYER_H