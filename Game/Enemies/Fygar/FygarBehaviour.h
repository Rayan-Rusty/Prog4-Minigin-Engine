//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARBEHAVIOUR_H
#define MINIGIN_FYGARBEHAVIOUR_H
#include <memory>

#include "Component.h"
#include "State.h"

class GameObject;

namespace DigDug
{
    class FygarBehaviour : public dae::Component
    {
    public:
        FygarBehaviour(dae::GameObject* owner);
        ~FygarBehaviour() override = default;
        void Update(float dt) override;
        void ChangeState(std::unique_ptr<State<FygarBehaviour>> newState);

        std::type_index GetType() const override;
    private:
        std::unique_ptr<State<FygarBehaviour>> m_state;

    };
}


#endif //MINIGIN_FYGARBEHAVIOUR_H