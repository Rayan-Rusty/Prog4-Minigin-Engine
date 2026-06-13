//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARBEHAVIOUR_H
#define MINIGIN_FYGARBEHAVIOUR_H
#include <memory>
#include <random>

#include "Component.h"
#include "IObserver.h"
#include "State.h"

class GameObject;

namespace DigDug
{
    class FygarBehaviour final : public dae::Component, public dae::IObserver
    {
    public:


        explicit FygarBehaviour(dae::GameObject* owner);
        ~FygarBehaviour() override = default;

        void Notify(dae::IObserver::Event event, dae::GameActor* actor) override;
        void Update(float dt) override;
        void ChangeState(std::unique_ptr<State<FygarBehaviour>> newState);
        std::type_index GetType() const override;
        State<FygarBehaviour>* GetState() const;

    private:
        std::unique_ptr<State<FygarBehaviour>> m_state;
        dae::GameActor* m_pumpActor     = nullptr;
        dae::GameActor* m_movementActor = nullptr;

        float m_GhostChance{ 0.1f };
        std::mt19937 m_Rng{ std::random_device{}() };
        std::uniform_real_distribution<float> m_dist{ 0.f, 1.f };


        FygarBehaviour(const FygarBehaviour& other) = delete;
        FygarBehaviour(FygarBehaviour&& other) = delete;
        FygarBehaviour& operator=(const FygarBehaviour& other) = delete;
        FygarBehaviour& operator=(FygarBehaviour&& other) = delete;


    };
}


#endif //MINIGIN_FYGARBEHAVIOUR_H