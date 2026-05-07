//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKA_H
#define MINIGIN_POOKA_H
#include <memory>

#include "GameObject.h"


class PookaState;
class GameObject;
class Pooka : public dae::Component
{
public:
    Pooka(dae::GameObject* owner);
    ~Pooka();


    void Update(float dt);
    void ChangeState(std::unique_ptr<PookaState> newState);
    std::type_index GetType() const override;
private:
    std::unique_ptr<PookaState> m_state;

};


#endif //MINIGIN_POOKA_H