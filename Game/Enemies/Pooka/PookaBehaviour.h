//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKA_H
#define MINIGIN_POOKA_H
#include <memory>

#include "../../../Minigin/GameObject/GameObject.h"
#include "State.h"


namespace dae {
    class GameObject;
}
namespace DigDug
{
    class PookaState;

    class PookaBehaviour : public dae::Component
    {
    public:
        PookaBehaviour(dae::GameObject* owner);
        ~PookaBehaviour() = default;


        void Update(float dt) override;
        void ChangeState(std::unique_ptr<State<PookaBehaviour>> newState);
        std::type_index GetType() const override;



        PookaBehaviour(const PookaBehaviour& other) = delete;
        PookaBehaviour(PookaBehaviour&& other) = delete;
        PookaBehaviour& operator=(const PookaBehaviour& other) = delete;
        PookaBehaviour& operator=(PookaBehaviour&& other) = delete;


    private:
        std::unique_ptr<State<PookaBehaviour>> m_state;

    };
}



#endif //MINIGIN_POOKA_H